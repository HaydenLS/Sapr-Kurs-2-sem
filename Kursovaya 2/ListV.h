#pragma once
#include "NodeV.h"

class ListV
{
public:
	NodeV* head;
	NodeV* cur;
	NodeV* last;
	int size;

	ListV();
	~ListV();

	void push_back(ListH& list);

	ListH& operator[](int index);
	void pop_back();
	void pop(int n);

	void OutList(std::ostream& os);


	void push(ListH& list, int pos); // Сохранить элемент в определенное место.

};

