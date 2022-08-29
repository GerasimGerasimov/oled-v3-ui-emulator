#ifndef T_PAGE_EDIT_VALUE_H
#define T_PAGE_EDIT_VALUE_H

#include "Pages.h"
#include "TComponentListVertical.h"
#include "LinkLabel.h"
#include "HeaderLabel.h"
#include "WrappedText.h"
#include "NumericEdit.h"

class TPageEditValue : public TPage
{
public:
    virtual void view();//вывести объект на экране
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void clear();//очистит список
    bool ProcessMessage(TMessage* m);//обработчик сообщений
    TPageEditValue(std::string Name);//конструктор
    ~TPageEditValue();//деструктор
private:
    TComponentListVertical* MainMenu;
    THeaderLabel* pHeader;
    //TWrappedText* pText;
    TNumericEdit* pEdit;
    TNumericEdit* pEdit1;
};

#endif