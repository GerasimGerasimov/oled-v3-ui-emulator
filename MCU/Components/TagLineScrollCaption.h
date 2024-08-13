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

/*
	„то бы текст не уходил до последней буквы необходимо указать TLabelInitStructure.Rect.Width лоину отображаемого текста
	„то бы текст не перекрывал последующие элементы необходимо указать TLabelInitStructure.style = LabelsStyle::WIDTH_FIXED
*/