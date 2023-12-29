#pragma once

#include <Label.h>

//класс отображает параметр время в формате ЧЧ:ММ
class TLabelTime : public TLabel {
protected:

	void view() override;
private:
	void setTimeToHH_MM();
	std::string oldCaption = "";
public:
	TLabelTime(TLabelInitStructure init);
};

