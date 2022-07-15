#ifndef LINKED_TAG_LABEL_H
#define LINKED_TAG_LABEL_H

#include "LinkLabel.h"
#include "Events.hpp"
#include "signal.h"

//������ ������
class TLinkedTagLabel : public TLinkLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkedTagLabel(std::string tag, TLabelInitStructure init);//�����������
    ~TLinkedTagLabel();//����������
    void view(void);//������� ������ �� ������
private:
    ISignal* DataSrc;
};

#endif