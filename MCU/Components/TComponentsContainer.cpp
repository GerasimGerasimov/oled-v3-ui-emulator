#include "TComponentsContainer.h"

void TComponentsContainer::Add(TVisualObject* pVisualObject){//�������� ������ � ������
  List.push_back(pVisualObject);
}

void TComponentsContainer::AddList(std::vector <TVisualObject*> Source) {//�������� ������ �������� � ������
    List.assign(Source.begin(), Source.end());
}

void  TComponentsContainer::Clear(void){//������� ������
	for (auto& e : List) {
		delete e;
	}
  List.clear();
}

TComponentsContainer::TComponentsContainer(std::vector <TVisualObject*> Source) {//�����������
  AddList(Source);
}

const u16 TComponentsContainer::ItemsCount() const {
    return List.size();
}

TComponentsContainer::~TComponentsContainer() {
};

std::vector<TVisualObject*> TComponentsContainer::getFocusedElements() {
	std::vector<TVisualObject*> res = {};
	return res;
};