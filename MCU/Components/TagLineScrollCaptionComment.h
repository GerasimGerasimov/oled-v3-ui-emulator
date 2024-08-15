#pragma once

#include "TagLineScrollCaption.h"

//класс TTagLine с автоматической прокруткой текста, текст из комментария .ini файла
class TTagLineScrollCaptionComment : public TTagLineScrollCaption
{
public:
	TTagLineScrollCaptionComment(std::string tag, TLabelInitStructure init);
};

