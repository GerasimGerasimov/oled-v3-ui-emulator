#include "HandleSubscribers.h"

std::map<std::string, std::map<std::string, std::function<void(bool)>>> HandlerSubscribers::Handlers = {};

void HandlerSubscribers::set(std::string source, std::function<void(bool)>) {
	/*TDOD source это строка типа "U1/RAM/" еЄ надо распарсить и добавить в Handlers
	  чтобы получилось
	  U1--
	     |-RAM--
		       |-function*/
	/*TODO » вернуть bool чтои что бы знать что добавилось или нет*/
}

void HandlerSubscribers::remove(std::string source) {
	/*TODO удалить обработчик "U1/RAM/" из Handlers*/
}

void HandlerSubscribers::send(/*TODO аргумент "U1/RAM/"*/) {
	//найти все обработчики соответсвующие аргументу "U1/RAM/" и последовательно вызвать их
}