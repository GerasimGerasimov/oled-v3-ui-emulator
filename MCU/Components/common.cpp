#include "common.h"
//бaзовый класс визуальных объектов
TVisualObject::TVisualObject() {};

TVisualObject::TVisualObject(TVisualObjectInitStructure props)
	: inFocus(props.focused)
    , ElementRect(props.Rect) {

}

TVisualObject::~TVisualObject() {};