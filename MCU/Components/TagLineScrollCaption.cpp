#include "TagLineScrollCaption.h"
#include "LinkLabel.h"

TTagLineScrollCaption::TTagLineScrollCaption(std::string caption, std::string tag, TLabelInitStructure init) : TTagLine(caption, tag, init) {
	if (Caption) {
		delete Caption;
	}
	Caption = new TLinkLabel(caption, tag, init);
}

bool TTagLineScrollCaption::ProcessMessage(TMessage* m) {
	return Caption->ProcessMessage(m);
}
