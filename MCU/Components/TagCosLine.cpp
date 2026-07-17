#include "TagCosLine.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

std::string TTagCosLine::calculateCos(const std::string& angleStr) {
    if (angleStr.empty() || angleStr == "**.**") {
        return "**.**";
    }
    char* endptr = nullptr;
    float valFloat = std::strtof(angleStr.c_str(), &endptr);
    if (endptr == angleStr.c_str()) {
        return "**.**";
    }
    float radians = valFloat * static_cast<float>(M_PI / 180.0);
    float cosValue = cosf(radians);

    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.2f", cosValue);
    return std::string(buffer);
}

TTagCosLine::TTagCosLine(std::string caption, std::string tag, TLabelInitStructure init)
    : TTagLine(caption, tag, init)
{
    Value->setCaption("**.**");
    msu->setCaption(" ");

}

 void TTagCosLine::update(const TSlotHandlerArsg& args, const char* format)  {
    if (DataSrc != nullptr) {
        TParameter* p = static_cast<TParameter*>(DataSrc);

        std::string rawAngleValue = p->getValue(args, "");

        std::string cosValue = calculateCos(rawAngleValue);

        Value->setCaption(cosValue);
        msu->setCaption(" ");
    }
}
 void TTagCosLine::view(void) {
     Caption->inFocus = inFocus;
     Caption->ElementRect.Top = ElementRect.Top;
     Caption->ElementRect.Left = ElementRect.Left;
     Caption->view();


     u16 yStart = ElementRect.Top;
    u16 yEnd = ElementRect.Top + 16;

    if (DataSrc) {/*TODO 2-˜ ˜˜˜ ˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜*/

        u16 x1 = 69;
        u16 y = ElementRect.Top;
        u16 line1_x = 69;
        TGrahics::Line(line1_x, yStart, line1_x, yEnd, 1);
        // Âàøà íèçêîóðîâíåâàÿ ôóíêöèÿ âûâîäà òåêñòà, íàïðèìåð:
        // LCD_DrawText(x1, y, "|", Color);
        Value->inFocus = inFocus;
        Value->ElementRect.Top = ElementRect.Top;
        Value->ElementRect.Left = 70;//ElementRect.Left;
        Value->view();
    }

    if (DataSrc) {/*TODO 2-˜ ˜˜˜ ˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜*/
        
        u16 line2_x = 103;
        TGrahics::Line(line2_x, yStart, line2_x, yEnd, 1);
        msu->setCaption(" ");
        msu->inFocus = inFocus;
        msu->ElementRect.Top = ElementRect.Top;
        msu->ElementRect.Left = 105;//ElementRect.Left;
        msu->view();
    }
 }