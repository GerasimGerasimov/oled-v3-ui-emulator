#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>

class IniParser  {
public:
	static void init(void);
	static void setRoot(char* root, int size);
	static char* SearchSectionBegin(char* SectionName);
	static char* getNextTagString(char* sectionRoot);
private:
	static int isDelimiter(char** ptr, char Delimiter);
	static char* Root;
	static int RootSize;
};

#endif