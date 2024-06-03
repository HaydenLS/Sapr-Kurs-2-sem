#include "ListH.h"

ListH::ListH()
{
	head = cur = last = nullptr;
	size = 0;
}

ListH::ListH(const ListH& other)
{
	this->copyList(other);
}

void ListH::push_back(String& str)
{
	if (head == nullptr)
	{
		head = new NodeH(str);
		last = head;
		size++;
	}
	else
	{
		NodeH* elem = new NodeH(str, last);
		last->strNext = elem;
		last = elem;
		size++;
	}
}


void ListH::copyList(const ListH& lst)
{
	this->~ListH();
	if (lst.size != 0)
	{
		NodeH* tmp = lst.cur;
		tmp = lst.head;
		while (tmp!=nullptr)
		{
			this->push_back(tmp->elem);
			tmp = tmp->strNext;
		}
	}
}


int ListH::GetSize()
{
	cur = head;
	int l = 0;
	while (cur != nullptr)
	{
		l += cur->elem.Len();
		cur = cur->strNext;
	}
	return l;
}

String& ListH::operator[](int index)
{
	if (index > size)
	{
		throw std::out_of_range("Index Out Of Range");
	}
	
	cur = head;
	for (int i = 0; i < index; i++)
	{
		cur = cur->strNext;
	}

	return cur->elem;
}


void ListH::pop(int n) // Удаление элемента по номеру
{




	cur = head;
	// Доходим до нужного элемента
	for (int i = 0; i < n - 1; i++)
	{
		cur = cur->strNext;
	}

	// Переадресацию указателей
	if (cur != head)
		cur->strPrev->strNext = cur->strNext;
	else
		head = cur->strNext;
	if (cur != last)
		cur->strNext->strPrev = cur->strPrev;
	else
		last = cur->strPrev;


	delete cur;
	size--;
	
}
ListH::~ListH()
{
	if (size != 0)
	{
		cur = head;
		while (cur!=nullptr)
		{
			NodeH* tmp = cur->strNext;
			delete cur;
			cur = tmp;
		}
	}
	head = cur = last = nullptr;
	size = 0;
}

std::ostream& operator<<(std::ostream& os, ListH& listH)
{

	// Если плохо выводить будет, то метод перепишу с использованием дополнительной памяти.
	int fullLen = listH.GetSize();
	std::unique_ptr<char[]> fullstr ( std::make_unique<char[]>(fullLen+1) );

	listH.cur = listH.head;
	int j = 0;
	while (listH.cur != nullptr)
	{
		for (int i = 0; i < listH.cur->elem.Len(); i++)
		{
			fullstr[j++] = listH.cur->elem[i];
		}


		listH.cur = listH.cur->strNext;
	}
	fullstr[fullLen] = '\0';

	os << fullstr;

	return os;

	
	/*
	Old
	listH.cur = listH.head;
	while (listH.cur != nullptr)
	{
		os << listH.cur->elem;
		listH.cur = listH.cur->strNext;
	}

	return os;
	*/
}
