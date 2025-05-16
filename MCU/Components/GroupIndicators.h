#pragma once
#include "common.h"
class GroupIndicators : public TVisualObject
{
private:
	int height = 63;
	int width = 17;
	int x, y;

public:

	GroupIndicators(int x, int y);
	void view() override;
	const u16 getHeight(void);

	void outValue(std::string outValue);

	void sparksValue(std::string sparksValue);

	void stateValue(char mode);

	void point();

};

