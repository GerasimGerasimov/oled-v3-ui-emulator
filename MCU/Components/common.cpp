#include "common.h"
//�a����� ����� ���������� ��������
TVisualObject::TVisualObject() {};

TVisualObject::TVisualObject(TVisualObjectInitStructure props)
	: inFocus(props.focused)
    , ElementRect(props.Rect) {

}

TVisualObject::~TVisualObject() {};