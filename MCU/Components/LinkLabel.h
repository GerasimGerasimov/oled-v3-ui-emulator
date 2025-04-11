#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "ScrollLabel.h"
#include "Events.hpp"

//������ ������ � �������������� �������������� ����������
class TLinkLabel : public TScrollLabel
{
public:
    virtual bool ProcessMessage(TMessage* m) override;
    TLinkLabel(std::string caption, std::string url, TLabelInitStructure init);//�����������
    ~TLinkLabel();//����������
private:
    std::string URL;
};

#endif