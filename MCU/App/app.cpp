#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

#include "PageMainMenu.h"

TPageMainMenu* PageMainMenu;


void App::init(void) {
    PageMainMenu = new TPageMainMenu();
}

void App::run(void) {

    PageMainMenu->view();

    TDisplayDriver::out();
}