#ifndef FIXED_FOOTER_H
#define FIXED_FOOTER_H

#include <string>
#include "Label.h"
#include "graphics.h"

//������ ������
class TFixedFooter : public TLabel {
public:
    virtual void view(void);//������� ������ �� ������
    TFixedFooter(TLabelInitStructure init);//�����������
    ~TFixedFooter();//����������
    TVisualObject* Owner;
};

#endif