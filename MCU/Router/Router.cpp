#include "Router.h"
#include "PageMainMenu.h"
#include "PageAlarms.h"
#include "PageEditValue.h"
#include "PageHome.h"
#include "PageHelp.h"
#include "PageWarnings.h"
//#include "PageOperateStatus.h"
//#include "PageBasicSettings.h"
//#include "PageBasicProtectionsSettings.h"
#include "PageSensors.h"
#include "SelfExc/PageSelfExc.h"
#include "PageParameterListEdit.h"
#include "ControlSettings/PageControlSettings.h"
#include "Ready/PageReady.h"
#include "Discretes/PageDIn.h"
#include "Discretes/TPageDOut.h"
#include "Converter/PageConverter.h"
#include "ReactivePower/PageReactivePower.h"
#include "CurrentLim/PageCurrentLim.h"
#include "VoltageLim/PageVoltageLim.h"
#include "PowerLim/PagePowerLim.h"
#include "InitExcitation/PageInitExcitation.h"
#include "ControlVoltageStator/PageControlVoltageStator.h"
//#include "RegulatorKoeff/PageRegulatorKoeff.h"
#include "InsulResist/PageInsulResist.h"
#include "PowerConverter/PagePowerConverter.h"
#include <IniResources.h>

/*TODO � ������� � ��������� ����� ����������� �������� �� ��������/�������� ����*/
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
    //Pages["BasicSettings"] = new TPageBasicSettings("BasicSettings"); //�������� ������
    Pages["SelfExc"] = new TPageSelfExc("SelfExc"); //���������������
    Pages["ControlSettings"] = new TPageControlSettings("ControlSettings"); //������� ���� ������
    Pages["EditValue"] = new TPageEditValue("EditValue");
    Pages["Ready"] = new TPageReady("Ready");//����������
    //Pages["OperateStatus"] = new TPageOperateStatus("OperateStatus"); //������ ������
    //Pages["BasicProtectionsSettings"] = new TPageBasicProtectionsSettings("BasicProtectionsSettings"); //������. �������� �������
    Pages["Sensors"] = new TPageSensors("Sensors"); //�������� ���������
    Pages["DIn"] = new TPageDIn("DIn"); //���������� �����
    Pages["DOut"] = new TPageDOut("DOut"); //���������� ������
    Pages["Converter"] = new TPageConverter("Converter"); //���������������
    Pages["PowerConverter"] = new TPagePowerConverter("PowerConverter"); //������� ���������������
    Pages["ReactivePower"] = new TPageReactivePower("ReactivePower"); //���������� ��������
    Pages["CurrentLim"] = new TPageCurrentLim("CurrentLim"); //������������ �����
    Pages["VoltageLim"] = new TPageVoltageLim("VoltageLim"); //������������ ����������
    Pages["PowerLim"] = new TPagePowerLim("PowerLim"); //������������ ��������
    Pages["InitExcitation"] = new TPageInitExcitation("InitExcitation"); //��������� �����������
    Pages["ControlVoltageStator"] = new TPageControlVoltageStator("ControlVoltageStator"); //�������� ���� �������
    //Pages["RegulatorKoeff"] = new TPageRegulatorKoeff("RegulatorKoeff"); //������������ ����������
    Pages["InsulResist"] = new TPageInsulResist("InsulResist"); //������������� ��������

    Pages["PrmListEdit"] = new TPageParameterListEdit("PrmListEdit");
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