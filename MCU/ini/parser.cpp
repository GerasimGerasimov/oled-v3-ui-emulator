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
//в качестве параметра, передаётся имя секции с квадратными скобками (например [RAM])
//!!! название секции передаётся в квадратных скобках! "[RAM]"
char* IniParser::SearchSectionBegin(char* SectionName) {
    char* ptr = (char*)strstr(Root, SectionName);
    if (ptr != 0) {
        ptr += strlen(SectionName);//если фраза есть в тексте, тогда добавляю длину секции
        //проверяю, есть ли #13#10 после фразы, и если есть, то добавляю смещение на их длину
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
    /*TODO в общем надо просто брать строку от начала до CRLN или [ или конца ресурса (дляну-то знаю)
    а далее смотреть её на предмет информативности
    - если CRLF - пропускать идти к следущей
    - если начинается с ";" то это камент - пропустить на дину камента
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
        /*TODO контроль размера ресурса! не должны выходить за его пределы
        надо останавливать поиск при выходе за заданный размер*/
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

//GetIniStringLenght сканит строку до нахождния CR или LN
//возвращает сколько символов насканил
//если это символы типа CR, LN возвращает ноль
//если EOF то "-1"
int IniParser::getStringLenght(char** ptr) {
    int res = 0;
    char c;
    do {
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
    } while (true);
    return res;
}



int IniParser::getSectionLinesCount(char* SectionName) {//возвращает кол-во строк в секции
    char* begin;
    char* ptr;
    int res = 0;//счётчик строк и результат работы функции
    int IniStrLenght;
    //1) находит секцию и переходит к следующей строке
    //2) считает строки заканчивающиеся на "#13#10" но имеющие длину отличную от "0"
    //3) заканчивает счёт, когда находит EOF #0
    ptr = SearchSectionBegin(SectionName);//получил адрес начала данных секции
    if (ptr != 0) {//секция найдена
        do {
            begin = ptr;
            IniStrLenght = getStringLenght(&ptr);
            if (IniStrLenght > 0) {//если символы в строке есть
            //то проверю не является ли она заголовком новой секции
            //т.е. первый символ "["
                if (*begin == '[') break;//если наткнулся на новую секцию то прекращаю поиск
                res++;//а так считаю что это полноценная строка
                           //(к стати не забываю что ";" это начала камента в ini)
            }
        } while (IniStrLenght != -1);
    };
    return res;
}