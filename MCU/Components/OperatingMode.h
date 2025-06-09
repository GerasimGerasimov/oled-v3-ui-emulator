#pragma once
#include <common.h>
#include <array>

class TParameter;
class ISignal;
class Slot;

class OperatingMode : public TVisualObject
{
private:
	u8 colorState;
	unsigned int yPosition;

	std::string normalValue;
	std::string cleanValue;
	std::string vacValue;
	std::string manualValue;

	std::string normalName;
	std::string cleanName;
	std::string vacName;
	std::string manualName;

	TParameter* objNormal;
	TParameter* objClean;
	TParameter* objVac;
	TParameter* objManual;

	bool cmdSendInProcess;
	u16 TryCount;
	int SubscriberID = 0;
	std::array <ISignal*, 4> container;
	int component = 0;
	int yPos = 0;

public:

	OperatingMode(int x, int y, u8 colorState, std::string ready, std::string clean, std::string vac, std::string manual);
	void view() override;
	const u16 getHeight(void);
	void background();
	void drawBorder();
	void stateValue(u8 newColor);
	int getYPosition();
	void setYPosition();
	void sendModeCmd(ISignal* signal);
	void sendCmd(std::string& refValue);
	void SlotUpdate(Slot* slot, u8* reply);
	void SlotUpdate(const char* sector, TSlotHandlerArsg args);
	void SlotUpdateRAM(TSlotHandlerArsg args);
	void hidingBorder();
	bool ProcessMessage(TMessage* m);
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) override;
	
	std::vector <TVisualObject*> List;
};

