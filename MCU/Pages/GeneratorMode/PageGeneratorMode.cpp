#include "PageGeneratorMode.h"
#include "TagLine.h"
#include "FixedHeader.h"

TPageGeneratorMode::TPageGeneratorMode(std::string Name) : TPageBasicSettings(Name){
    TLabelInitStructure LabelInitH;
    LabelInitH.pOwner = Container;
    LabelInitH.caption = "Генераторный режим";
    TFixedHeader* pHeader = new TFixedHeader(LabelInitH);
    delete Container->List[0];
    Container->List[0] = pHeader;
}
