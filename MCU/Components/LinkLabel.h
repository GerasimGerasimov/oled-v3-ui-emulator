#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"


//строка текста
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string url, TLabelInitStructure init);//конструктор
    ~TLinkLabel();//деструктор
protected:
    virtual bool onEnter(void);
private:
    std::string URL;
};

#endif