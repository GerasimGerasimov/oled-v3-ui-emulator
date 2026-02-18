#pragma once
#include "common.h"

class TParameter;

class SparksIndicator : public TVisualObject
{
private:
	u8 colorState;
	std::string sparks;
	std::string nameSparks;

	TParameter* objSparks;

public:
	SparksIndicator(int x, int y, u8 colorState, std::string sparks);
	const u16 getHeight(void);
	void view() override;
	void sparksValue();
	void updateObj(std::string sector, const TSlotHandlerArsg& args, const char* format);
	bool ProcessMessage(TMessage* m);
	void areaState();
	void startEdit() override;
};

