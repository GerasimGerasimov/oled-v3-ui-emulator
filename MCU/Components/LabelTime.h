#pragma once

#include <Label.h>

class TLabelTime : public TLabel {
protected:

	void view() override;
private:
	void setTimeToHH_MM();
	std::string oldCaption = "";
public:
	TLabelTime(TLabelInitStructure init);
};

