#include "display_dc.h"

u8 framebuffer[8][128]; //��� �������� �� SPI 

u32 getFrameBufferAddr(void) {
  return (u32) & framebuffer;
}