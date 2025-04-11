#pragma once

#include "Label.h"

class TScrollLabel : public TLabel
{
private:
    static const int BEFORE_PAUSE = 15;
    static const int AFTER_PAUSE = 10;
    static const int SHIFT_DELAY = 4;

    enum class AnimationStage
    {
        WAIT_BEFORE_SHIFTING,
        SHIFTING,
        WAIT_AFTER_SHIFTING,
    };

    struct Vars
    {
        std::string shifted = "";
        int Delay = BEFORE_PAUSE;
        AnimationStage Stage = AnimationStage::WAIT_BEFORE_SHIFTING;
    };

    std::string SrcCaption;
    int Shift;
    Vars LabelVars;
    void doShift();
public:
    TScrollLabel(std::string caption, TLabelInitStructure init);
    virtual bool ProcessMessage(TMessage* m);
    void setSrcCaption(std::string caption);
};

