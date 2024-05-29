#include "ListV.h"

ListV::ListV()
{
	head = cur = last = nullptr;
	size = 0;
}

void ListV::push_back(ListH& list)
{
	if (head == nullptr)
	{
		head = new NodeV(list);
		last = head;
		size++;
	}
	else
	{
		NodeV* tmp = new NodeV(list, last);
		last->lstNext = tmp;
		last = tmp;
		size++;
	}
}

ListH& ListV::operator[](int index)
{
	if (index > size)
	{
		throw std::out_of_range("Index Out Of Range");
	}

	cur = head;
	for (int i = 0; i < index; i++)
	{
		cur = cur->lstNext;
	}

	return cur->elemH;
}

void ListV::pop_back()
{
	if (size <= 0)
		return;

	NodeV* tmp = last->lstPrev;

	delete last; size--;

	if (size == 0)
		return;

	tmp->lstNext = nullptr;
	last = tmp;
}

// Удаление элемента по индексу.
void ListV::pop(int n)
{
	if (n >= size-1 || (n==0 && size==1))
	{
		pop_back();
	}
	else 
	{
		if (size == 0)
			return;

		cur = head;
		for (int i = 0; i < n; i++)
		{
			cur = cur->lstNext;
		}

		
		
		cur->lstNext->lstPrev = cur->lstPrev;
		if (cur != head)
			cur->lstPrev->lstNext = cur->lstNext;
		else
			head = cur->lstNext;

		delete cur; size--;
		

	}
}

void ListV::OutList(std::ostream& os)
{
	int n = 0;
	cur = head;
	while (cur != nullptr)
	{
		os << BLUE <<++n << RESET << ". " << cur->elemH << std::endl;
		cur = cur->lstNext;
	}
}


void ListV::push(ListH& list, int pos)
{
	if (pos > 0 && pos < size)
	{
		// Доходим до элемента,  потом просто запихиваем строку.

		cur = head;
		for (int i = 0; i < pos; i++)
		{
			cur = cur->lstNext;
		}

		cur->elemH.copyList(list);
	}
	else
	{
		push_back(list);
	}
}

ListV::~ListV()
{
	if (size != 0)
	{
		cur = head;
		while (cur != nullptr)
		{
			NodeV* tmp = cur->lstNext;
			delete cur;
			cur = tmp;
		}
	}
	head = cur = last = nullptr;
	size = 0;
}