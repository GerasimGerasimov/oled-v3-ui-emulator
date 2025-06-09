#pragma once

#include "PageInOut.h"

class TPageDIn : public TPageInOut
{
public:
    TPageDIn(std::string Name);
    //void SlotUpdate(TSlotHandlerArsg args);
protected:
    virtual void fillPageContainer() override;
};

