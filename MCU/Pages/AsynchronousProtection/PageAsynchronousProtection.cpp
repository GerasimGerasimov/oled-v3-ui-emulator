#include "PageAsynchronousProtection.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>

TPageAsynchronousProtection::TPageAsynchronousProtection(std::string Name) : TPageControlSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Асинхр. ход";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageAsynchronousProtection::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 105 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/RAM/AsyncRun/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Istat/", LabelInit),
        new TTagLineScrollCaptionComment("U1/RAM/Iq/", LabelInit),
        new TTagLineScrollCaption("Отключение Асинхронного хода по реактивному току статора", "U1/FLASH/IstQMaxFlt/", LabelInit),
        new TTagLineScrollCaption("Отключение Перегруза Статора по полному току статора", "U1/FLASH/IstSMaxFlt/", LabelInit),

        });

    dynamic_cast<TTagLine*>(TagList->List[0])->setValueLeft(105);
    dynamic_cast<TTagLine*>(TagList->List[0])->setMsuLeft(115);
}