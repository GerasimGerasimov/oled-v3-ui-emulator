#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"
#include "Events.hpp"

//��� ��� ���� ��������������� ���� �� �� ������ � ������ ������� ���� ������ � ��������
// � ������� ���� ���������� �� ����
static const int RETURN_PAUSE = 10;

struct  {
    std::string shifted;
    int Shift;
    int ReturnPause;
} TLinkLabelVars = {"", 0, RETURN_PAUSE};

// 
//������ ������
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string caption, std::string url, TLabelInitStructure init);//�����������
    ~TLinkLabel();//����������
private:
    std::string URL;
    std::string SrcCaption;
    void doShift(void);
};

#endif