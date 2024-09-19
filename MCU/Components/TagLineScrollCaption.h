#pragma once

#include "TagLine.h"

//����� TTagLine � �������������� ���������� Caption
class TTagLineScrollCaption : public TTagLine
{
private:

public:
	TTagLineScrollCaption(std::string caption, std::string tag, TLabelInitStructure init);
	virtual bool ProcessMessage(TMessage* m) override;
};

/*
	��� �� ����� �� ������ �� ��������� ����� ���������� ������� TLabelInitStructure.Rect.Width ����� ������������� ������
	��� �� ����� �� ���������� ����������� �������� ���������� ������� TLabelInitStructure.style = LabelsStyle::WIDTH_FIXED
*/