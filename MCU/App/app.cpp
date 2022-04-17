#include "app.h"
#include <string>
#include "graphics.h"
#include "display_driver.h"

void App::init(void) {

}

static u32 COUNT = 0;

void App::run(void) {
    COUNT++;
    std::string scount = std::to_string(COUNT);

    TTextSizes tsize;
    tsize = TMCUFonts::getTextSizes(scount, "Verdana12");
    TGrahics::fillRect({ 10,36, tsize.width, tsize.height, 0 });
    TGrahics::outText(scount, 10, 36, 1, "Verdana12");

    tsize = TMCUFonts::getTextSizes(scount, "MSSansSerifBold14");
    TGrahics::fillRect({ 40,36, tsize.width, tsize.height, 1 });
    TGrahics::outText(scount, 40, 36, 0, "MSSansSerifBold14");

    TDisplayDriver::out();
}