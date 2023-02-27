#include "ValueVerticalDiagram.h"
#include "IniResources.h"

bool TValueVerticalDiagram::ProcessMessage(TMessage* m) {
    return false;
}

const std::string TValueVerticalDiagram::ComponentName() {
    return "TValueVerticalDiagram";
}

TValueVerticalDiagram::TValueVerticalDiagram(std::string caption, std::string tag)
    : Tag(tag) {
    TLabelInitStructure init;
    init.style = LabelsStyle::WIDTH_DINAMIC;
    init.Rect = { 10, 10, 10, 10 };
    init.focused = false;

    init.font = "Verdana12";
    Name = new TLabel(init);

    init.font = "MSSansSerifBold14";
    Value = new TLabel(init);

    init.font = "Verdana12";
    Ref = new TLabel(init);

    Name->setCaption(caption);
    Value->setCaption("XXX.X");
    Ref->setCaption("XXX.X");
}

TValueVerticalDiagram::~TValueVerticalDiagram() {
    delete Name;
    delete Value;
    delete Ref;
}

const u16 TValueVerticalDiagram::getHeight(void) {
    TTextSizes tsizes = Name->getSize();
    return tsizes.height;
}

void TValueVerticalDiagram::view(void) {
    Name->inFocus = inFocus;
    Name->ElementRect.Top = ElementRect.Top;
    Name->ElementRect.Left = ElementRect.Left;
    Name->view();

    Value->inFocus = inFocus;
    Value->ElementRect.Top = ElementRect.Top + 50;
    Value->ElementRect.Left = ElementRect.Left;
    Value->view();

    Ref->inFocus = inFocus;
    Ref->ElementRect.Top = ElementRect.Top + 20;
    Ref->ElementRect.Left = ElementRect.Left;
    Ref->view();


    TFillRect rect;
    rect = { (s16)(ElementRect.Left + 40), (s16)(ElementRect.Top + 10) , 1, 42, 1 };
    TGraphics::fillRect(rect);
    rect = { (s16)(ElementRect.Left + 40 + 11), (s16)(ElementRect.Top + 10) , 1, 42, 1 };
    TGraphics::fillRect(rect);
    rect = { (s16)(ElementRect.Left + 40), (s16)(ElementRect.Top + 10) , 12, 1, 1 };
    TGraphics::fillRect(rect);

    //FillRect показывает положение Value над Ref
    rect = { (s16)(ElementRect.Left + 40 + 2), (s16)(ElementRect.Top + 24) , 8, 6, 1 };
    TGraphics::fillRect(rect);

    //DashedFillRect показывает положение Value под Ref
    rect = { (s16)(ElementRect.Left + 40 + 2), (s16)(ElementRect.Top + 30) , 8, 22, 1 };
    TGraphics::DashedfillRect(rect);

    //Dashed line показывает положение Ref
    TGraphics::DashedLine((u8)(ElementRect.Left + 40 - 2), (s16)(ElementRect.Top + 30),
        (u8)(ElementRect.Left + 40 + 14), (s16)(ElementRect.Top + 30), 1);

}
