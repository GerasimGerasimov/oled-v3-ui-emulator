#ifndef T_ROUTER_H
#define T_ROUTER_H

#include <map>
#include "Pages.h"
#include "stm32f4xx.h"
#include "msg.h"

class TRouter {
public:
    static void ProcessMessage(TMessage* m);
    static void Init(void);
    TRouter();
    ~TRouter();
    static TPage* setActivePage(std::string PageName);
    static void setBackPage(std::string url);
    static TPage* goBack();
    static TPage* Page;
    static TPage* BackPage;
private:
    static std::map<std::string, TPage*> Pages;
};

#endif