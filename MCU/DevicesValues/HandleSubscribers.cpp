#include "HandleSubscribers.h"
#include <parser.h>

std::map<std::string, std::map<std::string, std::vector<std::function<void(TSlotHandlerArsg)>>>> HandlerSubscribers::Handlers = {};

void HandlerSubscribers::set(std::string source, std::function<void(TSlotHandlerArsg)> handler) {
	/*source ��� ������ ���� "U1/RAM/" ��� � �������� � �������� � Handlers
	  ����� ����������
	  U1--
	     |-RAM--
		       |-function*/
	/*TODO � ������� bool ���� ��� �� ����� ��� ���������� ��� ���*/
	std::vector<std::string> v = IniParser::getListOfDelimitedString(
		(const char)'/',
		(char*)source.c_str(),
		source.size());
	std::string dev = v[0];
	std::string section = v[1];
	/*���� ��������� �� ���� � ��������� ������������*/
	Handlers[dev][section].push_back(handler);
}

void HandlerSubscribers::remove(std::string source) {
	/*TODO ������� ���������� "U1/RAM/" �� Handlers*/
}

void HandlerSubscribers::send(Slot& slot /*TODO �������� "U1/RAM/"*/) {
	//����� ��� ����������� �������������� ��������� "U1/RAM/" � ��������������� ������� ��
	if (Handlers.count(slot.Device)) {
		std::map<std::string, std::vector<std::function<void(TSlotHandlerArsg)>>> sections = Handlers.at(slot.Device);
		if (sections.count(slot.Section)) {
			std::vector<std::function<void(TSlotHandlerArsg)>> handlers = sections.at(slot.Section);
				for (auto& handler : handlers) {
					TSlotHandlerArsg args = { &slot.InputBuf[0], slot.InputBufValidBytes, slot.StartAddrOffset, slot.LastAddrOffset };
					handler(args);
				}
		}
	}
}