#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"
#include <functional>
//#include "Delegate.hpp"


//������ ������
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string url, TLabelInitStructure init);//�����������
    ~TLinkLabel();//����������
    using type_one_arg_handler = std::function<void(int)>;
    type_one_arg_handler onEnterPressed;
private:
    std::string URL;
};

#endif