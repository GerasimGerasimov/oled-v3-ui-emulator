#include "TagLineScrollCaptionComment.h"
#include "IniResources.h"
#include "LinkLabel.h"

TTagLineScrollCaptionComment::TTagLineScrollCaptionComment(std::string tag, TLabelInitStructure init) : TTagLineScrollCaption("", tag, init) {
	TParameter* parametr = (TParameter*)(IniResources::getSignalByTag(tag));
	
	((TLinkLabel*)Caption)->setSrcCaption(parametr->getComment());
}
