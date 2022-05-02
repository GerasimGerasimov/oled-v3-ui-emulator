#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"
#include "Events.hpp"

//������ ������
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string url, TLabelInitStructure init);//�����������
    ~TLinkLabel();//����������
    TEventHandler onEnterPressed;
private:
    std::string URL;
};

#endif