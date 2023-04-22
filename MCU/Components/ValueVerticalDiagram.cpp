#include "ValueVerticalDiagram.h"
#include "IniResources.h"

bool TValueRefVerticalDiagram::ProcessMessage(TMessage* m) {
    return false;
}

const std::string TValueRefVerticalDiagram::ComponentName() {
    return "TValueVerticalDiagram";
}

TValueRefVerticalDiagram::TValueRefVerticalDiagram(std::string caption, std::string tag)
    : Tag(tag) 
    , BarMaxHeight(0)
    , BarBearHeight(0)
    , BarNormalHeight(0)
    , RefPosition(30)
    , uValue(0)
    , uRef(50)
    , uMaxValue(100) {
    ElementRect = { 0, 0, 63, 54 };
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

TValueRefVerticalDiagram::~TValueRefVerticalDiagram() {
    delete Name;
    delete Value;
    delete Ref;
}

const u16 TValueRefVerticalDiagram::getHeight(void) {
    TTextSizes tsizes = Name->getSize();
    return tsizes.height;
}

void TValueRefVerticalDiagram::view(void) {
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
    //������ �����
    rect = { (s16)(ElementRect.Left), (s16)(ElementRect.Top) , (u16)(ElementRect.Width), (u16)(ElementRect.Height), 1 };
    TGraphics::Rect(rect);
    
    rect = { (s16)(ElementRect.Left + 40), (s16)(ElementRect.Top + 10) , 1, 42, 1 };
    TGraphics::fillRect(rect);
    rect = { (s16)(ElementRect.Left + 40 + 11), (s16)(ElementRect.Top + 10) , 1, 42, 1 };
    TGraphics::fillRect(rect);
    rect = { (s16)(ElementRect.Left + 40), (s16)(ElementRect.Top + 10) , 12, 1, 1 };
    TGraphics::fillRect(rect);

    /*TODO
    * ������������: uValue � uRef �� ������ ��������� uMaxValue
    *   ���� uValue �������� ��� ����� uMaxValue �� 
    *   ���� ���� ��������� ��������� �������� ������ (Filled-���������������)
    * ���� �� uValue ������ uMaxValue �� ��������� ����� ����������� �� ��� �������
    * 1) uValue ������ ��� ����� uRef, �����:
    *   ����������� ������ Dashed-�������������� ��� ����������� uValue � uMaxValue,
        � ������ Filled-�������������� = 0 (��� ���� ������ ��� �� ��������)
    * 2) uValue ������ uRef, �����:
    *   ������ Dashed-�������������� ����� ��������� uRef � uMaxValue, 
    *   � ������ Filled-�������������� ����� ��������� �������� (uValue - uRef) � uMaxValue.
    * ����������� �������, ������� ��������� uValue, uRef, uMaxValue �� ������
    * ����� ������ Filled � Dashed-�����������. 
    */
    /*TODO ������, ����� �������� 
    */
    //FillRect ���������� ��������� Value ��� Ref
    /*TODO ���� Value �� ��������� Ref �� ������ ������� �� ������������*/
    rect = { (s16)(ElementRect.Left + 40 + 2), (s16)(ElementRect.Top + 24) , 8, 6, 1 };
    TGraphics::fillRect(rect);

    //DashedFillRect ���������� ��������� Value ��� Ref
    rect = { (s16)(ElementRect.Left + 40 + 2), (s16)(ElementRect.Top + 30) , 8, 22, 1 };
    TGraphics::DashedfillRect(rect);

    //Dashed line ���������� ��������� Ref
    TGraphics::DashedLine((u8)(ElementRect.Left + 40 - 2), (s16)(ElementRect.Top + RefPosition),
        (u8)(ElementRect.Left + 40 + 14), (s16)(ElementRect.Top + RefPosition), 1);

}
