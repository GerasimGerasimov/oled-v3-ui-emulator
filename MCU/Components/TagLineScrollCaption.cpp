#include "TagLineScrollCaption.h"
#include "ScrollLabel.h"

TTagLineScrollCaption::TTagLineScrollCaption(std::string caption, std::string tag, TLabelInitStructure init) : TTagLine(caption, tag, init) {
	if (Caption) {
		delete Caption;
	}
	Caption = new TScrollLabel(caption, init);
}

bool TTagLineScrollCaption::ProcessMessage(TMessage* m) {
	return Caption->ProcessMessage(m);
}
