#pragma once

#define N 5
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"


#include <stdexcept>
#include <ostream>


class String
{
	char str[N];
	int len = N;
public:
	//Constructors
	String(int len=N);
	~String();

	//Getters
	int Len();
	char& operator[](int index);

	//Setters
	void SetElem(char elem, int index);
	void SetLen(int newlen);

	int Znach();


	//Methods
	void Clear();

	friend std::ostream& operator<<(std::ostream& os, String& string);

};

