#include "common.h"
//�a����� ����� ���������� ��������
TVisualObject::TVisualObject() {};

TVisualObject::TVisualObject(TVisualObjectInitStructure props)
	: inFocus(props.focused)
    , ElementRect(props.Rect) {

}

TVisualObject::~TVisualObject() {};

std::vector<TVisualObject*> TVisualObject::getFocusedElements() {
	std::vector<TVisualObject*> res = {};
	return res;
};