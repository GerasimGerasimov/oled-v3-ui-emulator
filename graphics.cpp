#include "graphics.h"
#include <iostream>

HANDLE TGrahics::console = NULL;
HDC TGrahics::dc = NULL;
HBRUSH TGrahics::brush = NULL;

void TGrahics::console_init() {
	HWND hwnd = GetConsoleWindow();
	//RECT rect = { 100, 100, 640, 480 };
	//MoveWindow(hwnd, rect.left, rect.top, rect.right, rect.bottom, TRUE);

	HANDLE cns = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	set_console(cns);
	brush = CreateSolidBrush(RGB(0, 255, 0)); // Создаём кисть определённого стиля и цвета

	dc = GetDC(hwnd); //Цепляемся к консольному окну
}

void TGrahics::set_console(HANDLE dest_console) {
	console = dest_console;
};

HANDLE TGrahics::get_console() {
	return console;
};

void TGrahics::outText(TTextProps& props, std::string s) {
	COORD start = { props.left, props.top};
	::SetConsoleTextAttribute(console, props.color | (props.foreground << 4));
	::SetConsoleCursorPosition(console, start);
	std::cout << s;
};

void TGrahics::fillRect(TFillRect& props) {
	COORD start = { props.left, props.top };
	::SetConsoleTextAttribute(console, props.color << 4);
	::SetConsoleCursorPosition(console, start);
	std::string s = std::string(20, ' ');
	std::cout << s;
};

void TGrahics::setPixel(TPixel& props) {
	SelectObject(dc, brush); //Выбираем кисть
	//Rectangle(dc, props.left, props.top, props.left+1, props.top+1);
	SetPixel(dc, props.x, props.y, RGB(0, 255, 0));
	/*
	COORD start = { props.left, props.top };
	::SetConsoleTextAttribute(console, props.color << 4);
	::SetConsoleCursorPosition(console, start);
	std::cout << '*';
	*/
}

void TGrahics::rect() {
	SelectObject(dc, brush); //Выбираем кисть
	Rectangle(dc, 10, 100 , 10+128, 100+64);
	Rectangle(dc, 200, 100, 200+128, 100+64);
}