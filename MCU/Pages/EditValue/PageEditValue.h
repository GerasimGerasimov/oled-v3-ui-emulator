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
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void clear();//������� ������
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageEditValue(std::string Name);//�����������
    ~TPageEditValue();//����������
private:
    TComponentListVertical* MainMenu;
    THeaderLabel* pHeader;
    //TWrappedText* pText;
    TNumericEdit* pEdit;
    TNumericEdit* pEdit1;
};

#endif