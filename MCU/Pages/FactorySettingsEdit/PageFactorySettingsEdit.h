#pragma once

#include <Pages.h>
#include "TVerticalContainer.h"

class TPageFactorySettingsEdit : public TPage
{
private:
    TVisualObject* getSignalOfFocusedChild();
    void sendSetting();
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

