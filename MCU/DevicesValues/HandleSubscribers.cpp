#include "HandleSubscribers.h"

std::map<std::string, std::map<std::string, std::function<void(bool)>>> HandlerSubscribers::Handlers = {};

void HandlerSubscribers::set(std::string source, std::function<void(bool)>) {
	/*TDOD source ��� ������ ���� "U1/RAM/" � ���� ���������� � �������� � Handlers
	  ����� ����������
	  U1--
	     |-RAM--
		       |-function*/
	/*TODO � ������� bool ���� ��� �� ����� ��� ���������� ��� ���*/
}

void HandlerSubscribers::remove(std::string source) {
	/*TODO ������� ���������� "U1/RAM/" �� Handlers*/
}

void HandlerSubscribers::send(/*TODO �������� "U1/RAM/"*/) {
	//����� ��� ����������� �������������� ��������� "U1/RAM/" � ��������������� ������� ��
}