#ifndef RESOURCES_H
#define RESOURCES_H

#include "iresources.h"

struct TInternalResources {
  public:
    static void init();
    static pItem getItemByName(char* Name);
    static std::string getID();
    static char* getRoot();
  private:
    static pResources Root;// = (pResources)RESOURCES_DATA;//RESOURCES_ADDRESS;
    static std::vector<pItem> ValidItems;
    static char* getItemName(u16 idx);
    static std::string getStringFormResource(pItem item);
};

#endif