#include "livecontrol.h"
#include <iar_dlmalloc.h>
#include "LEDs.h"
#include "RAMdata.h"

static struct mallinfo IARHeapInfo;

void ctrlSysLive(void) {
   IARHeapInfo = __iar_dlmallinfo();
   RAM_DATA.UsedMem = IARHeapInfo.uordblks;
   RAM_DATA.TotalMem = IARHeapInfo.usmblks;
   //RAM_DATA.var2 ++;
}