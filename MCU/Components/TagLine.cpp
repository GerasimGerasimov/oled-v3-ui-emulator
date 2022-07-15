#include "TagLine.h"
#include "IniResources.h"

bool TTagLine::ProcessMessage(TMessage* m) {
    return true;
}

TTagLine::TTagLine(std::string tag, TLabelInitStructure init)
    : Caption(new TLabel(init))
    , Value(new TLabel(init))
    , msu(new TLabel(init))
    , DataSrc(IniResources::getSignalByTag(tag)) {
}

TTagLine::~TTagLine() {//����������
}

const u16 TTagLine::getHeight(void) {
    TTextSizes tsizes = Caption->getSize();
    return tsizes.height;
}

void TTagLine::view(void) {
    Caption->inFocus = inFocus;
    Caption->ElementRect.Top = ElementRect.Top;
    Caption->ElementRect.Left = ElementRect.Left;
    Caption->view();//������� Coption

    /*TODO ���� ������� �������� ����*/
    Value->setCaption("9023.78");
    Value->inFocus = inFocus;
    Value->ElementRect.Top = ElementRect.Top;
    Value->ElementRect.Left = 55;//ElementRect.Left;
    Value->view();

    /*TODO ���� ������� ��.��� ����*/
    msu->setCaption("KVAr");
    msu->inFocus = inFocus;
    msu->ElementRect.Top = ElementRect.Top;
    msu->ElementRect.Left = 95;//ElementRect.Left;
    msu->view();
}
