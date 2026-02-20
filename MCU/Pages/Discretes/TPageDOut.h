#pragma once

#include "PageInOut.h"
class TPageDOut :  public TPageInOut
{
public:
	TPageDOut(std::string Name);
protected:
	virtual void fillPageContainer() override;
};

