#ifndef RESOURCES_H
#define RESOURCES_H

#include "iresources.h"

struct TInternalResources {
  public:
    static void init();
    static char * getItemName(u16 idx);
    static char * getID();
  private:
    static pResources Root;// = (pResources)RESOURCES_DATA;//RESOURCES_ADDRESS;
    static std::vector<pItem> ValidItems;
    static pItem getItemByName(char* Name);
    static std::string getStringFormResource(pItem item);
};

#endif