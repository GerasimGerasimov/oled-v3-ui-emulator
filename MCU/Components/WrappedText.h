#ifndef WRAPPED_TEXT_H
#define WRAPPED_TEXT_H

#include <string>
#include "common.h"
#include "graphics.h"
#include "Label.h"

//������ ������
class TWrappedText : public TVisualObject {
public:
    virtual bool ProcessMessage(TMessage* m);
    virtual void view(void);//������� text �� ������
    virtual const u16 getHeight(void);
    void setText(std::string text);//�������� ����� � ������ ������� � �����
    TTextSizes getSize(void);
    TWrappedText(TLabelInitStructure init);//�����������
    ~TWrappedText();//����������
private:
    std::string Font;
    std::vector<std::string> List;
    void outText();
    u16 GetViewObjectsCount();//���-�� �������� ����������� � ������ ���� �� FirstPosition �� ������� ����
    //u16 FocusLine;//������ ����������� � ������
    u16 FirstPosition;//������ ������������ ������ ������� �������� � ��
    u16 LastPosition; //��������� ������������ ������
    void goUp(void);
    void goDown(void);
};

#endif