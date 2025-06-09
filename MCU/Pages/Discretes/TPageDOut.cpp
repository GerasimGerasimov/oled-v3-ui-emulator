#include "TPageDOut.h"
#include "TagLineScrollCaptionComment.h"
#include <FixedHeader.h>
#include "Router.h"
#include "TagLine.h"
#include <IniResources.h>

TPageDOut::TPageDOut(std::string Name) : TPageInOut(Name){
    
    TVerticalContainerProps props = { false };
    Container = new TVerticalContainer(props, {});

    TLabelInitStructure LabelInit;
    LabelInit.pOwner = Container;
    LabelInit.caption = "Дискретные выходы";
    TFixedHeader* pHeader = new TFixedHeader(LabelInit);
    Container->Add(pHeader);

    props = { true };
    TagList = new TVerticalContainer(props, {});
    TagList->ElementRect = { 0, 0,
                        (u16)(VIEW_PORT_MAX_HEIGHT - pHeader->getHeight() - 1),
                        VIEW_PORT_MAX_WIDTH };
    Container->Add(TagList);
    AddList({ TagList });
}

void TPageDOut::fillPageContainer()
{
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_FIXED;
    LabelInit.Rect = { 10, 10, 10, 80 };
    LabelInit.focused = false;
    TagList->AddList({
        new TTagLine("oAlarm", "U1/RAM/oAlarm/", LabelInit),
      // new TTagLineScrollCaptionComment("U1/RAM/oAlarm/", LabelInit),
        });
}
