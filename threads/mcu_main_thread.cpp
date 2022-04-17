#include "mcu_main_thread.h"

#include <iostream>
#include <conio.h>
#include "app.h"
#include "msg.h"

static HANDLE hMCUMainThread = NULL;
static DWORD  dwMCUMainThreadId = 0;

DWORD WINAPI mcu_main_thread(LPVOID lpParam) {
    App::init();
    do {
        Sleep(1);
        App::run();
    } while (true);
}

void create_mcu_main_thread(void) {
    DWORD dwThrdParam = 1;
    hMCUMainThread = CreateThread(
        NULL,         // �������� ������������ �� ���������
        0,            // ������ ����� ������������ �� ���������
        mcu_main_thread,   // ������� ������
        &dwThrdParam, // �������� ������� ������
        0,            // ������ �������� ������������ �� ���������
        &dwMCUMainThreadId  // ���������� ������������� ������
    );
}

void close_mcu_main_thread(void) {
    if (hMCUMainThread != NULL) {
        CloseHandle(hMCUMainThread);
    }
}