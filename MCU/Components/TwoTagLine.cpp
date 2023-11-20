#include "IniResources.h"
#include "TwoTagLine.h"
#include "TagLineVarSize.h"


TTwoTagLine::TTwoTagLine(std::string caption1, std::string tag1, TLabelInitStructure init1, std::string caption2, std::string tag2, TLabelInitStructure init2) {
	firstTag = new TTagLine(caption1, tag1, init1);
	secondTag = new TTagLine(caption2, tag2, init2);
}

TTwoTagLine::TTwoTagLine(TTagLine* tag1, TTagLine* tag2)  {
	firstTag = tag1;
	secondTag = tag2;
	
}

TTwoTagLine::~TTwoTagLine() {
	if (firstTag) {
		delete firstTag;
	}
	if (secondTag) {
		delete secondTag;
	}
}

void TTwoTagLine::view() {
	firstTag->view();
	secondTag->view();
}

const u16 TTwoTagLine::getHeight() {
	u16 height = (firstTag->getHeight() > secondTag->getHeight()) ? firstTag->getHeight() : secondTag->getHeight();
	return height;
}

void TTwoTagLine::update(const TSlotHandlerArsg& args, const char* format) {
	firstTag->update(args, format);
	secondTag->update(args, format);
}

void TTwoTagLine::setLeftFirstTag(u16 left) {
	static_cast<TTagLineVarSize*>(firstTag)->setLeftSide(left);
}

void TTwoTagLine::setLeftSecondTag(u16 left) {
	static_cast<TTagLineVarSize*>(secondTag)->setLeftSide(left);
}
