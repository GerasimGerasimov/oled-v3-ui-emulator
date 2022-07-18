#ifndef HANDLE_SUBSCRIBERS_H
#define HANDLE_SUBSCRIBERS_H

#include <string>
#include <map>
#include <functional>

class HandlerSubscribers {
public:
	static void set(std::string source, std::function<void(bool)>);
	static void remove(std::string source);
	static void send();

private:
	static std::map<std::string, std::map<std::string, std::function<void(bool)>>> Handlers;
};

#endif