#pragma once

#include <Pages.h>
#include "TVerticalContainer.h"

class Slot;

class TPageFactorySettingsEdit : public TPage
{
private:
    TVisualObject* getSignalOfFocusedChild();
    void sendSetting();
    void SlotUpdate(Slot* slot, u8* reply);
public:
    TPageFactorySettingsEdit(std::string Name);
    ~TPageFactorySettingsEdit();
    void onOpen() override;
    void view() override;
    bool ProcessMessage(TMessage* m) override;
    void startToClose() override;
protected:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    virtual void fillPageContainer();
};

