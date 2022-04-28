#ifndef T_ROUTER_H
#define T_ROUTER_H

#include "TComponentsContainer.h"
#include "Pages.h"
#include "stm32f4xx.h"
#include "msg.h"

class TRouter : public TComponentsContainer
{
public:
    TPage* pActivePage;
    TRouter(std::vector <TVisualObject*> Source = {});
    ~TRouter();
};

#endif