#include "Pages.h"
void TPage::view() {
}

void TPage::clear() {

}

bool TPage::ProcessMessage(TMessage* m) {//���������� ���������
	return false;
}

void TPage::setProps(void* _props) {
	props = _props;
	isOpen = true;
	onOpen();
}

void TPage::onOpen() {
	
}

void TPage::onClose() {
	
}

TPage::TPage(std::string name)
	:TComponentsContainer()
	,isOpen(false)
	,Name(name)
	,BackPage("")
	,props(NULL){
}

TPage::TPage(std::string name, bool isOpenState, std::vector <TVisualObject*> Source)
	: TComponentsContainer(Source)
	, isOpen(isOpenState)
	, Name(name)
	, BackPage("")
	, props(NULL){
}

TPage::~TPage() {};//����������

void TPage::startToClose() {//���� ����� �������������� ��������, �� �� ������ ������� ������������ startToClose()
	                        //��� � ���� startToClose() ������� isOpen = false ����� ���������� ��������� ��������;
	onClose();
	isOpen = false;
}

bool TPage::isClosed() {
	return (bool)(isOpen == false);
}