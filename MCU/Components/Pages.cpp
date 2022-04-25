#include "Pages.h"
void TPage::view() {
}

void TPage::clear() {

}

void TPage::ProcessMessage(TMessage* m) {//обработчик сообщений
}

TPage::TPage(bool isOpenState, std::vector <TVisualObject*> Source) 
	: TComponentsContainer(Source),
	isOpen(isOpenState) {
}

TPage::~TPage() {};//деструктор