#include "MainPage.h"
#include "resource.h"
#include <string> 
#include "display_driver.h"
#include "graphics.h"

HINSTANCE MainPage::hInst = NULL;                                // текущий экземпл€р
WCHAR MainPage::szTitle[MAX_LOADSTRING];                  // “екст строки заголовка
WCHAR MainPage::szWindowClass[MAX_LOADSTRING];            // им€ класса главного окна

HWND MainPage::hwndButton = NULL;
HWND MainPage::hwndKeyCodeText = NULL;
HWND MainPage::hwndDisplayEmulator = NULL;
HWND MainPage::hwndTimer = NULL;
UINT MainPage::IDT_TIMER1 = 0;

//
//  ‘”Ќ ÷»я: MyRegisterClass()
//
//  ÷≈Ћ№: –егистрирует класс окна.
//
ATOM MainPage::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
};

//
//   ‘”Ќ ÷»я: InitInstance(HINSTANCE, int)
//
//   ÷≈Ћ№: —охран€ет маркер экземпл€ра и создает главное окно
//
//    ќћћ≈Ќ“ј–»»:
//
//        ¬ этой функции маркер экземпл€ра сохран€етс€ в глобальной переменной, а также
//        создаетс€ и выводитс€ главное окно программы.
//
BOOL MainPage::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // —охранить маркер экземпл€ра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        480,
        248,
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    HWND hwndLedLnk = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"LNK",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        4,         // y position 
        32,        // Button width
        16,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    HWND hwndLedWrn = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"WRN",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10 + 32 + 4,         // x position 
        4,         // y position 
        32,        // Button width
        16,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    HWND hwndLedAlrm = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"ALR",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10 + 32 + 32 + 4 + 4,         // x position 
        4,         // y position 
        32,        // Button width
        16,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    hwndDisplayEmulator = CreateWindow(
        L"STATIC",  // Predefined class; Unicode assumed 
        L"",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER,  // Styles 
        10,         // x position 
        4+20,         // y position 
        128 * 2,        // Button width
        64 * 2,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    hwndButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"OK",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        138+20,         // y position 
        100,        // Button width
        24,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    hwndKeyCodeText = CreateWindow(
        L"STATIC",  // Predefined class; Unicode assumed 
        L"- - -",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER,  // Styles 
        166,         // x position 
        138+20,         // y position 
        100,        // Button width
        24,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    SetTimer(hWnd,             // handle to main window 
        IDT_TIMER1,            // timer identifier 
        1000,                 // 10-second interval 
        (TIMERPROC)MyTimerProc);     // no timer callback 

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

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
    std::wstring s = std::to_wstring(COUNT);
    SetWindowText(hwndKeyCodeText, (LPCWSTR)s.c_str()); // выводим результат в статическое поле
}


u16 out_128_64() {
    u16 count = 0;
    TPixel p = { 0, 0, 0 };
    for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 128; x++) {
            p.x = x;
            p.y = y;
            TGrahics::setPixel(p);
            count++;
        }
    }
    return count;
}

//
//  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ÷≈Ћ№: ќбрабатывает сообщени€ в главном окне.
//
//  WM_COMMAND  - обработать меню приложени€
//  WM_PAINT    - ќтрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернутьс€
//
//
LRESULT CALLBACK MainPage::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    u16 x = 0;
    switch (message)
    {
    case WM_CREATE:
        //out_128_64();
        //TGrahics::Line(0, 0, 127, 63, 1);
        TGrahics::putChar(0x0de, x,  0, 1);
        TGrahics::putChar(0x0be, x, 0, 1);
        TGrahics::outText("ѕривет!!123", 0, 32, 1);
        break;
    case WM_COMMAND:
    {
        if (lParam == (LPARAM)hwndButton) {
            //обработка нажати€ кнопки
            MessageBox(hWnd, (LPCWSTR)L"You pressed my button", (LPCWSTR)L"MessageBox", MB_OK | MB_ICONWARNING);
            return 0;
        }

        int wmId = LOWORD(wParam);
        // –азобрать выбор в меню:
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
            PAINTSTRUCT ps_dem;
            HDC hdc_dem = BeginPaint(hwndDisplayEmulator, &ps_dem);
                TDisplayDriver::setDC(hdc_dem);
                TDisplayDriver::out();

                EndPaint(hwndDisplayEmulator, &ps_dem);
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

// ќбработчик сообщений дл€ окна "ќ программе".
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