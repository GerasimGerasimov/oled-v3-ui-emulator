#include "utils.h"

/*
std::wstring s2ws(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}
*/

//swp_copy_u16( u8 *s, u16 *d, u8 c)
//���������� � ������������� ����
//u8  *s ����� ������ - ������ ����� �������� �������� ������
//u16 *d ����� ������ - ���� ����� ������ ������������ ������ (���� �� 2 �����)
//u8   c ���������� ����! ������� ���������� �����������
void swp_copy_u16(u8* s, u16* d, u8 c) {
    bauint w;
    while (c--) {
        //������ � �������
        w.b[1] = *s++;
        w.b[0] = *s++;
        *d++ = w.i;
    }
}