#include "PageUPP.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>


TPageUPP::TPageUPP(std::string Name) : TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Работа с УПП";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}

void TPageUPP::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLineScrollCaptionComment("U1/FLASH/SSPSelect/", LabelInit),
        new TTagLineScrollCaption("Время срабатывания защиты обрыва поля", "U1/FLASH/SSPFieldFailTime/", LabelInit),
        new TTagLineScrollCaption("Ток при включении РВВ-возбуждение", "U1/FLASH/SSPIExcRef/", LabelInit),
        new TTagLineScrollCaption("Ток при включении РВФ-форсировка", "U1/FLASH/SSPIExcFrc/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/SSPDropTime/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/SSPADCK/", LabelInit),
        new TTagLineScrollCaptionComment("U1/FLASH/SSPADCT/", LabelInit),

        });

}
