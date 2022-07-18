#include "DevicesValuesHandler.h"
#include "HandleSubscribers.h"



void DevicesValuesHandler::setValues(Slot& slot) {
	HandlerSubscribers::send();
}

void DevicesValuesHandler::setDefault(Slot& slot) {
	/*TODO вызвать функции подписчиков*/
	HandlerSubscribers::send();
}