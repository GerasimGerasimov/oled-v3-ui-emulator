#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

#include "Router.h"
#include "msg.h"
#include "DevicePollManager.h"

#include "IniResources.h"
#include "IniSlotsprops.h"
#include "CreateSlotsByStart.h"
#include "resources.h"

void App::init(void) {
    TInternalResources::init();
    IniResources::init();
    IniSlotsProps::init();
    /*TODO ��� ����� ���� ��� ������, �� ������ �������� � �������� �� �����, ��� ��� ���������� ����� �������� �� �������*/
    /*TODO ��� ���������� �� ���������� DIO ����� ����*/
    DevicePollManager::init(CreateSlotsByStart::init(IniSlotsProps::Devices));
    TRouter::Init();
    Msg::send_message(REPAINT, 0, 0);
}

void App::run(void) {

    TMessage m;
    while (true) {
        TRouter::chekNextPage();
        if (Msg::get_message(&m)) {
            if (TRouter::Page) {
                TRouter::Page->ProcessMessage(&m);
                TRouter::Page->view();
            }
        }
        TDisplayDriver::out();
        DevicePollManager::execute();
    }
}