#include "Pages.h"
void TPage::view() {
}

void TPage::clear() {

}

void TPage::ProcessMessage(TMessage* m) {//���������� ���������
}

TPage::TPage(bool isOpenState, std::vector <TVisualObject*> Source) 
	: TComponentsContainer(Source),
	isOpen(isOpenState) {
}

TPage::~TPage() {};//����������