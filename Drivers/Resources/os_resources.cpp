#include "os_resources.h"
#include "crc16.h"
#include <string.h>

u8* OSResources::res = NULL;

const u8* OSResources::getRes(void) {
    return res;
}

void OSResources::init() {
    int fSuccess = 0;
    HANDLE fHandle = NULL;
    fHandle = CreateFile(L"C:\\Users\\info\\source\\repos\\WindowsProject1\\Drivers\\Resources\\res.bin", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (fHandle != INVALID_HANDLE_VALUE) {
        DWORD FileSize = 0;
        fSuccess = GetFileSize(fHandle, 0);
        FileSize = fSuccess;
        res = new u8[fSuccess];
        DWORD BytesRead = 0;
        fSuccess = ReadFile(fHandle, res, FileSize, &BytesRead, NULL);
        fSuccess = CloseHandle(fHandle);
    }
}

