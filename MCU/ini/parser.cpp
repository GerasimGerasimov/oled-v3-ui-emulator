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

void IniParser::resetFind(char* start) {
    SearchPointer =  start;
}

static bool isComment(char* begin) {
    return (bool)(*begin == ';');
}

static bool isSection(char* begin) {
    return (bool) (*begin == '[');
}

int IniParser::getTagString(char** position) {
    char* begin = SearchPointer;
    char* end   = SearchPointer;
    int len = 0;
    while ((len = getStringLenght(&end)) >=0) {
        SearchPointer = end;
        if (len > 0) {
            if (isComment(begin)) { (*position) = NULL;  return (int)ParcerResult::COMMENT; };
            if (isSection(begin)) { (*position) = NULL;  return (int)ParcerResult::SECTION; };
            (*position) = begin;  return len;
        }
        begin = end;
    };
    (*position) = NULL;  return (int)ParcerResult::END;
}

static bool isNexSymbolValid(char** ptr) {
    char* c = *ptr;
    return (bool)(*c == '\n');
}

//GetIniStringLenght сканит строку до нахождни€ CR или LN
//возвращает сколько символов насканил
//если это символы типа CR, LN возвращает ноль
//если EOF то (int)ParcerResult::END
int IniParser::getStringLenght(char** ptr) {
    int limitCounter = 0;
    int res = 0;
    char c;
    while (limitCounter = RootSize - (int)(*&ptr[0] - &Root[0])) {
        c = *((*ptr)++);
        switch (c) {
        case '\r': //CR (возврат каретки)
            if (isNexSymbolValid(ptr)) (*ptr)++;
            return res;
        case '\n': //LN (конец строки)
            return(res);
        default:
            res++;//увеличиваю кол-во символов в строке
            break;
        }
    };
    return (int)ParcerResult::END;
}

int IniParser::getSectionLinesCount(char* SectionName) {//возвращает кол-во строк в секции
    char* begin;
    char* ptr;
    int res = 0;//счЄтчик строк и результат работы функции
    int IniStrLenght;
    //1) находит секцию и переходит к следующей строке
    //2) считает строки заканчивающиес€ на "#13#10" но имеющие длину отличную от "0"
    //3) заканчивает счЄт, когда находит EOF #0
    ptr = SearchSectionBegin(SectionName);//получил адрес начала данных секции
    if (ptr != 0) {//секци€ найдена
        do {
            begin = ptr;
            IniStrLenght = getStringLenght(&ptr);
            if (IniStrLenght > 0) {//если символы в строке есть
            //то проверю не €вл€етс€ ли она заголовком новой секции
            //т.е. первый символ "["
                if (*begin == '[') break;//если наткнулс€ на новую секцию то прекращаю поиск
                res++;//а так считаю что это полноценна€ строка
                           //(к стати не забываю что ";" это начала камента в ini)
            }
        } while (IniStrLenght != -1);
    };
    return res;
}



/*
static bool isValidTagString(char* begin, int len) {
    return (bool)(*begin == 'p');
}*/

/*
int skipComment(char** ptr) {
    char* start = *ptr;
    char c;
    int i = 0;
    do {
        c = *((*ptr)++);
        switch (c) {
            case '\r': //CR (возврат каретки)
                if (isNexSymbolValid(ptr)) (*ptr)++;
                i = (int)(*&ptr[0] - &start[0]);
                return i;
            case '\n': //LN (конец строки)
                i = (int)(*&ptr[0] - &start[0]);
                return i;
        }
    } while (true);
}*/