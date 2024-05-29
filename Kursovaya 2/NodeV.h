#pragma once
#include "ListH.h"

class NodeV
{
public:
	ListH elemH;
	NodeV* lstPrev;
	NodeV* lstNext;

	NodeV(ListH& elemH, NodeV* lstPrev = nullptr, NodeV* lstNext = nullptr);
	~NodeV();
};

