#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"


//������ ������
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string url, TLabelInitStructure init);//�����������
    ~TLinkLabel();//����������
protected:
    virtual bool onEnter(void);
private:
    std::string URL;
};

#endif