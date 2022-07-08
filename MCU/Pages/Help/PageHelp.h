#ifndef T_PAGE_HELP_H
#define T_PAGE_HELP_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkedTagLabel.h"

class TPageHelp : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void clear();
    bool ProcessMessage(TMessage* m);
    TPageHelp(std::string Name);
    ~TPageHelp();
private:
    TComponentListVertical* MainMenu;
    TLinkedTagLabel* pLTagUref;
    void goToTagInfoPage(int a);
};

#endif