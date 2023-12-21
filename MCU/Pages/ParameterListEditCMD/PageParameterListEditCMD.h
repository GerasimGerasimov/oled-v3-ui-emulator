#pragma once

#include <map>
#include <PageParameterListEdit.h>

class TPageParameterListEditCMD : public TPageParameterListEdit
{
private:
	std::map<std::string, int> CMD;
public:
	TPageParameterListEditCMD(std::string Name);
	virtual void sendValue(void) override;
};

