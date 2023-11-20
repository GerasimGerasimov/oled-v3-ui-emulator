#include "TagLineVarSize.h"

TTagLineVarSize::TTagLineVarSize(std::string caption, std::string tag, TLabelInitStructure init, int elementLeft = 0) : TTagLine(caption, tag, init) {
	ElementRect.Left = elementLeft;
}

void TTagLineVarSize::view() {
  Caption->inFocus = inFocus;
  Caption->ElementRect.Top = ElementRect.Top;
  Caption->ElementRect.Left = ElementRect.Left;
  Caption->view();//выводит Coption

  if (DataSrc) {
    Value->inFocus = inFocus;
    Value->ElementRect.Top = ElementRect.Top;
    Value->ElementRect.Left = ((Caption->getCaption() == "") ? ElementRect.Left : Caption->ElementRect.Left + Caption->ElementRect.Width + gap);//ElementRect.Left;
    Value->view();
  }

  if (DataSrc) {
    msu->setCaption(((TParameter*)DataSrc)->getMSU());
    msu->inFocus = inFocus;
    msu->ElementRect.Top = ElementRect.Top;
    msu->ElementRect.Left = Value->ElementRect.Left + Value->ElementRect.Width + gap;//ElementRect.Left;
    msu->view();
  }
}

void TTagLineVarSize::setLeftSide(u16 left) {
  ElementRect.Left = left;
}

void TTagLineVarSize::setGap(u16 newGap) {
  gap = newGap;
}
