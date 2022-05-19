#include "parser.h"

char* IniParser::Root = NULL;
int IniParser::RootSize = 0;

void IniParser::init() {

}

void IniParser::setRoot(char* root, int size) {
    Root = root;
    RootSize = size;
}

//возвращает адрес символа следующего за закрывающей квадратной скобкой заданной секции из devece_ini
//в качестве параметра, передаЄтс€ им€ секции с квадратными скобками (например [RAM])
//!!! название секции передаЄтс€ в квадратных скобках! "[RAM]"
char* IniParser::SearchSectionBegin(char* SectionName) {
    char* ptr = (char*)strstr(Root, SectionName);
    if (ptr != 0) {
        ptr += strlen(SectionName);//если фраза есть в тексте, тогда добавл€ю длину секции
        //провер€ю, есть ли #13#10 после фразы, и если есть, то добавл€ю смещение на их длину
        if (*(ptr) == '\r') { ptr++; }//если CR (возврат каретки)
        if (*(ptr) == '\n') { ptr++; }//если LN (конец строки)
    }
    return ptr;
}

int IniParser::isDelimiter(char** ptr, char Delimiter) {
    int res = 0;
    char c;
    do {
        c = *((*ptr)++);
        switch (c) {
            case 0   : return(-1);//конец файла
            case '\r': return(-2);//CR (возврат каретки)
            case '\n': return(-3);//LN (конец строки)
            default: {
                res++;//inc смещение
                if (c == Delimiter) return(res);//возвр. номер заданного символа в строке
            }
        }
    } while (true);
    return(res);
}

char* IniParser::getNextTagString(char* sectionRoot) {
    return NULL;
}