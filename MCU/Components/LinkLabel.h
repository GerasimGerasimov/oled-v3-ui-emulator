#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"


//строка текста
class TLinkLabel : public TLabel {
public:
    TLinkLabel(std::string url, TLabelInitStructure init);//конструктор
    ~TLinkLabel();//деструктор
private:
    std::string URL;
};

#endif