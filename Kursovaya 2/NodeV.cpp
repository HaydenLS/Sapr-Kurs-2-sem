#include "NodeV.h"

NodeV::NodeV(ListH& elemH, NodeV* strPrev, NodeV* strNext)
{
	this->elemH.copyList(elemH);
	this->lstPrev = strPrev;
	this->lstNext = strNext;
}

NodeV::~NodeV()
{
}
