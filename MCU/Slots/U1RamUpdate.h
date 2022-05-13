#ifndef U1_RAM_UPDATE_H
#define U1_RAM_UPDATE_H
#include "Slot.h"

class U1RAMSlot : public Slot {
public:
	virtual void init(void);
	U1RAMSlot();
	~U1RAMSlot();
private:
	void parceRespond(s16 result, u8* reply);
};

#endif