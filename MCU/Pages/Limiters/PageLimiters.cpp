#include "PageLimiters.h"
#include "Router.h"
#include "TagLine.h"
#include "TagLineScrollCaptionComment.h"
#include <IniResources.h>
#include <FixedHeader.h>
#include "PageBasicSettings.h"


TPageLimiters::TPageLimiters(std::string Name) :TPageBasicSettings(Name) {
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Ограничители";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
};
void TPageLimiters::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;

    TagList->AddList({
        new TTagLine("fIzMin", "U1/FLASH/fIzMin/", LabelInit),
        new TTagLine("fIzMax", "U1/FLASH/fIzMax/", LabelInit),
        new TTagLine("Ti2tR", "U1/FLASH/Ti2tR/", LabelInit),
        new TTagLine("i2tOV_ON", "U1/FLASH/i2tOV_ON_R/", LabelInit),
        new TTagLine("i2tOV_OFF", "U1/FLASH/i2tOV_OFF_R/", LabelInit),
        new TTagLine("Iz_i2tR_lim", "U1/FLASH/Iz_i2t_R_limit/", LabelInit),
        new TTagLine("Amax", "U1/FLASH/Amax/", LabelInit),
        new TTagLine("Amin", "U1/FLASH/Amin/", LabelInit),
        });
}
