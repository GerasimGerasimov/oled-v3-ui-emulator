#pragma once

#include "common.h"
#include "Label.h"

class TTagLine;

class TTwoTagLine : public TVisualObject
{
private:
	TTagLine* firstTag;
	TTagLine* secondTag;
public:
	TTwoTagLine(std::string caption1, std::string tag1, TLabelInitStructure init1, std::string caption2, std::string tag2, TLabelInitStructure init2);
	TTwoTagLine(TTagLine* tag1, TTagLine* tag2);
	~TTwoTagLine();
	virtual void view() override;
	virtual const u16 getHeight() override;
	virtual void update(const TSlotHandlerArsg& args, const char* format) override;
	void setLeftFirstTag(u16 left);
	void setLeftSecondTag(u16 left);
};

