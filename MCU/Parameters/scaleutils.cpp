#include "scaleutils.h"
#include "vars.h"
#include "Utils.h"
#include "parser.h"
#include "IniResources.h"

float ScaleUtils::getScaleFromProps(const char* dev, const char* optional) {
	char* pScale = IniParser::getElementPtrByNumber(3, '/', (char*) optional);
	std::string s = IniParser::getElement('/', pScale);
	Utils::comma_to_dot((char*)s.c_str());
	float res = 1.0f;
	try {
		res = std::stof(s);
	}
	catch (...) {
		//����� ����, ������ ��� ������ �� ��������������� � float
		//�������� ��� ��� ����� �� ������ [vars] �� ����� ���� ����� � ������ DEV ��� ���������. 
		std::string val = getVarStrValueByKey(s, dev);
		Utils::comma_to_dot((char*)val.c_str());
		try {
			res = std::stof(val);
		}
		catch (...) {
			//TODO ��� ���� �����?!
		}

	};
	/*TODO ���� ������ ��� ���������� ���������������� �� float �� �� ���� ��������������*/
	/*TODO ���� �������� ����������, �� ������ ����� ������ � vars
		���� ������, �� ���� � ��������
			���� �������� ����������� ��� ���������� � float �� ���� ��������������
			���� �������� ����������, �� �������� ��� ������!, ���� ��� ������� � �� ���� ��������� ��������
				���� � ������ ��� ��������������� ��������, �� ��������� "1"
			*/
			/*TODO ���� �� ����� ������� �� ���������� ������� �������� ������������, �� ������� "1"*/
	return res;
}

std::string ScaleUtils::getVarStrValueByKey(std::string& key, const char* dev) {
	std::string _dev(dev);/*GIST �������������� char* � std::string*/
	std::string sval = IniResources::getScaleValueByKey(key, _dev);
	return sval;
}