#pragma once

#include "PageInOut.h"

class TPageDIn : public TPageInOut
{
public:
    TPageDIn(std::string Name);
protected:
    virtual void fillPageContainer() override;
};

