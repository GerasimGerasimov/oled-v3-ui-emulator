#include "graphics.h"
#include <iostream>

static HANDLE console = NULL;

void set_console(HANDLE dest_console) {
	console = dest_console;
};

void outText(TTextProps& props, std::string s) {
	COORD start = { props.left, props.top};
	::SetConsoleTextAttribute(console, props.color | (props.foreground << 4));
	::SetConsoleCursorPosition(console, start);
	std::cout << s;
};

void fillRect(TFillRect& props) {
	COORD start = { props.left, props.top };
	::SetConsoleTextAttribute(console, props.color << 4);
	::SetConsoleCursorPosition(console, start);
	std::string s = std::string(20, ' ');
	std::cout << s;
};
