#include "Router.h"
#include "PageMainMenu.h"
#include "PageCounters.h"
#include "PageEditValue.h"

TPage* TRouter::Page = NULL;
TPage* TRouter::BackPage = NULL;

std::map<std::string, TPage*> TRouter::Pages = std::map<std::string, TPage*>();

void TRouter::Init(void) {
    Pages["MainMenu"] = new TPageMainMenu("MainMenu");
    Pages["Counters"] = new TPageCounters("Counters");
    Pages["EditValue"] = new TPageEditValue("EditValue");
    setActivePage("MainMenu");
}

void TRouter::ProcessMessage(TMessage* m) {
};

TPage* TRouter::setActivePage(std::string PageName) {
    return (Pages.count(PageName))
        ? (BackPage = Page, Page = Pages[PageName])
        : (NULL);
}

void TRouter::setBackPage(std::string url) {
    BackPage = Pages[url];
}

TPage* TRouter::goBack(void) {
    Page = BackPage;
    return Page;
}

TRouter::TRouter() {

}

TRouter::~TRouter() {};//деструктор