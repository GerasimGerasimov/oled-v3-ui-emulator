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

	std::string modeValue;

	std::string infoMode;

	TParameter* objMode;

	bool cmdSendInProcess;
	u16 TryCount;
	int SubscriberID = 0;
	std::array <ISignal*, 3> container;
	int component = 0;
	int yPos = 0;

public:

	OperatingMode(int x, int y, u8 colorState, std::string mode);
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
	void startEdit() override;
	void hidingBorder();
	bool ProcessMessage(TMessage* m);
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format) override;
	
	std::vector <TVisualObject*> List;
};

