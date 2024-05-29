#include "String.h"

String::String(int len): len(len)
{

}

String::~String()
{
}

int String::Len()
{
	return len;
}

char& String::operator[](int index)
{
	if (index > len)
		throw std::out_of_range("Index Out Of Range");
	else
		return str[index];
}

void String::SetElem(char elem, int index)
{
	if (index < len)
		str[index] = elem;
}

void String::SetLen(int newlen)
{
	if (newlen > N)
		len = N;
	else
		len = newlen;
}

int String::Znach()
{
	return atoi(str);
}

void String::Clear()
{
	for (int i = 0; i < len; i++)
	{
		str[i] = '\0';
	}
	len = N;
}

std::ostream& operator<<(std::ostream& os, String& string)
{
	char* newChar = new char[string.len + 1];
	for (int i = 0; i < string.len; i++)
	{
		newChar[i] = string[i];
	}
	newChar[string.len] = '\0';

	os << newChar;

	delete[] newChar;

	return os;
}
