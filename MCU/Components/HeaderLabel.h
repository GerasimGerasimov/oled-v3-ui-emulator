#ifndef HEADER_LABEL_H
#define HEADER_LABEL_H

#include <string>
#include "Label.h"
#include "graphics.h"

//������ ������
class THeaderLabel : public TLabel {
public:
    virtual void view(void);//������� ������ �� ������
    THeaderLabel(TLabelInitStructure init);//�����������
    ~THeaderLabel();//����������
};

#endif