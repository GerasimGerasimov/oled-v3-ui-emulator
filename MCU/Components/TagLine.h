#ifndef TAG_LINE_H
#define TAG_LINE_H

#include "common.h"
#include "Label.h"
#include "Events.hpp"
#include "parameters.h"

//������ ������
class TTagLine : public TVisualObject {
public:
    virtual bool ProcessMessage(TMessage* m);
    virtual const u16 getHeight(void);
    TTagLine(std::string tag, TLabelInitStructure init);//�����������
    ~TTagLine();//����������
    void view(void);//������� ������ �� ������
private:
    TParameter* DataSrc;
    TLabel* Caption;
    TLabel* Value;
    TLabel* msu;
};

#endif