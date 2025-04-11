#include "ScrollLabel.h"

void TScrollLabel::doShift(){
    if(inFocus){
    /*дл€ элементов в фокусе, прокрутку влево надписей который не вмещаютс€ на экран.
     ак только тер€ет фокус, вернутьс€ к отображению с первой буквы.
    ≈сли в фокусе, и достиг последненг символа, то пауза,
    после паузы быстрый сдвиг вправо до первой буквы, пауза,
    медленный сдвиг влево.*/
        switch(LabelVars.Stage){
        case AnimationStage::WAIT_BEFORE_SHIFTING:
            if(LabelVars.Delay){
                LabelVars.Delay--;
            }
            else{
                LabelVars.Delay = 0;
                LabelVars.Stage = AnimationStage::SHIFTING;
            }
            break;
        case AnimationStage::SHIFTING:
            (LabelVars.Delay)
                ? (LabelVars.Delay--)
                : (LabelVars.Delay = SHIFT_DELAY);
            LabelVars.shifted = SrcCaption.substr(Shift);
            TextSize = TMCUFonts::getTextSizes(Caption, Font);
            if(TextSize.width > ElementRect.Width){
                Shift++;
                Caption = LabelVars.shifted;
            }
            else{
                if(Shift != 0){
                    LabelVars.Delay = AFTER_PAUSE;
                    LabelVars.Stage = AnimationStage::WAIT_AFTER_SHIFTING;
                }
            }
            break;
        case AnimationStage::WAIT_AFTER_SHIFTING:
            (LabelVars.Delay)
                ? (LabelVars.Delay--)
                : (LabelVars.Delay = BEFORE_PAUSE,
                    LabelVars.Stage = AnimationStage::WAIT_BEFORE_SHIFTING,
                    Caption = SrcCaption,
                    Shift = 0);
            break;

        }
    }
    else{
        if(Caption != SrcCaption){
            setCaption(SrcCaption);
            Shift = 0;
            LabelVars.Delay = BEFORE_PAUSE;
            LabelVars.Stage = AnimationStage::WAIT_BEFORE_SHIFTING;
        }
    }
}

TScrollLabel::TScrollLabel(std::string caption, TLabelInitStructure init) : TLabel(init){
    SrcCaption = caption;
    Shift = 0;
    Caption = caption;
}

bool TScrollLabel::ProcessMessage(TMessage* m){
    switch(m->Event){
    case (u32)EventSrc::TIMER:
        doShift();
        break;
    }
    return false;
}

void TScrollLabel::setSrcCaption(std::string caption){
    SrcCaption = caption;
}
