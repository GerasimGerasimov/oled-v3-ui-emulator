#include "TagLine.h"
#include "IniResources.h"

bool TTagLine::ProcessMessage(TMessage* m) {
    return false;
}

const std::string TTagLine::ComponentName() {
    return "TTagLine";
}

void TTagLine::update(const TSlotHandlerArsg& args, const char* format) {

    TParameter* p = static_cast<TParameter*>(DataSrc);
    Value->setCaption(p->getValue(args, ""));
}

TTagLine::TTagLine(std::string caption, std::string tag, TLabelInitStructure init)
    : Caption(new TLabel(init))
    , Value(new TLabel(init))
    , msu(new TLabel(init))
    , Tag(tag) {
    Caption->setCaption(caption);
    DataSrc = (TParameter*)IniResources::getSignalByTag(tag);
    Value->setCaption(((TParameter*)DataSrc)->getDefaultValue());
}
std::string TTagLine::getValue() {
    return Value->getCaption();
}

TTagLine::~TTagLine() {
    delete Caption;
    delete Value;
    delete msu;
}

const u16 TTagLine::getHeight(void) {
    TTextSizes tsizes = Caption->getSize();
    return tsizes.height;
}

void TTagLine::view(void) {
    Caption->inFocus = inFocus;
    Caption->ElementRect.Top = ElementRect.Top;
    Caption->ElementRect.Left = ElementRect.Left;
    Caption->view();//˜˜˜˜˜˜˜ Coption

    u16 yStart = ElementRect.Top;
    u16 yEnd = ElementRect.Top + 16;

    if (DataSrc) {/*TODO 2-˜ ˜˜˜ ˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜*/

        u16 x1 = valueLeft - 10;
        u16 y = ElementRect.Top;
        u16 line1_x = valueLeft - 1;
        TGrahics::Line(line1_x, yStart, line1_x, yEnd, 1);
        // Âàøà íèçêîóðîâíåâàÿ ôóíêöèÿ âûâîäà òåêñòà, íàïðèìåð:
        // LCD_DrawText(x1, y, "|", Color);
        Value->inFocus = inFocus;
        Value->ElementRect.Top = ElementRect.Top;
        Value->ElementRect.Left = valueLeft;//ElementRect.Left;
        Value->view();
    }

    if (DataSrc) {/*TODO 2-˜ ˜˜˜ ˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜*/
        
        u16 line2_x = msuLeft - 2;
        TGrahics::Line(line2_x, yStart, line2_x, yEnd, 1);
        msu->setCaption(((TParameter*)DataSrc)->getMSU());
        msu->inFocus = inFocus;
        msu->ElementRect.Top = ElementRect.Top;
        msu->ElementRect.Left = msuLeft;//ElementRect.Left;
        msu->view();
    }
}

void TTagLine::setValueLeft(int step) {
    valueLeft = step;
}

void TTagLine::setMsuLeft(int step) {
    msuLeft = step;
}