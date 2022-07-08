#ifndef LINKED_TAG_LABEL_H
#define LINKED_TAG_LABEL_H

#include "LinkLabel.h"
#include "Events.hpp"

//строка текста
class TLinkedTagLabel : public TLinkLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkedTagLabel(std::string url, std::string tag, TLabelInitStructure init);//конструктор
    ~TLinkedTagLabel();//деструктор
private:
    std::string Tag;
};

#endif