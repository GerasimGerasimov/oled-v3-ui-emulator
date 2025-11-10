#pragma once
#include <PageBasicSettings.h>
class TPagePanelSettingsEFI : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
	TPagePanelSettingsEFI(std::string Name);
    ~TPagePanelSettingsEFI();
private:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    void fillPageContainer(void);
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
};

