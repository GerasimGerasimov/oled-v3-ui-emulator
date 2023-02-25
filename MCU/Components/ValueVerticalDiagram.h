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
    TValueVerticalDiagram(std::string caption, std::string tag, TLabelInitStructure init);//�����������
    ~TValueVerticalDiagram();//����������
    void view(void);//������� ������ �� ������
    TLabel* Value;
    const std::string Tag;
    const std::string ComponentName();
private:
    TLabel* Caption;
    TLabel* msu; 
};

#endif