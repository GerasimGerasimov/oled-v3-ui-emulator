#include "MainPage.h"
#include "resource.h"
#include <string> 
#include "display_driver.h"
#include "graphics.h"
#include "consolelog.h"

HINSTANCE MainPage::hInst = NULL;                                // текущий экземпляр
WCHAR MainPage::szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR MainPage::szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HWND MainPage::hWndMain = NULL;
HWND MainPage::hwndButton = NULL;
HWND MainPage::hwndKeyCodeText = NULL;
HWND MainPage::hwndDisplayEmulator = NULL;
HWND MainPage::hwndMemoLogger = NULL;
HWND MainPage::hwndTimer = NULL;
UINT MainPage::IDT_TIMER1 = 0;
bool MainPage::isHadlersFilled = false;

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MainPage::MyRegisterClass(HINSTANCE hInstance)
{
    TGrahics::init();
    
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra =  DLGWINDOWEXTRA;//0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = (LPCWSTR)L"MainWndClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
};

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL MainPage::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    hWndMain = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, (DLGPROC)WndProc);
    if (!hWndMain)
    {
        return FALSE;
    };

    SetTimer(hWndMain,             // handle to main window 
        IDT_TIMER1,            // timer identifier 
        1,                 // 10-second interval 
        (TIMERPROC)MyTimerProc);     // no timer callback 

    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);

    return TRUE;
}

static UINT COUNT = 0;
VOID CALLBACK MainPage::MyTimerProc(
    HWND hwnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{
    COUNT++;
    std::string scount = std::to_string(COUNT);

    TTextSizes tsize;
    tsize = TMCUFonts::getTextSizes(scount, "Verdana12");
    TGrahics::fillRect({ 10,36, tsize.width, tsize.height, 0 });
    TGrahics::outText(scount, 10, 36, 1, "Verdana12");

    tsize = TMCUFonts::getTextSizes(scount, "MSSansSerifBold14");
    TGrahics::fillRect({ 40,36, tsize.width, tsize.height, 1 });
    TGrahics::outText(scount, 40, 36, 0, "MSSansSerifBold14");

    updateEmulatorView();

    std::wstring s = std::to_wstring(COUNT) + L"Привет\n";
    console::log(s);
}


void MainPage::updateEmulatorView(void) {
    HDC hdc_dem = GetDC(hwndDisplayEmulator);
    TDisplayDriver::setDC(hdc_dem);
    TDisplayDriver::out();
    ReleaseDC(hwndDisplayEmulator, hdc_dem);
}

void MainPage::fillHandlersByID(void) {
    if (isHadlersFilled) return;
    hwndDisplayEmulator = GetDlgItem(hWndMain, ID_DISPLAY_EMULATOR);
    console::hwnd = hwndMemoLogger = GetDlgItem(hWndMain, ID_MEMO_LOGGER);
    isHadlersFilled = true;
}

//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
LRESULT CALLBACK MainPage::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    u16 x = 0;
    switch (message)
    {
    case WM_CREATE:
       
        break;
    case WM_SHOWWINDOW:
        fillHandlersByID();
        break;

    case WM_COMMAND:
    {
        if (lParam == (LPARAM)hwndButton) {
            //обработка нажатия кнопки
            MessageBox(hWnd, (LPCWSTR)L"You pressed my button", (LPCWSTR)L"MessageBox", MB_OK | MB_ICONWARNING);
            return 0;
        }

        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
            //PAINTSTRUCT ps_dem;
            //HDC hdc_dem = BeginPaint(hwndDisplayEmulator, &ps_dem);
            //    TDisplayDriver::setDC(hdc_dem);
            //    TDisplayDriver::out();
            //    EndPaint(hwndDisplayEmulator, &ps_dem);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK MainPage::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}