#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

#include "Router.h"
#include "msg.h"

TRouter Router;

void App::init(void) {
    Router.Init();
    send_message(REPAINT, 0, 0);
}

void App::run(void) {

    TMessage m;
    while (true) {
        if (get_message(&m)) {
            if (Router.Page) {
                Router.Page->ProcessMessage(&m);
                Router.Page->view();
            }
        }
        TDisplayDriver::out();
    }
}