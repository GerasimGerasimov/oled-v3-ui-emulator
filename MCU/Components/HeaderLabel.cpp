#include "HeaderLabel.h"

//����� "������ ������"
void  THeaderLabel::view(void) {//������� ������ �� ������
    TTextSizes tsizes = getSize();
    TFillRect rect{ ElementRect.Left, ElementRect.Top, tsizes.width, tsizes.height, 1 };
    TGraphics::fillRect(rect);
    s16 Left = (ElementRect.Width - TextSize.width) / 2;
    s16 Top = ElementRect.Top;
    TGraphics::outText(Caption, Left, Top, 0, Font);
}

THeaderLabel::THeaderLabel(TLabelInitStructure init)
    : TLabel(init) {
    isSkipped = true;
}

THeaderLabel::~THeaderLabel() {//����������
}
