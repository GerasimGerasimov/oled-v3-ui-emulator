#include "parser.h"

char* IniParser::Root = NULL;
int IniParser::RootSize = 0;
char* IniParser::SearchPointer = NULL;

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

void IniParser::resetFind(char* start) {
    SearchPointer =  start;
}

static bool isValidTagString(char* begin, int len) {
    return (bool)(*begin == 'p');
}

static bool isComment(char* begin) {
    return (bool)(*begin == ';');
}

static bool isSection(char* begin) {
    return (bool) (*begin == '[');
}

int IniParser::getTagString(char** position) {
    /*TODO � ����� ���� ������ ����� ������ �� ������ �� CRLN ��� [ ��� ����� ������� (�����-�� ����)
    � ����� �������� � �� ������� ���������������
    - ���� CRLF - ���������� ���� � ��������
    - ���� ���������� � ";" �� ��� ������ - ���������� �� ���� �������
    */
    char* begin = SearchPointer;
    char* end   = SearchPointer;
    do {
        int len = getStringLenght(&end);
        SearchPointer = end;
        if (len > 0) {
            if (isValidTagString(begin, len)) { (*position) = begin;  return len; };
            if (isComment(begin)) { (*position) = NULL;  return -1; };
            if (isSection(begin)) { (*position) = NULL;  return -2; };
        }
        /*TODO �������� ������� �������! �� ������ �������� �� ��� �������
        ���� ������������� ����� ��� ������ �� �������� ������*/
        begin = end;
    } while (true);
}

bool isNexSymbolValid(char** ptr) {
    char* c = *ptr;
    return (bool)(*c == '\n');
}

/*
int skipComment(char** ptr) {
    char* start = *ptr;
    char c;
    int i = 0;
    do {
        c = *((*ptr)++);
        switch (c) {
            case '\r': //CR (������� �������)
                if (isNexSymbolValid(ptr)) (*ptr)++;
                i = (int)(*&ptr[0] - &start[0]);
                return i;
            case '\n': //LN (����� ������)
                i = (int)(*&ptr[0] - &start[0]);
                return i;
        }
    } while (true);
}*/

//GetIniStringLenght ������ ������ �� ��������� CR ��� LN
//���������� ������� �������� ��������
//���� ��� ������� ���� CR, LN ���������� ����
//���� EOF �� "-1"
int IniParser::getStringLenght(char** ptr) {
    int res = 0;
    char c;
    do {
        c = *((*ptr)++);
        switch (c) {
        case '\r': //CR (������� �������)
            if (isNexSymbolValid(ptr)) (*ptr)++;
            return res;
        case '\n': //LN (����� ������)
            return(res);
        default:
            res++;//���������� ���-�� �������� � ������
            break;
        }
    } while (true);
    return res;
}



int IniParser::getSectionLinesCount(char* SectionName) {//���������� ���-�� ����� � ������
    char* begin;
    char* ptr;
    int res = 0;//������� ����� � ��������� ������ �������
    int IniStrLenght;
    //1) ������� ������ � ��������� � ��������� ������
    //2) ������� ������ ��������������� �� "#13#10" �� ������� ����� �������� �� "0"
    //3) ����������� ����, ����� ������� EOF #0
    ptr = SearchSectionBegin(SectionName);//������� ����� ������ ������ ������
    if (ptr != 0) {//������ �������
        do {
            begin = ptr;
            IniStrLenght = getStringLenght(&ptr);
            if (IniStrLenght > 0) {//���� ������� � ������ ����
            //�� ������� �� �������� �� ��� ���������� ����� ������
            //�.�. ������ ������ "["
                if (*begin == '[') break;//���� ��������� �� ����� ������ �� ��������� �����
                res++;//� ��� ������ ��� ��� ����������� ������
                           //(� ����� �� ������� ��� ";" ��� ������ ������� � ini)
            }
        } while (IniStrLenght != -1);
    };
    return res;
}