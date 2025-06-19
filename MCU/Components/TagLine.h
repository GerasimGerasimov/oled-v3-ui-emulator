#ifndef TAG_LINE_H
#define TAG_LINE_H

#include "common.h"
#include "Label.h"
#include "Events.hpp"
#include "parameters.h"

//������ ������
class TTagLine : public TVisualObject {
public:
    virtual bool ProcessMessage(TMessage* m);
    virtual const u16 getHeight(void);
    TTagLine(std::string caption, std::string tag, TLabelInitStructure init);//�����������
    ~TTagLine();//����������
    void view(void);
    void setValueLeft(int step);
    void setMsuLeft(int step);

    //������� ������ �� ������
    TLabel* Value;
    const std::string Tag;
    const std::string ComponentName();
    virtual void update(const TSlotHandlerArsg& args, const char* format) override;
private:
    int valueLeft = 70;
    int msuLeft = 105;
protected:
    TLabel* Caption;
    TLabel* msu;
};

#endif