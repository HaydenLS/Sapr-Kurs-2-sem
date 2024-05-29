#pragma once
#include "String.h"

class NodeH
{
public:
	String elem;
	NodeH* strPrev;
	NodeH* strNext;


	NodeH(String& str, NodeH* strPrev=nullptr, NodeH* strNext=nullptr);
	~NodeH();
};

