#include "internal_dout.h"
#include "RAMdata.h"
#include <IniResources.h>
#include "HandleSubscribers.h"

#define DOUT_0_ON   GPIOC->BSRRH = GPIO_Pin_9
#define DOUT_0_OFF  GPIOC->BSRRL = GPIO_Pin_9
#define DOUT_0_ST   GPIOC->ODR & GPIO_Pin_9

#define DOUT_1_ON   GPIOC->BSRRH = GPIO_Pin_8
#define DOUT_1_OFF  GPIOC->BSRRL = GPIO_Pin_8
#define DOUT_1_ST   GPIOC->ODR & GPIO_Pin_8

TTrackedBit InternalDOUT::Tag = {"U1/RAM/frambckp_error/", nullptr, false, false};

void InternalDOUT::init(void){
  RAM_DATA.DIO &= 0x00FF;//старший байт для вЫходов
  const std::string& tag = Tag.Tag;
  Tag.pBit = (TBit*)IniResources::getSignalByTag(tag);
  HandlerSubscribers::set("U1/RAM/", SlotU1RAMUpdate);
}

void InternalDOUT::update(void){
    if(Tag.isValid){
        setState(Tag.State, DO_RUN);
    }
    else{
        setState(false, DO_RUN);
    }
  /*
  (RAM_DATA.DIO & DOUT0BIT) ? DOUT_0_OFF : DOUT_0_ON;
  (RAM_DATA.DIO & DOUT1BIT) ? DOUT_1_OFF : DOUT_1_ON;
  */
}

void InternalDOUT::setState(bool state, u16 out){
    if(state){
        RAM_DATA.DIO |= out;
    }
    else{
        RAM_DATA.DIO &= ~out;
    }
}

void InternalDOUT::SlotU1RAMUpdate(TSlotHandlerArsg args){
    uptateSlot("U1/RAM/", args);
}

void InternalDOUT::uptateSlot(const std::string PosMem, TSlotHandlerArsg& args){
    static std::string res = "";
    bool isDeviceTag = Tag.Tag.find(PosMem) != std::string::npos;
    if(isDeviceTag){
        TBit* p = Tag.pBit;
        res = p->getValue(args, "");
        if((res == "0") || (res == "1")){
            Tag.isValid = true;
            Tag.State = (res == "1") ? true : false; //
        }
        else{
            Tag.isValid = false;
        }
    }
}
