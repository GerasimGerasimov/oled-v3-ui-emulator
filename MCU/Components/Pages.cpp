#include "Pages.h"
void TPage::view() {
}

void TPage::clear() {

}

bool TPage::ProcessMessage(TMessage* m) {//обработчик сообщений
	return true;
}

TPage::TPage(std::string name)
	:TComponentsContainer(),
	isOpen(false) {
	Name = name;
	BackPage = "";
}

TPage::TPage(std::string name, bool isOpenState, std::vector <TVisualObject*> Source)
	: TComponentsContainer(Source),
	isOpen(isOpenState) {
	Name = name;
	BackPage = "";
}

TPage::~TPage() {};//деструктор