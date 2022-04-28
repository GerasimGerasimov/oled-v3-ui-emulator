#include "Pages.h"
void TPage::view() {
}

void TPage::clear() {

}

void TPage::ProcessMessage(TMessage* m) {//обработчик сообщений
}

TPage::TPage(std::string name)
	:TComponentsContainer(),
	isOpen(false) {
	Name = name;
}

TPage::TPage(std::string name, bool isOpenState, std::vector <TVisualObject*> Source)
	: TComponentsContainer(Source),
	isOpen(isOpenState) {
	Name = name;
}

TPage::~TPage() {};//деструктор