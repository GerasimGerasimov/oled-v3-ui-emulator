#include "PageMainMenu.h"

void TPageMainMenu::view() {
};

void TPageMainMenu::clear() {
}

void TPageMainMenu::ProcessMessage(TMessage* m) {
};

TPageMainMenu::TPageMainMenu(bool isOpenState, std::vector <TVisualObject*> Source) 
	:TPage(isOpenState, Source) {
};

TPageMainMenu::~TPageMainMenu() {
};
