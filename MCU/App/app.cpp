#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"


#include "PageMainMenu.h"
#include "msg.h"

TPageMainMenu* PageMainMenu;


void App::init(void) {
    PageMainMenu = new TPageMainMenu();
    send_message(REPAINT, 0, 0);
}

void App::run(void) {

    TMessage m;
    
    if (get_message(&m)) {
        PageMainMenu->ProcessMessage(&m);
        PageMainMenu->view();
    }
    TDisplayDriver::out();
}