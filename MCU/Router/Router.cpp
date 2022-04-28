#include "Router.h"

TPage* pActivePage = NULL;

void TRouter::Init(void) {

}

void TRouter::ProcessMessage(TMessage* m) {
    //for (auto& element : List) {
    //    element->ProcessMessage(m);
    //}
};

TRouter::TRouter() {

}

/*
TRouter::TRouter(std::vector <TVisualObject*> Source)
	: TComponentsContainer(Source) {
}
*/
TRouter::~TRouter() {};//деструктор