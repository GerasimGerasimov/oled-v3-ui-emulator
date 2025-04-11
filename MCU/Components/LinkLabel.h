#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "ScrollLabel.h"
#include "Events.hpp"

//строка текста с горизонтальной автоматической прокруткой
class TLinkLabel : public TScrollLabel
{
public:
    virtual bool ProcessMessage(TMessage* m) override;
    TLinkLabel(std::string caption, std::string url, TLabelInitStructure init);//конструктор
    ~TLinkLabel();//деструктор
private:
    std::string URL;
};

#endif