#include "NodeH.h"

NodeH::NodeH(String& str, NodeH* strPrev, NodeH* strNext)
{
	this->elem = str;
	this->strPrev = strPrev;
	this->strNext = strNext;
}

NodeH::~NodeH()
{
}
