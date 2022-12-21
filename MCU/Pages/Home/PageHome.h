#ifndef T_PAGE_HOME_H
#define T_PAGE_HOME_H

#include "Pages.h"
#include "TVerticalContainer.h"
#include "TagLine.h"
#include "HandleSubscribers.h"

typedef struct {
    ISignal* signal;
    TVisualObject* element;
} TSignalOnFocus;

class TPageHome : public TPage
{
public:
    virtual void view();//������� ������ �� ������
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);//���������� ���������
    TPageHome(std::string Name);//�����������
    ~TPageHome();//����������
private:
    TVerticalContainer* MainMenu;
    TTagLine* pLTagUref;
    TTagLine* pLTagIref;
    TTagLine* pLTagUoutAve;
    TTagLine* pLTagIoutAve;
    TTagLine* pLTagSparkFrq;
    TTagLine* pLTagOut;
    //TLinkedTagLabel* pLTagIinAve;
    void goToTagInfoPage(int a);
    void SlotU1RAMUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
};

#endif