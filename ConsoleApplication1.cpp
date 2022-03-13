// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// https://habr.com/ru/post/443406/
//

#include <iostream>
#include <thread>
#include <conio.h>
#include <mutex>
#include <windows.h>
#include <vector>
#include <string>
#include "stm32f4xx.h"
#include "msg.h"
#include "fonts.h"
#include "menu.h"
#include "graphics.h"

#define KEY_F1 49
#define KEY_F2 50
#define KEY_F3 51

#define KEY_ECS 27
#define KEY_OK 13

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

HANDLE console = NULL;

std::mutex mu;

static TMenu menu("", true, {});

void key_board_control() {
    int key = 0;
    do {
       key = _getch_nolock();
       mu.lock();
       SetConsoleTextAttribute(console, 15);// FOREGROUND_INTENSITY);
       COORD start = { 20, 0 };
       ::SetConsoleCursorPosition(console, start);
       std::cout <<"key:"<< key <<"\n";
       send_message(KEYBOARD, key, 0);
       mu.unlock();
    } while (key != 8);
    std::cout << "Leave the Thread!\n";
}

void timer_control() {
    u16 count = 0;
    while (true) {
        mu.lock();
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        COORD start = { 0, 0 };
        ::SetConsoleCursorPosition(console, start);
        std::cout << "time:" << count++ << "\n";
        mu.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


std::vector<std::string> Menu = std::vector<std::string>({"a","b","c"});

void outList() {
    COORD start = { 0, 2 };
    ::SetConsoleCursorPosition(console, start);
    for (const auto item : Menu) {
        SetConsoleTextAttribute(console, 11);
        std::cout << "item:" << item << "\n";
        start.Y++;
        ::SetConsoleCursorPosition(console, start);
    }
}

void runApp(TMessage* m) {
    menu.ProcessMessage(m);
    menu.View();
}

void processMessage() {
    TMessage m;
    while (true) {
        if (get_message(&m)) {
            mu.lock();
            SetConsoleTextAttribute(console, 10);
            COORD start = { 0, 1 };
            ::SetConsoleCursorPosition(console, start);
            std::cout << "msg:" << m.p1 << "\n";
            runApp(&m);
            mu.unlock();
        }
    }
}

int main()
{
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    set_console(console);
    menu.Top = 10;
    menu.AddList({  new TLabel("1-пункт меню номер один"),
                    new TMenu("Mеню", false, {
                        new TLabel("1-пункт вложенного меню номер один"),
                        new TLabel("2-пункт вложенного меню номер два")
                        }),
                    new TLabel("3-пункт меню номер три"),
                    new TLabel("4-пункт меню номер четыре"),
                    new TLabel("5-пункт меню номер пять"),
                    new TLabel("6-пункт меню номер шесть"),
                    new TLabel("7-пункт меню номер семь"),
                    new TLabel("8-пункт меню номер восемь"),
                    new TLabel("9-пункт меню номер девять"),
                    new TLabel("A-пункт меню номер десять"), });
    menu.View();
    std::thread key_control_thr(key_board_control);
    std::thread timer_control_thr(timer_control);
    std::thread proc_msg_thr(processMessage);
    key_control_thr.join();
    timer_control_thr.join();
    proc_msg_thr.join();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
