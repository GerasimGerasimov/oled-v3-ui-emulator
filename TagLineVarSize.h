#pragma once

#include <TagLine.h>

class TTagLineVarSize : public TTagLine
{
private:

public:
	TTagLineVarSize(std::string caption, std::string tag, TLabelInitStructure init, int elementLeft);
	virtual void view() override;
};

