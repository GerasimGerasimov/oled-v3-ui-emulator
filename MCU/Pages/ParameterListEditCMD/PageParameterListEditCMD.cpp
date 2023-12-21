#include "PageParameterListEditCMD.h"
#include "Router.h"
#include "TPrmList.h"
#include "CmdSender.h"

TPageParameterListEditCMD::TPageParameterListEditCMD(std::string Name) : TPageParameterListEdit(Name){
  
}

void TPageParameterListEditCMD::sendValue(void) {
  std::string value = getValueOfFocusedLine();
  if (CmdSender::sendCmdPrimList(value)) {
    isDataSent = true;
  }
}


