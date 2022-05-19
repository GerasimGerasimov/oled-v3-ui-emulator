#include "parser.h"

char* IniParser::Root = NULL;
int IniParser::RootSize = 0;

void IniParser::init() {

}

void IniParser::setRoot(char* root, int size) {
    Root = root;
    RootSize = size;
}

//���������� ����� ������� ���������� �� ����������� ���������� ������� �������� ������ �� devece_ini
//� �������� ���������, ��������� ��� ������ � ����������� �������� (�������� [RAM])
//!!! �������� ������ ��������� � ���������� �������! "[RAM]"
char* IniParser::SearchSectionBegin(char* SectionName) {
    char* ptr = (char*)strstr(Root, SectionName);
    if (ptr != 0) {
        ptr += strlen(SectionName);//���� ����� ���� � ������, ����� �������� ����� ������
        //��������, ���� �� #13#10 ����� �����, � ���� ����, �� �������� �������� �� �� �����
        if (*(ptr) == '\r') { ptr++; }//���� CR (������� �������)
        if (*(ptr) == '\n') { ptr++; }//���� LN (����� ������)
    }
    return ptr;
}

int IniParser::isDelimiter(char** ptr, char Delimiter) {
    int res = 0;
    char c;
    do {
        c = *((*ptr)++);
        switch (c) {
            case 0   : return(-1);//����� �����
            case '\r': return(-2);//CR (������� �������)
            case '\n': return(-3);//LN (����� ������)
            default: {
                res++;//inc ��������
                if (c == Delimiter) return(res);//�����. ����� ��������� ������� � ������
            }
        }
    } while (true);
    return(res);
}

char* IniParser::getNextTagString(char* sectionRoot) {
    return NULL;
}