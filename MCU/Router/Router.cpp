#include "Router.h"
#include "PageMainMenu.h"
#include "PageCounters.h"

TPage* TRouter::Page = NULL;
std::map<std::string, TPage*> TRouter::Pages = std::map<std::string, TPage*>();

void TRouter::Init(void) {
    Pages["MainMenu"] = new TPageMainMenu("MainMenu");
    Pages["Counters"] = new TPageCounters("Counters");
    setActivePage("MainMenu");
}

void TRouter::ProcessMessage(TMessage* m) {
};

TPage* TRouter::setActivePage(std::string PageName) {
    return (Pages.count(PageName))
        ? (Page = Pages[PageName])
        : (Page = NULL);
}

TRouter::TRouter() {

}

/*
TRouter::TRouter(std::vector <TVisualObject*> Source)
	: TComponentsContainer(Source) {
}
*/
TRouter::~TRouter() {};//деструктор