#include "id.h"
#include "Intmash_bastypes.h"
#include "resources_wrapper.h"

int getID(char **addr) {//�������, ����������� ID-������
  TItemProps props = getIDPropsFromRes();
  *addr = props.Addr;
  return props.Size;
}