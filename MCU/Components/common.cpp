#include "common.h"
//�a����� ����� ���������� ��������
TVisualObject::TVisualObject()
	: inFocus(false)
	, isSkipped(false)
	, ElementRect({0,0,0,0})
	, DataSrc(NULL) {
};

TVisualObject::TVisualObject(TVisualObjectInitStructure props)
	: inFocus(props.focused)
    , ElementRect(props.Rect)
	, DataSrc(NULL) {

}

TVisualObject::~TVisualObject() {};

TVisualObject* TVisualObject::getFocusedElement() {
	return NULL;
};

void* TVisualObject::getDataSrc() {
	return DataSrc;
}