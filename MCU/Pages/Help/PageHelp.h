#ifndef T_PAGE_HELP_H
#define T_PAGE_HELP_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "Label.h"
#include "WrappedText.h"

class TPageHelp : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void clear();
    bool ProcessMessage(TMessage* m);
    TPageHelp(std::string Name);
    ~TPageHelp();
private:
    TComponentListVertical* MainMenu;
    TLabel* pHeader;
    TWrappedText* pText;
};

#endif