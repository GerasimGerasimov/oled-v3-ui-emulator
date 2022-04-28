#ifndef T_ROUTER_H
#define T_ROUTER_H

#include "TComponentsContainer.h"
#include "Pages.h"
#include "stm32f4xx.h"
#include "msg.h"

class TRouter : public TComponentsContainer
{
public:
    void view(void) {};
    const u16 getHeight(void) { return 0; };
    void ProcessMessage(TMessage* m);
    static void Init(void);
    TRouter();
    ~TRouter();
private:
    static TPage* pActivePage;
};

#endif