#include "HandleSubscribers.h"
#include <parser.h>

std::map<std::string, std::map<std::string, std::list<TSubscriber>>> HandlerSubscribers::Handlers = {};

int HandlerSubscribers::set(std::string source, std::function<void(TSlotHandlerArsg)> handler) {
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
	int id = (int)&handler;
	TSubscriber subscriber = {id, handler};
	Handlers[dev][section].push_back(subscriber);
	return id;
}

/*TODO ������� �� Source "U1/RAM/" ���������� Handler*/
void HandlerSubscribers::remove(std::string source, int& ID) {
	std::vector<std::string> v = IniParser::getListOfDelimitedString(
		(const char)'/',
		(char*)source.c_str(),
		source.size());
	std::string dev = v[0];
	std::string section = v[1];
	if (Handlers.count(dev)) {
		std::map<std::string, std::list<TSubscriber>>& sections = Handlers.at(dev);//����� ������
		if (sections.count(section)) {
			std::list<TSubscriber> & subscribers = sections[section];
			if (subscribers.size()) {
				std::list<TSubscriber>::iterator it = subscribers.begin();
				for (auto& s : subscribers) {
					if (s.id == ID) {
						subscribers.erase(it);
						ID = 0;
						break;
					};
					it++;
				}
			}
		}
	}
}

void HandlerSubscribers::send(Slot* slot /*TODO �������� "U1/RAM/"*/) {
	//����� ��� ����������� �������������� ��������� "U1/RAM/" � ��������������� ������� ��
	if (Handlers.count(slot->Device)) {
		std::map<std::string, std::list<TSubscriber>>& sections = Handlers.at(slot->Device);
		if (sections.count(slot->Section)) {
			std::list<TSubscriber>& subscribers = sections.at(slot->Section);
				for (auto& subscriber : subscribers) {
					TSlotHandlerArsg args = { &slot->InputBuf[0], slot->InputBufValidBytes, slot->StartAddrOffset, slot->LastAddrOffset };
					subscriber.handler(args);
				}
		}
	}
}