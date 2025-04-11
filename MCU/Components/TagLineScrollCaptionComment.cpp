#include "TagLineScrollCaptionComment.h"
#include "IniResources.h"
#include "ScrollLabel.h"

TTagLineScrollCaptionComment::TTagLineScrollCaptionComment(std::string tag, TLabelInitStructure init) : TTagLineScrollCaption("", tag, init) {
	TParameter* parametr = (TParameter*)(IniResources::getSignalByTag(tag));
	
	((TScrollLabel*)Caption)->setSrcCaption(parametr->getComment());
}
