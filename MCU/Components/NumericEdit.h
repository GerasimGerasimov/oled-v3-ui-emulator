#ifndef NUMERIC_EDIT_H
#define NUMERIC_EDIT_H

#include <string>
#include "common.h"
#include "graphics.h"
#include "Label.h"
#include <array>

typedef struct {
    char c;
    bool sig;
} TCharSignificance;

class TNumericEdit : public TVisualObject {
public:
    virtual void view(void);//������� ������ �� ������
    virtual const u16 getHeight(void);
    void setCaption(std::string caption);
    bool ProcessMessage(TMessage* m);
    TTextSizes getSize(void);
    TNumericEdit(TLabelInitStructure init);//�����������
    ~TNumericEdit();//����������
protected:
    std::string Font;
    std::string Caption;
    TTextSizes TextSize;
    TColorScheme PrimaryColor; //�������� �������� ����� 
    TColorScheme SelectedColor;//�������� ����� ��� ���������
    int Style;
    void fillBackGround(TColorScheme& ColorScheme);
    void outCaption(TColorScheme& ColorScheme);
    void blinkCursor(void);
    void shiftCursorLeft(void);
    void shiftCursorRight(void);
    int Position;//����� �� ��� ����� �� �������, ���� �� ����� �������, ������������� �� ��� ������� �����
    std::array<TCharSignificance,4> Integers;
    std::array<TCharSignificance, 2> Fractions;
};

#endif