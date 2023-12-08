#pragma once

#include <TagLine.h>

class TTagLineVarSize : public TTagLine
{
private:
	u16 gap = 10;
public:
	TTagLineVarSize(std::string caption, std::string tag, TLabelInitStructure init, int elementLeft);
	virtual void view() override;
	void setLeftSide(u16 left);
	void setGap(u16 gap);
};

