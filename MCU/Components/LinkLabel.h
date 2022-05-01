#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"
#include <functional>
//#include "Delegate.hpp"


//строка текста
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string url, TLabelInitStructure init);//конструктор
    ~TLinkLabel();//деструктор
    using type_one_arg_handler = std::function<void(int)>;
    type_one_arg_handler onEnterPressed;
private:
    std::string URL;
};

#endif