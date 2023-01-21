#ifndef T_PAGE_PARAMETER_LIST_EDIT_H
#define T_PAGE_PARAMETER_LIST_EDIT_H

#include "Pages.h"
#include "TVerticalContainer.h"
#include <FixedHeader.h>
#include "parameters.h"
#include <Slot.h>

class TPageParameterListEdit : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    void sendValue(void);
    TPageParameterListEdit(std::string Name);
    ~TPageParameterListEdit();
private:
    TVerticalContainer* Container;
    TVerticalContainer* TagList;
    TFixedHeader* pHeader;
    void fillPageContainer(void);
    TParameter* p;
    std::string tag;
    bool isDataSent = false;
    void SlotUpdate(Slot& slot, u8* reply);
};

#endif