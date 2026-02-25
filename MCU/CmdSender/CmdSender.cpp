#include "CmdSender.h"
#include <AppModbusSlave.h>
#include "Alarms.h"

u16 CmdSender::keyStopReset = 0;
u16 CmdSender::keyRun = 0;
//u16 CmdSender::keyClean = 0;
//u16 CmdSender::keyVAC = 0;
u16 CmdSender::keyPrevStopReset = 0;
u16 CmdSender::keyPrevRun = 0;
u16 CmdSender::keyMode = 0;
u16 CmdSender::keyPrevMode = 0;
bool CmdSender::cmdSendInProcess = false;
u16 CmdSender::TryCount = 3;

static const std::string CMD_RUN = "1111";
static const std::string CMD_STOP = "1000";
static const std::string CMD_RESET = "2222";
static const std::string CMD_CHARGE = "3333";
static const std::string CMD_CHARGE_EQUAL = "4444";
static const std::string CMD_DISCHARGE = "5555";

#define RECEIVE_COMAND_FLAG 1

//static const std::string CMD_NORMAL = "5310";
//static const std::string CMD_CLEAN = "5311";
//static const std::string CMD_VAC = "5312";
//static const std::string CMD_TEST = "5313";

//static const u16 SELECT_CMD_NORMAL = 0;
//static const u16 SELECT_CMD_CLEAN = 1;
//static const u16 SELECT_CMD_VAC = 2;
//static const u16 SELECT_CMD_MANU = 3;

static const u16 SELECT_CMD_CHARGE = 2;
static const u16 SELECT_CHARGE_EQUAL = 3;
static const u16 SELECT_DISCHARGE = 4;

#define DION0 (1 << 0)
#define DION1 (1 << 1)
#define DION2 (1 << 2)
#define DION3 (1 << 3)
#define DION4 (1 << 4)
#define DION5 (1 << 5)

#define SLAVE_DIN15   0x0001  
#define SLAVE_DIN14   0x0002   
#define SLAVE_DIN13   0x0004
#define SLAVE_DIN12   0x0008
#define SLAVE_DIN11   0x0010
#define SLAVE_DIN10   0x0020
#define SLAVE_DIN9    0x0040
#define SLAVE_DIN8    0x0080
#define SLAVE_DIN7    0x0100
#define SLAVE_DIN6    0x0200
#define SLAVE_DIN5    0x0400
#define SLAVE_DIN4    0x0800
#define SLAVE_DIN3    0x1000
#define SLAVE_DIN2    0x2000
#define SLAVE_DIN1    0x4000
#define SLAVE_DIN0    0x8000

#define DI_DBLCK_BTN            SLAVE_DIN0
#define DI_DIR_MODE             SLAVE_DIN1
#define DI_STAB_MODE            SLAVE_DIN2
#define DI_REF_PLUS             SLAVE_DIN3
#define DI_REF_MINUS            SLAVE_DIN4
#define DI_ON                   SLAVE_DIN5
#define DI_OVERHEAT_AVERS       SLAVE_DIN6
#define DI_OVERHEAT_REVERS      SLAVE_DIN7
#define DI_OVERHEAT_COOLIANT    SLAVE_DIN8
#define DI_PWR_STATE            SLAVE_DIN9
#define DI_LOW_PRESSURE         SLAVE_DIN10
#define DI_HI_PRESSURE          SLAVE_DIN11
#define DI_MODBUS_CONTROL       SLAVE_DIN12

void CmdSender::init() {

}



void CmdSender::update(const u16 din) {
    updateSlaveDIN(din);
}

void CmdSender::updateKeyMode(const u16 din) {
	//keyClean = (din & (1 << 2));
	//keyVAC   = (din & (1 << 3));

	if (din & DION2) keyMode = SELECT_CMD_CHARGE;
	if (din & DION3) keyMode = SELECT_CHARGE_EQUAL;
	if (din & DION4) keyMode = SELECT_DISCHARGE;
	//if ((keyClean !=0) && (keyVAC !=0)) keyMode = SELECT_CMD_MANU;
	if (keyPrevMode != keyMode) {
		/*TODO тут бы использовать таймер, чтобы чтобы при переключении,
		  использовать фиксированное (за время) значение*/
		if (cmdSendInProcess != true) {
			switch (keyMode) {
			case SELECT_CMD_CHARGE:
				sendCmd((std::string&)CMD_CHARGE);
				break;
			case SELECT_CHARGE_EQUAL:
				sendCmd((std::string&)CMD_CHARGE_EQUAL);
				break;
			case SELECT_DISCHARGE:
				sendCmd((std::string&)CMD_DISCHARGE);
				break;
			//case SELECT_CMD_MANU:
			//	sendCmd((std::string&)CMD_TEST);
			//	break;
			}
			keyPrevMode = keyMode;
		}
	}
}

void CmdSender::updateKeyStop(const u16 din) {
	keyStopReset = (din & DION0);
	if (keyPrevStopReset != keyStopReset) {
		if (keyStopReset) {
			if (cmdSendInProcess != true) {
				if (Alarms::isAlarm()) {
					sendCmd((std::string&)CMD_RESET);
				}
				else {
					sendCmd((std::string&)CMD_STOP);
				}
			}
		}
		keyPrevStopReset = keyStopReset;
	}
}

void CmdSender::updateKeyRun(const u16 din) {
	keyRun = (din & DION1);
	if (keyPrevRun != keyRun) {
		if (keyRun) {
			if (cmdSendInProcess != true) {
				sendCmd((std::string&) CMD_RUN);
			}
		}
		keyPrevRun = keyRun;
	}
}

void CmdSender::sendCmd(std::string& code) {
	std::string cmd = "U1/RAM/cmd_DI/";
	TryCount = 3;
	cmdSendInProcess = true;
	ModbusSlave::setValue(cmd, code, &SlotUpdate);
}

void CmdSender::SlotUpdate(Slot* slot, u8* reply) {
	if (slot->RespondLenghtOrErrorCode) {
		slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
		cmdSendInProcess = false;
	}
	else {
		if (TryCount)
			TryCount--;
		else {
			slot->Flags |= (u16)SlotStateFlags::SKIP_SLOT;
			cmdSendInProcess = false;
		}
	}
	/*TODO разделить использование слота с PageEditValue*/
}

//Массив соответствия DI дисплея и DI устройства
//Индекс массива соответствует DI дисплея
u16 MaskSlaveDIN[] = {DI_ON, DI_REF_PLUS, DI_REF_MINUS, DI_STAB_MODE, DI_DBLCK_BTN};

void CmdSender::updateSlaveDIN(const u16 din){
	u16 result = 0;
	for(u16 i = 0; i < 5; ++i){
		//Пробег по используемым DI
		if(din & (1 << i)){
			//Если DI включен -> добавить маску DI устройства
			result |= MaskSlaveDIN[i];
		}
	}
	//Добавляем флаг, сообщающий, что идёт новая посылка
	result |= RECEIVE_COMAND_FLAG;
	char s[8];
	sprintf(s, "%d", result);
	std::string sendRes(s);
	sendCmd(sendRes);
}
