#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

#include "PageMainMenu.h"
#include "PageCounters.h"
#include "msg.h"

TPageMainMenu* PageMainMenu;
TPageCounters* PageCounters;

void App::init(void) {
    PageMainMenu = new TPageMainMenu("MainMenu");
    PageCounters = new TPageCounters("Counters");
    send_message(REPAINT, 0, 0);
}

void App::run(void) {

    TMessage m;
    
    if (get_message(&m)) {
        //PageCounters->ProcessMessage(&m);
        //PageCounters->view();
        PageMainMenu->ProcessMessage(&m);
        PageMainMenu->view();
    }
    TDisplayDriver::out();
}