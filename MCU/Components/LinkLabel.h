#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"


//������ ������
class TLinkLabel : public TLabel {
public:
    virtual bool onEnter(void);
    TLinkLabel(std::string url, TLabelInitStructure init);//�����������
    ~TLinkLabel();//����������
private:
    std::string URL;
};

#endif