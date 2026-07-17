#pragma once
#include <TagLine.h>
class TTagCosLine : public TTagLine {
private:
    std::string calculateCos(const std::string& angleStr);
    TLabel* divider1;
    TLabel* divider2;

public:
    TTagCosLine(std::string caption, std::string tag, TLabelInitStructure init);
    virtual void update(const TSlotHandlerArsg& args, const char* format) override;
    virtual void view(void) override;
};

