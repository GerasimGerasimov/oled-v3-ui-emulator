#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"
#include "Events.hpp"

//������ ������ � �������������� �������������� ����������
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string caption, std::string url, TLabelInitStructure init);//�����������
    ~TLinkLabel();//����������
private:
    std::string URL;
    std::string SrcCaption;
    int Shift;
    void doShift(void);
};

#endif