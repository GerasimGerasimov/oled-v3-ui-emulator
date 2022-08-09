#include "Router.h"
#include "PageMainMenu.h"
#include "PageCounters.h"
#include "PageEditValue.h"
#include "PageHome.h"
#include "PageHelp.h"

/*TODO переписать вызов страниц, ибо сейчас вызов остаётся в стеке и в итоге он закончится
Надо дать задание роутеру на переключение, и когда в новом Арр цикле дело дойдёт до роутера
он окроет нужную страницу
В роутере и страницах можно реализовать переходы на закрытие/открытие окна*/
TPage* TRouter::Page = NULL;
TPage* TRouter::BackPage = NULL;

std::map<std::string, TPage*> TRouter::Pages = std::map<std::string, TPage*>();

void TRouter::Init(void) {
    Pages["Home"] = new TPageHome("Home");
    Pages["Help"] = new TPageHelp("Home");
    Pages["MainMenu"] = new TPageMainMenu("MainMenu");
    Pages["Counters"] = new TPageCounters("Counters");
    Pages["EditValue"] = new TPageEditValue("EditValue");
    setActivePage("Home", NULL);
}

void TRouter::ProcessMessage(TMessage* m) {
};

TPage* TRouter::setActivePage(std::string PageName, void* props) {
    return (Pages.count(PageName))
        ? (BackPage = Page, Page = Pages[PageName], Page->setProps(props), Page)
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