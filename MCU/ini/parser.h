#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>

enum class ParcerResult {
	COMMENT = -1,
	SECTION = -2,
	END     = -3
};

typedef struct {
	char* tag;
	int result;
} TSectionReadResult;

class IniParser  {
public:
	static void init(void);
	static bool setSectionToRead(char* SectionName);
	static TSectionReadResult getNextTagString();
	static void setRoot(char* root, int size);
private:
	static void resetFind(char* start);
	static char* getSectionEntryPoint(char* SectionName);
	static int getTagString(char** position);
	static int isDelimiter(char** ptr, char Delimiter);
	static int getStringLenght(char** ptr);
	static int getSectionLinesCount(char* SectionName);
	static char* Root;
	static char* SearchPointer;
	static int RootSize;
};

#endif