#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>

class IniParser  {
public:
	static void init(void);
	static void setRoot(char* root, int size);
	static char* SearchSectionBegin(char* SectionName);
	static void resetFind(char* start);
	static int getTagString(char* position);
	static int getSectionLinesCount(char* SectionName);
private:
	static int isDelimiter(char** ptr, char Delimiter);
	static int getStringLenght(char** ptr);
	static char* Root;
	static char* SearchPointer;
	static int RootSize;
};

#endif