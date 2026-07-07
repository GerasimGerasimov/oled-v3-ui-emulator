#include "os_resources.h"
#include "crc16.h"
#include <string.h>

u8* OSResources::res = NULL;

const u8* OSResources::getRes(void) {
    return res;
}

void OSResources::init() {
    // Получаем путь к исполняемому файлу
    wchar_t exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);

    // Обрезаем до папки с .exe
    wchar_t* lastSlash = wcsrchr(exePath, L'\\');
    if (lastSlash) {
        *lastSlash = L'\0';
    }

    // Ваш .exe лежит в ...\oled-v3-ui-emulator\x64\Debug\ (или Win32\Debug)
    // Поднимаемся на 2 уровня вверх до корня проекта
    wchar_t* secondSlash = wcsrchr(exePath, L'\\');
    if (secondSlash) {
        *secondSlash = L'\0';
    }

    // Формируем полный путь к res.bin
    wchar_t fullPath[MAX_PATH];
    swprintf(fullPath, MAX_PATH, L"%s\\Drivers\\Resources\\res.bin", exePath);

    // Открываем файл
    HANDLE fHandle = CreateFile(fullPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (fHandle != INVALID_HANDLE_VALUE) {
        DWORD FileSize = GetFileSize(fHandle, NULL);
        res = new u8[FileSize];
        DWORD BytesRead = 0;
        ReadFile(fHandle, res, FileSize, &BytesRead, NULL);
        CloseHandle(fHandle);
    }
}

