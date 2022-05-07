#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

#include "Router.h"
#include "msg.h"
#include "DevicePollManager.h"

void App::init(void) {
    TRouter::Init();
    DevicePollManager::init();
    Msg::send_message(REPAINT, 0, 0);
}

void App::run(void) {

    TMessage m;
    while (true) {
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