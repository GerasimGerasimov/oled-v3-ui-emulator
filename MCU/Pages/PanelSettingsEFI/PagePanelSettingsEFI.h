#pragma once
#include <PageBasicSettings.h>
class TPagePanelSettingsEFI : public TPageBasicSettings
{
public:
	TPagePanelSettingsEFI(std::string Name);
protected:
	void fillPageContainer(void) override;
};

