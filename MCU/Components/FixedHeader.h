#ifndef FIXED_HEADER_H
#define FIXED_HEADER_H

#include <string>
#include "Label.h"
#include "graphics.h"

//������ ������
class TFixedHeader : public TLabel {
public:
    virtual void view(void);//������� ������ �� ������
    TFixedHeader(TLabelInitStructure init);//�����������
    ~TFixedHeader();//����������
    TVisualObject* Owner;
};

#endif