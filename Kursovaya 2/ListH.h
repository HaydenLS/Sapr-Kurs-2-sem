#pragma once
#include "NodeH.h"
class ListH
{
public:
	NodeH* head;
	NodeH* cur;
	NodeH* last;
	int size = 0;


	ListH();
	ListH(const ListH& other);

	void push_back(String& str);
	void copyList(const ListH& lst);

	void SaveArray(char* string, int len);

	int GetSize();

	String& operator[](int index);

	friend std::ostream& operator<<(std::ostream& os, ListH& listH);



	void pop(int n);
	~ListH();

};

