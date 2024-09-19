#include "Router.h"
#include "PageMainMenu.h"
#include "PageAlarms.h"
#include "PageEditValue.h"
#include "PageHome.h"
#include "PageHelp.h"
#include "PageWarnings.h"
#include "PageOperateStatus.h"
#include "PageBasicSettings.h"
#include "PageCleanSettings.h"
#include "PageNetworkSettings.h"
#include "PageParameterListEdit.h"
#include "Discretes/PageDIn.h"
#include "Discretes/TPageDOut.h"
#include "RegulatorSettings/PageRegulatorSettings.h"
#include "ControlSettings/PageControlSettings.h"
#include "Excitation/PageExcitation.h"
#include "PowerSection/PagePowerSection.h"
#include "GeneratorMode/PageGeneratorMode.h"
#include "StatorCurrent/PageStatorCurrent.h"
#include "StatorVoltage/PageStatorVoltage.h"
#include "CurrentLimit/PageCurrentLimit.h"
#include "AutoMode/PageAutoMode.h"
#include "CosSetting/PageCosSetting.h"
#include "CurrentProtection/PageCurrentProtection.h"
#include "FieldBreak/PageFieldBreak.h"
#include "Sliding/PageSliding.h"
#include "Testing/PageTesting.h"

#include <IniResources.h>

/*TODO � ������� � ��������� ����� ����������� �������� �� ��������/�������� ����*/
TPage* TRouter::Page = nullptr;
TPage* TRouter::BackPage = nullptr;

TRouterTask TRouter::RouterTask = { false, "", nullptr };
TPageValueEditEntryData TRouter::PageValueEditEntryData = {"", ""};
std::map<std::string, TPage*> TRouter::Pages = std::map<std::string, TPage*>();

void TRouter::Init(void) {
    Pages["Home"] = new TPageHome("Home");//+ 1
    Pages["Help"] = new TPageHelp("Help");//+
    Pages["MainMenu"] = new TPageMainMenu("MainMenu");//+

    Pages["Alarms"] = new TPageAlarms("Alarms");//������+
    Pages["Warnings"] = new TPageWarnings("Warnings");//+

    Pages["DInput"] = new TPageDIn("DInput");//���������� �����+
    Pages["DOutput"] = new TPageDOut("DOutput");//���������� ������+

    Pages["EditValue"] = new TPageEditValue("EditValue");//+

    Pages["BasicSettings"] = new TPageBasicSettings("BasicSettings");//������� ����� + 2
    Pages["PowerSection"] = new TPagePowerSection("PowerSection");//������� ����� + 3
    Pages["GeneratorMode"] = new TPageGeneratorMode("GeneratorMode");//������������ ����� + 4
    Pages["StatorCurrent"] = new TPageStatorCurrent("StatorCurrent");//��� ������� + 5
    Pages["StatorVoltage"] = new TPageStatorVoltage("StatorVoltage");//���������� ������� + 6
    Pages["Excitation"] = new TPageExcitation("Excitation");//������ ����������� + 7
    Pages["ControlSettings"] = new TPageControlSettings("ControlSettings");//�������� �������� + 8
    Pages["CurrentLimit"] = new TPageCurrentLimit("CurrentLimit");//����������� ���� 9
    Pages["AutoMode"] = new TPageAutoMode("AutoMode"); //�������������� ����� 10
    Pages["CosSetting"] = new TPageCosSetting("CosSetting");//cos ��������� 11
    Pages["NetWorkSettings"] = new TPageNetworkSettings("NetWorkSettings");//��������� ����� + 12
    Pages["CurrentProtection"] = new TPageCurrentProtection("CurrentProtection");//������� ������ ����������� 13
    Pages["FieldBreak"] = new TPageFieldBreak("FieldBreak");//����� ���� 14
    Pages["RegulatorSettings"] = new TPageRegulatorSettings("RegulatorSettings");//��������� ���������� ���� + 15
    Pages["Sliding"] = new TPageSliding("Sliding");//���������� 16
    Pages["Testing"] = new TPageTesting("Testing");//����������� 17

    Pages["PrmListEdit"] = new TPageParameterListEdit("PrmListEdit");//+

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

TRouter::~TRouter() {};//����������