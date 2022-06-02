#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>
#include <vector>

enum class ParcerResult {
	COMMENT = -1,
	SECTION = -2,
	END     = -3,
	NOTKEYVALUE = -4
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
	static std::vector<std::string> getListOfDelimitedSting(char delimiter, char* src, int size);
private:
	static void resetFind(char* start);
	static char* getSectionEntryPoint(char* SectionName);
	static int getTagString(char** position);
	static int isDelimiter(char** ptr, char Delimiter);
	static int getStringLenght(char** ptr);
	static int getSectionLinesCount(char* SectionName);
	static int isDelimimerSizeLimited(char delimiter, char*& src, int& size);
	static std::string getElement(char delimiter, char** ptr, int& size);
	static char* Root;
	static char* SearchPointer;
	static int RootSize;
};

#endif