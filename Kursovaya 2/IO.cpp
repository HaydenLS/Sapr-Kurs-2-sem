#include"Methods.h"
#include<fstream>
#include<ostream>




bool ReadStr(ListH& lst, std::ifstream& f, int& bytes);

// Считывание файла
void Inf(ListV& two_list, std::ifstream& f, std::ofstream& output)
{
	
	ListH temp_lst;
	f.clear(); f.unsetf(std::ios::skipws);
	int bytes = 0; // Количесвто считаных символов.
	while (!f.eof())
	{

		bool result = ReadStr(temp_lst, f, bytes); // Читаем строку.
		if (result == 0)
		{
			output << "Ошибка при чтении файла. Конец программы."; return;
		}
		two_list.push_back(temp_lst);

		if (!f.eof())
			temp_lst.~ListH(); // Обнулить временный список.


	}
}

// Чтение строки
bool ReadStr(ListH& lst, std::ifstream& f, int& bytes)
{
	if (f.eof()) return 0;

	String tempStr;
	char t{};
	int i = 0;
	unsigned ps = 0;
	while (true)
	{
		f >> t; bytes++;
		if (i >= N || t == '\n' || f.eof()) // Put String in ListH
		{
			tempStr.SetLen(i);
			lst.push_back(tempStr);

			tempStr.Clear();
			
			i = 0;

			if (f.eof() || t == '\n')
				return 1;
			
			f.seekg(--bytes);
		}
		else
		{
			tempStr[i++] = t;
		}
	}
}

void OutStrH(ListH& lst, std::ostream& ofile, bool isProgram);

// Вывод всего списка
void OutPut(ListV& two_list, std::ostream& ofile, bool isProgram)
{
	two_list.cur = two_list.head;
	while (two_list.cur != nullptr)
	{
		OutStrH(two_list.cur->elemH, ofile, isProgram);
		ofile << std::endl;

		two_list.cur = two_list.cur->lstNext;

		if (two_list.cur != nullptr && isProgram)
			ofile << "\n |\n\\|/\n" << std::endl;
		else
			ofile << std::endl;
	}
}

// Вывод строки списка
void OutStrH(ListH& lst, std::ostream& ofile, bool isProgram)
{
	lst.cur = lst.head;
	int s = 0;
	while (lst.cur != nullptr)
	{
		// Вывод элемента String
		s = lst.cur->elem.Len();
		for (int i = 0; i < s; i++)
		{
			ofile << lst.cur->elem[i];
		}

		lst.cur = lst.cur->strNext;

		if (lst.cur != nullptr && isProgram)
			ofile << " --> ";
	}

}
