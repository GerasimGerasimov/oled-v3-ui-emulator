#pragma once
#include "PageSensors.h"
class TPageOperationFlags : public TPageSensors
{
public:
    TPageOperationFlags(std::string Name);
   
protected:
    void fillPageContainer();
};

