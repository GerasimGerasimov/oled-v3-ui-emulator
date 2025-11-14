#include "PageCommunicationSettings.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"

TPageCommunicationSettings::TPageCommunicationSettings(std::string Name) : TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Уставки времени";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageCommunicationSettings::fillPageContainer() {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("tOvrSt1", "U1/FLASH/tOvrSt1/", LabelInit),
        new TTagLine("tOvrSt2", "U1/FLASH/tOvrSt2/", LabelInit),
        new TTagLine("tOvrSt3", "U1/FLASH/tOvrSt3/", LabelInit),
        new TTagLine("tOvrSt4", "U1/FLASH/tOvrSt4/", LabelInit),
        new TTagLine("tAsym", "U1/FLASH/tAsym/", LabelInit),
        new TTagLine("tOutMin", "U1/FLASH/tOutMin/", LabelInit),
        new TTagLine("tOutMax", "U1/FLASH/tOutMax/", LabelInit),
        new TTagLine("tStartMax", "U1/FLASH/tStartMax/", LabelInit),
        new TTagLine("tContInMax", "U1/FLASH/tContInMax/", LabelInit),
        new TTagLine("tContBallMax", "U1/FLASH/tContBallMax/", LabelInit)

        });
}