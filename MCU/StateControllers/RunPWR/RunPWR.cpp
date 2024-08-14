#include "RunPWR.h"
#include <IniResources.h>
#include "Leds/PWR/LedPWR.h"

void RunPWR::SlotU1RAMUpdate(TSlotHandlerArsg args){
	uptate("U1/RAM/", args);
	State = checkState();
	LedPWR::setState((State ? 1 : 0));
}

std::map<std::string, TTrackedBit> RunPWR::Tags = {
	{"PWR", {"U1/RAM/PWR/", nullptr, false, false}}
};

bool RunPWR::State = true;

void RunPWR::init(){
	for(auto& e : Tags){
		std::string& tag = (std::string&)e.second.Tag;
		e.second.pBit = (TBit*)IniResources::getSignalByTag(tag);
	}
	HandlerSubscribers::set("U1/RAM/", SlotU1RAMUpdate);
}

void RunPWR::uptate(const std::string PosMem, TSlotHandlerArsg& args){
	static std::string res = "";
	for(auto& e : Tags){
		std::string& Tag = (std::string&)e.second.Tag;
		bool isDeviceTag = Tag.find(PosMem) != std::string::npos;
		if(isDeviceTag){
			TBit* p = e.second.pBit;
			res = p->getValue(args, "");
			if((res == "0") || (res == "1")){
				e.second.isValid = true;
				e.second.State = (res == "0") ? true : false;
			}
			else{
				e.second.isValid = false;
			}
		}
	}
}

bool RunPWR::checkState(){
	bool res = false;
	for(auto& e : Tags){
		bool valid = e.second.isValid;
		bool state = e.second.State;
		if(valid){//данные валидны
			if(!state){//цикл прекращается и возвращает "0" если хоть один из элементов "0"
				res = true;
				break;
			}
		}
		else{//что-то НЕ валидное попалось
			res = false;
			break;
		}
	}
	return res;
}


