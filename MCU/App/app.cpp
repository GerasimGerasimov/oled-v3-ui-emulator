#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

#include "Router.h"
#include "msg.h"

void App::init(void) {
    TRouter::Init();
    send_message(REPAINT, 0, 0);
}

void App::run(void) {

    TMessage m;
    while (true) {
        if (get_message(&m)) {
            if (TRouter::Page) {
                TRouter::Page->ProcessMessage(&m);
                TRouter::Page->view();
            }
        }
        TDisplayDriver::out();
    }
}