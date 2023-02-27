#ifndef VALUE_VERTICAL_DIAGRAM_H
#define VALUE_VERTICAL_DIAGRAM_H

#include "common.h"
#include "Label.h"
#include "Events.hpp"
#include "parameters.h"

//������ ������
class TValueVerticalDiagram : public TVisualObject {
public:
    virtual bool ProcessMessage(TMessage* m);
    virtual const u16 getHeight(void);
    TValueVerticalDiagram(std::string name, std::string tag);//�����������
    ~TValueVerticalDiagram();//����������
    void view(void);//������� ������ �� ������
    TLabel* Name;
    TLabel* Value;
    TLabel* Ref;
    const std::string Tag;
    const std::string ComponentName();

};

#endif