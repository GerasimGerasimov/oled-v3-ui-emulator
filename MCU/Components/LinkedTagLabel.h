#ifndef LINKED_TAG_LABEL_H
#define LINKED_TAG_LABEL_H

#include "LinkLabel.h"
#include "Events.hpp"

//������ ������
class TLinkedTagLabel : public TLinkLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkedTagLabel(std::string url, std::string tag, TLabelInitStructure init);//�����������
    ~TLinkedTagLabel();//����������
private:
    std::string Tag;
};

#endif