#ifndef TCOMPONENTS_CONTAINER_H
#define TCOMPONENTS_CONTAINER_H

#include <string>
#include <vector>
#include "common.h"
#include "stm32f4xx.h"
#include "msg.h"

class TComponentsContainer : public TVisualObject
{
  public:
    virtual void view(void) = 0;//������� ������ �� ������
    void Add(TVisualObject* pVisualObject);//�������� ������ � ������
    void AddList(std::vector <TVisualObject*> Source);//�������� ������ �������� � ������
    virtual void Clear(void);//������� ������
    virtual bool ProcessMessage(TMessage* m) = 0;
    TComponentsContainer(std::vector <TVisualObject*> Source = {});
    ~TComponentsContainer();
    const u16 ItemsCount() const;
    std::vector<TVisualObject*> getFocusedElements();
    std::vector <TVisualObject*> List;
};

#endif