#include "LedPWR.h"

#define LED_RUN_ON   GPIOB->BSRRH = GPIO_Pin_11//13
#define LED_RUN_OFF  GPIOB->BSRRL = GPIO_Pin_11
#define LED_RUN_ST   GPIOB->ODR & GPIO_Pin_11

void LedPWR::init() {
    setState(0);
}

void LedPWR::setState(u16 state) {
    switch (state) {
    case 0:
	LED_RUN_OFF;
	break;
    case 1:
	LED_RUN_ON;
	break;
  };
}
