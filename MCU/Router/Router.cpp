#include "PageAlarms.h"
#include "PageEditValue.h"
#include "PageHelp.h"
#include "PageHome.h"
#include "PageMainMenu.h"
#include "PageWarnings.h"
#include "Router.h"
//#include "PageOperateStatus.h"
#include "PageBasicSettings.h"
//#include "PageBasicProtectionsSettings.h"
#include "PageSensors.h"
#include "PageParameterListEdit.h"
#include "PowerSupply/TPagePowerSupply.h"
#include "Discretes/TPageDOut.h"
#include "Discretes/PageDIn.h"
#include <IniResources.h>

/*TODO В роутере и страницах можно реализовать переходы на закрытие/открытие окна*/
TPage* TRouter::Page = nullptr;
TPage* TRouter::BackPage = nullptr;

TRouterTask TRouter::RouterTask = { false, "", nullptr };
TPageValueEditEntryData TRouter::PageValueEditEntryData = {"", ""};
std::map<std::string, TPage*> TRouter::Pages = std::map<std::string, TPage*>();

void TRouter::Init(void) {
    Pages["Home"] = new TPageHome("Home");
    Pages["Help"] = new TPageHelp("Help");
    Pages["MainMenu"] = new TPageMainMenu("MainMenu");
    Pages["Alarms"] = new TPageAlarms("Alarms");
    Pages["Warnings"] = new TPageWarnings("Warnings");
    Pages["BasicSettings"] = new TPageBasicSettings("BasicSettings"); //Основные уставк
    Pages["EditValue"] = new TPageEditValue("EditValue");
    Pages["PowerSupply"] = new TPagePowerSupply("PowerSupply"); //Питание
    //Pages["OperateStatus"] = new TPageOperateStatus("OperateStatus"); //Статус работы
    //Pages["BasicProtectionsSettings"] = new TPageBasicProtectionsSettings("BasicProtectionsSettings"); //Защиты. Основные уставки
    Pages["Sensors"] = new TPageSensors("Sensors"); //Датчики
    Pages["PrmListEdit"] = new TPageParameterListEdit("PrmListEdit");
    Pages["DiscretesIn"] = new TPageDIn("DiscretesIn");//Дескретные входы
    Pages["DiscretesOut"] = new TPageDOut("DiscretesOut"); //Дескретные выходы
    setInitPage();
}

void TRouter::setTask(TRouterTask task) {
    RouterTask = task;
    RouterTask.isDone = false;
    if (Page) { Page->startToClose(); }
}

bool TRouter::chekNextPage() {
    return (RouterTask.isDone)
        ? false
        : changeToNextPage();
}

bool TRouter::changeToNextPage() {
    if (Page) {
        if (Page->isClosed()) {
            if (Pages.count(RouterTask.NextPage)) {
                BackPage = Page;
                Page = Pages[RouterTask.NextPage];
                Page->setProps(RouterTask.props);
                RouterTask.isDone = true;
                return true;
            }
        }
    }
    return false;
}

void TRouter::ProcessMessage(TMessage* m) {
};

void TRouter::setInitPage() {
    setActivePage("Home", nullptr);
    RouterTask.isDone = true;
}

TPage* TRouter::setActivePage(std::string PageName, void* props) {
    return (Pages.count(PageName))
        ? (BackPage = Page, Page = Pages[PageName], Page->setProps(props), Page)
        : (nullptr);
}

void TRouter::setBackPage(std::string url) {
    BackPage = Pages[url];
}

TPage* TRouter::goBack(void) {
    Page = BackPage;
    return Page;
}

/* TU8BIT, TU16bit, TS16bit, TFloat  - "EditValue"
   TPrmList - "PrmListEdit" */
static const std::map<std::string, std::string> EditPageNameBySignalType = {
    {"TU8BIT", "EditValue"},
    {"TU16bit", "EditValue"},
    {"TS16bit", "EditValue"},
    {"TFloat", "EditValue"},
    {"TPrmList", "PrmListEdit"},
};

const std::string TRouter::getEditPageNameBySignalType(const std::string& SignalType) {
    std::string s = (EditPageNameBySignalType.count(SignalType))
        ? EditPageNameBySignalType.at(SignalType)
        : "EditValue";
    return s;
}

const std::string TRouter::selectEditPage(std::string& tag) {
    ISignal* p = IniResources::getSignalByTag(tag);
    std::string SignalType = p->getSignalType();
    std::string PageName = getEditPageNameBySignalType(SignalType);
    return PageName;
}

const std::string TRouter::getBackPage() {
    std::string s = (Pages.count(PageValueEditEntryData.backPage))
        ? PageValueEditEntryData.backPage
        : "Home";
    return s;
}

TRouter::TRouter() {

}

TRouter::~TRouter() {};//деструктор