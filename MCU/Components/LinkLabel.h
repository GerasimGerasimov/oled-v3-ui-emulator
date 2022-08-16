#ifndef LINK_LABEL_H
#define LINK_LABEL_H

#include "Label.h"
#include "Events.hpp"

//Так как меню показываеттлько одно то не делать в каждом объекте свои строки и счётчики
// а сделать одни переменные на всех
static const int RETURN_PAUSE = 10;

struct  {
    std::string shifted;
    int Shift;
    int ReturnPause;
} TLinkLabelVars = {"", 0, RETURN_PAUSE};

// 
//строка текста
class TLinkLabel : public TLabel {
public:
    virtual bool ProcessMessage(TMessage* m);
    TLinkLabel(std::string caption, std::string url, TLabelInitStructure init);//конструктор
    ~TLinkLabel();//деструктор
private:
    std::string URL;
    std::string SrcCaption;
    void doShift(void);
};

#endif