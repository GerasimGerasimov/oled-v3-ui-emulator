#pragma once

#include <map>
#include <PageParameterListEdit.h>

//класс разобранное значение TPrmList отправляет для обработки TPageParameterListEditCMD
class TPageParameterListEditCMD : public TPageParameterListEdit
{
private:
	std::map<std::string, int> CMD;
public:
	TPageParameterListEditCMD(std::string Name);
	virtual void sendValue(void) override;
	virtual void fillPageContainer(void) override;
};

