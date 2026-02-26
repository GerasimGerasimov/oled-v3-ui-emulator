#ifndef INTERNAL_DOUT_H
#define INTERNAL_DOUT_H

#include "stm32f4xx.h"
#include <StateControllers.h>

#define DOUT0BIT (1<<8)
#define DOUT1BIT (1<<9)

#define DO_RUN    DOUT0BIT
#define DO_ALARM  DOUT1BIT

struct InternalDOUT {
  public:
    static void init();
    static void update();
    static void setState(bool state, u16 out);
private:
    static TTrackedBit Tag;
    static void SlotU1RAMUpdate(TSlotHandlerArsg args);
    static void uptateSlot(const std::string PosMem, TSlotHandlerArsg& args);
};

#endif