#include "U1RamUpdate.h"
#include "consolelog.h"
#include "resources.h"

static const u8 cmdGetID[] = { 1, 17 };

void U1RAMSlot::init(void) {
	Flags = 0;
	addcmd((u8*)cmdGetID, sizeof(cmdGetID));
	onReadEnd = [this](s16 result, u8* reply) { parceRespond(result, reply); };
}

void U1RAMSlot::parceRespond(s16 result, u8* reply) {
	if (result < 0) {
		//console::log(L"comcallback:Error\n");
		std::string str = TInternalResources::getID();
		str += "\n";
		std::wstring wstr(str.begin(), str.end());
		console::log(wstr);
	}
	else {
		std::string str((char*)reply, (int)result);
		str += "\n";
		std::wstring wstr(str.begin(), str.end());
		console::log(wstr);
	}
}

U1RAMSlot::U1RAMSlot() {

}

U1RAMSlot::~U1RAMSlot() {

}