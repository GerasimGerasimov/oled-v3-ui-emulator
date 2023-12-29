#pragma once

#include "TagLine.h"

//класс TTagLine с автоматической прокруткой Caption
class TTagLineScrollCaption : public TTagLine
{
private:

public:
	TTagLineScrollCaption(std::string caption, std::string tag, TLabelInitStructure init);
	virtual bool ProcessMessage(TMessage* m) override;
};

