#include "resources.h"
#include "crc16.h"
#include <string>

//инициализация статического чдена класса
std::vector<pItem> TInternalResources::ValidItems = std::vector<pItem>();
pResources TInternalResources::Root = NULL;

void TInternalResources::init() {
  Root = (pResources) RESOURCES_DATA;
  u16 i = 0;
  while (i < Root->NumberOfItems) {
    pItem p = &Root->Items[i++];
    if (crc16((u8*) p, sizeof (TResourceTableItem)) == 0) {
      ValidItems.push_back(p);
    } else {
      ValidItems.clear();
      return;
    }
  }
}

bool isRequiredName(char * Name1, char * Name2) {
  return (bool)(strcmp(Name1, Name2) == 0);
}

pItem TInternalResources::getItemByName(char* Name) {
  pItem res = NULL;
  for (const pItem & item: ValidItems) {
    if (isRequiredName(item->Name, Name)) {
      return item;
    }
  }
  return res;
}

const char * unknown = "unknown";

/*TODO надо не физический адрес в TResourceProps.Addr помещать, а смешение относительно начала ресурсов
это позволит обращатся к ресурсам безопасно под любой ОС*/

std::string TInternalResources::getStringFormResource(pItem item) {
  const u32 Addr = item->BinaryDataAddr;
  const u32 Size = item->BinaryDataSize;
  std::string str;
  u8* p = (u8*) &Root + Addr;
  str.assign((char*) p, Size);
  return str;
}

char * TInternalResources::getID() {
  pItem item = getItemByName((char*)"ID");
  return (item != NULL)
    ? (char *)getStringFormResource(item).c_str()
    : (char *) unknown;
}

char * TInternalResources::getItemName(u16 idx) {
  return Root->Items[idx].Name;
}