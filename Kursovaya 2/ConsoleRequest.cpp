#include "ConsoleRequest.h"

using namespace std;

// Превращает списки в массивы чисел.
void CreateArray(ListH& l1, ListH& l2, int* number1, int sizel1, int* number2, int sizel2)
{
	// Для 1 списка.

	l1.cur = l1.head;
	int j = 0; // Переменная для пробега по массиву int.
	while (l1.cur != nullptr)
	{
		for (int i = 0; i < l1.cur->elem.Len(); i++)
		{
			number1[j++] = l1.cur->elem[i] - '0';
		}
		l1.cur = l1.cur->strNext;
	}

	// Тоже для второго списка.
	// 
	// Для 2 списка.

	l2.cur = l2.head;
	j = 0; // Переменная для пробега по массиву int.
	while (l2.cur != nullptr)
	{
		for (int i = 0; i < l2.cur->elem.Len(); i++)
		{
			number2[j++] = l2.cur->elem[i] - '0';
		}
		l2.cur = l2.cur->strNext;
	}
}

// Создать из Int список
void MakeList(ListH& list, int* number, int size)
{
	// Удаляем жлементы списка, если он уже заполнен.
	list.~ListH();

	//int j = 0; // Счетчик

	int listSize = size / N + (size % N != 0);

	String tempstr;

	int k = size; // сколько элементов осталось добавить.
	int needToAdd = (k - N) >= 0 ? N : k % N; // Сколько элементов нужно добавить на текщем шаге.
	int all = 0;
	while (k > 0)
	{
		needToAdd = (k - N) >= 0 ? N : k % N;

		tempstr.SetLen(needToAdd);


		for (int i = 0; i < needToAdd; i++)
		{
			tempstr[i] = number[all++] + '0';
		}

		list.push_back(tempstr);
		tempstr.Clear();

		k -= needToAdd;
	}
}

// Выполнение запроса.
void DoRequest(ListV& list, ListH& request)
{
	char operation = request[0][0];

	int i1 = request[1].Znach() - 1, i2 = request[2].Znach() - 1; // Индексы чисел

	if (i1 >= list.size || i2 >= list.size)
	{
		cout << RED << "Номера нужных строк не найдены!\n" << RESET;
		return;
	}

	int size1 = list[i1].GetSize(), size2 = list[i2].GetSize(); // Размеры

	int* number1 = new int[size1];
	int* number2 = new int[size2];


	CreateArray(list[i1], list[i2], number1, size1, number2, size2);

	int rSize = 0;

	ListH result;

	switch (operation)
	{
	case '+':

		Addition(number1, size1, number2, size2, result, rSize);

		cout << GREEN << "Результат сложения чисел: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << endl
			<< '\t' << result << "\n\n";

		break;

	case '-':

		if (Oless(number1, size1, number2, size2))
		{
			cout << RED << "Нельзя вычитать из меньшего большее!!\n" << RESET;
			return;
		}
		Sub(number1, size1, number2, size2, result, rSize);
		rSize = max(size1, size2);
		cout << GREEN << "Результат вычитания чисел: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << endl
			<< '\t' << setfill(' ') << setw(rSize) << result << "\n\n";




		break;

	case '*':
		rSize = size1 + size2;

		cout << GREEN << "Результат умножения чисел: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << setfill(' ') << endl;

		Multiply(number1, size1, number2, size2, result, rSize);

		rSize = size1 + size2;

		cout << '\t' << setfill('-') << setw(rSize) << "" << endl << setfill(' ')
			<< '\t' << setw(rSize) << result << "\n\n";

		break;

	case '/':

		// Проверка на случай деления на ноль
		if (size2 == 1 && number2[0] == 0)
		{
			cout << RED << "Нельзя вычитать из меньшего большее!!\n" << RESET;
			return;
		}

		cout << GREEN << "Результат деления чисел: \n\n" << RESET;
		cout << '\t' << list[i1] << "|" << list[i2] << endl;


		Division(number1, size1, number2, size2, result, rSize);


		break;
	}

	int position = request[3].Znach() - 1;
	cout << YELLOW;
	if (position >= list.size || position <= 0)
	{
		cout << "Результат сохранен в конец списка!\n";
	}
	else
	{
		cout << "Результат сохранен на " << BLUE << position + 1 << YELLOW << " место списка.\n";
	}
	cout << RESET;
	list.push(result, position);


}

// Читает файл с запросом.
void ReadRequest(ListV& requests)
{
	ifstream f("Request.txt"); f.unsetf(ios::skipws);
	if (f.eof()) return;

	ListH tempReq;

	int i = 0;
	char t = 0;

	char tempEl[13]{};


	while (true)
	{
		f >> t;

		//Дошли до конца строки
		if (t == '\n' || f.eof() || i >= 13)
		{

			String Op(1);
			Op[0] = tempEl[0];

			tempReq.push_back(Op);

			int k = 2;
			String number(3);

			while (k < i && tempEl[k] != '\0')
			{
				number.SetLen(3);
				int j = 0;
				do
				{

					number[j++] = tempEl[k++];

				} while (tempEl[k] != ' ' && j < 3 && tempEl[k] != '\0');

				number.SetLen(j);
				tempReq.push_back(number);

				k++;
				number.Clear();


			}

			if (tempReq.size == 3)
			{
				String zero(1);
				zero[0] = '0';
				tempReq.push_back(zero);
			}


			requests.push_back(tempReq);

			tempReq.~ListH();

			i = 0;

			for (int l = 0; l < 13; l++) tempEl[l] = '\0';

			if (f.eof())
				break;

		}
		else
		{
			tempEl[i++] = t;
		}

	}
}


// Основной метод с запросами из файла.
void RequestHandler(ListV& list)
{

	ListV requests;

	ReadRequest(requests);

	while (requests.size > 0)
	{


		// Вывод запроса.
		cout << CYAN << "\nВведи нужный номер запроса:\n" << RESET;
		int k = 0;
		requests.cur = requests.head;

		while (requests.cur != nullptr)
		{
			ListH request = requests.cur->elemH;

			String operation = request[0];
			String n1 = request[1];
			String n2 = request[2];
			cout << ++k << ". Число под номером " << BLUE << n1 << RESET << " " << operation
				<< " Число под номером " << BLUE << n2 << RESET << endl;


			requests.cur = requests.cur->lstNext;
		}
		cout << "0. Назад.\n";



		int n = 0;
		cout << "Введите номер: ";
		cin >> n;
		cout << "\n";

		if (n > requests.size || n < 0)
		{
			cout << "\nТакого запроса нет!\n";
			continue;
		}
		if (n == 0)
			return;
		else
		{
			DoRequest(list, requests[n - 1]);
			requests.pop(n - 1);

			// Вывод списка.
			cout << "\nПолученный список: \n";
			list.OutList(cout);


		}
		/*cout << "\n\n\n";*/


	}



}