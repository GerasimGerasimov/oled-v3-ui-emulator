#include "SetValueSelector.h"
#include "IniResources.h"

/*������ ����� ����������� �� ���������� ������ ��, ��� �� ������� ���������
���� �� ������� ���������, ����� ���������� ModbusSlave::setValue,
���� �� ���������� ������ �� �� ������ �������
� ������������ ��� ����� tag
���� �������� ��������� "SLF" ������ ������ ��*/
bool SetValueSelector::setValue(std::string& tag, std::string& value, TSlotDataHandler callback) {
	const TValueSearchStruct Info = IniResources::spliceTagInfo(tag);
	if (Info.device == "SLF") {
		return SetValueSelector::setInternalValue(tag, value);
	}
	else {
		return ModbusSlave::setValue(tag, value, callback);
	}
}

bool SetValueSelector::setInternalValue(std::string& tag, std::string& value) {
	const TValueSearchStruct Info = IniResources::spliceTagInfo(tag);
	//��� ������� ��� ��� SLF
	return false;
}