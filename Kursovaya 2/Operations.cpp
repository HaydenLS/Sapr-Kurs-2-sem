#include "Operations.h"
#include "ConsoleRequest.h"
#include <sstream>


using namespace std;

// Переворачивание строки
void ReverseInt(int* number, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		if (i != (size - 1) - i)
		{
			int temp = number[i];
			number[i] = number[(size - 1) - i];
			number[(size - 1) - i] = temp;
		}

	}
}

// Удаление ведущих нулей.
void RemoveZeroes(int* number, int& size)
{
	ReverseInt(number, size);

	int i = size - 1;
	while (size > 1 && number[i] == 0) {

		size--;
		i--;
	}

	ReverseInt(number, size);
}

/* Операции сравнения */

// ==
bool Oequal(int* number1, const int sizel1, int* number2, const int sizel2)
{
	if (sizel1 != sizel2)
		return false;
	else
	{
		for (int i = 0; i < sizel1; i++)
		{
			if (number1[i] != number2[i])
				return false;
		}
		return true;
	}
}

// <
bool Oless(int* number1, const int sizel1, int* number2, const int sizel2)
{
	if (Oequal(number1, sizel1, number2, sizel2))
		return false;
	else
	{
		if (sizel1 != sizel2)
			return sizel1 < sizel2;
		else
		{
			for (int i = 0; i < sizel1; i++)
			{
				if (number1[i] != number2[i])
					return number1[i] < number2[i];
			}
		}

	}
}

// <=
bool Orless(int* number1, const int sizel1, int* number2, const int sizel2)
{
	if (Oequal(number1, sizel1, number2, sizel2))
		return true;
	else
	{
		if (sizel1 != sizel2)
			return sizel1 < sizel2;
		else
		{
			for (int i = 0; i < sizel1; i++)
			{
				if (number1[i] != number2[i])
					return number1[i] < number2[i];
			}
		}

	}
}

// >=
bool Obig(int* number1, const int sizel1, int* number2, const int sizel2)
{
	if (!Oless(number1, sizel1, number2, sizel2)) // Значит что >=
	{

		return true;

	}

	return false;
}

/* Арифметика */

// Сумма чисел
void Addition(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr)
{
	sizelr = max(sizel1, sizel2) + 1;
	int* numberR = new int[sizelr];
	// Меняем элементы местами
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);

	// Для логов.
	/*cout << '\n';
	OutNumber(number1, sizel1);
	OutNumber(number2, sizel2);*/


	int carry = 0, total = 0;
	for (int i = 0; i < sizelr; i++)
	{
		// Достаем цифры, чтобы не дойти случайно до конца массива.
		int digit1 = i < sizel1 ? number1[i] : 0;
		int digit2 = i < sizel2 ? number2[i] : 0;

		// Считаем
		total = digit1 + digit2;

		// Если число+ остаток больше 9 то в ответ пришем посл цифру если нет то просто число+остаток
		numberR[i] = total + carry > 9 ? (total + carry) % 10 : total + carry;

		// Сохраняем остаток
		carry = (total + carry) / 10;

	}

	// Удаляем ненужный ноль если он есть.
	if (numberR[sizelr - 1] == 0)
		sizelr--;


	// Переворачиваем числа обратно
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);
	ReverseInt(numberR, sizelr);



	//OutNumber(number1, sizel1, '+');
	//OutNumber(number2, sizel2, '=');

	//OutNumber(numberR, sizelr);

	// Сохраняем результат в список result

	MakeList(result, numberR, sizelr);


	delete[] numberR;
}

// Вычитание
void Sub(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr)
{
	sizelr = max(sizel1, sizel2);
	int* numberR = new int[sizelr];

	// Меняем элементы местами
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);

	// Создаем коппию первого числа на всякий случай
	int* number1copy = new int[sizel1];
	for (int i = 0; i < sizel1; i++)
	{
		number1copy[i] = number1[i];
	}

	// Определяем знак ответа.

	int carry = 0;
	for (int i = 0; i < sizelr; i++)
	{
		// Достаем цифры, чтобы не дойти случайно до конца массива.
		int digit1 = i < sizel1 ? number1copy[i] : 0;
		int digit2 = i < sizel2 ? number2[i] : 0;

		// Считаем
		int total = digit1 - digit2;

		if (total < 0)
		{
			number1copy[i + 1] -= 1;
			total += 10;
		}

		numberR[i] = total;
	}

	int i = sizelr;
	while (numberR[i - 1] == 0)
	{
		sizelr--;
		i--;
	}

	/*OutNumber(number1, sizel1);*/

	// Переворачиваем числа обратно
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);
	ReverseInt(numberR, sizelr);




	/*OutNumber(number1, sizel1, '-');
	OutNumber(number2, sizel2, '=');

	OutNumber(numberR, sizelr);*/

	// Сохраняем результат в список result

	MakeList(result, numberR, sizelr);

	/*OutNumber(numberR, sizelr);*/

	MakeList(result, numberR, sizelr);

	delete[] number1copy;
	delete[] numberR;
}


// Умножение
void Multiply(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr)
{
	// Если умножаем на 0.
	if (sizel1 == 1 && number1[0] == 0 || sizel2 == 1 && number2[0] == 0)
	{
		int* zero = new int[1];
		zero[0] = 0;
		MakeList(result, zero, 1);
		return;
	}


	// Выделение памяти для результата умножения.
	sizelr = sizel1 + sizel2;
	int* numberR = new int[sizelr]();
	// Для промежуточных результатов.
	int promSize = sizel1 + 1;
	const int begsize = promSize;
	int* promNumber = new int[promSize];
	for (int i = 0; i < sizel1 + 1; i++)
	{
		promNumber[i] = numberR[i];
	}
	promNumber[promSize - 1] = 0;

	int w = sizelr; // Сдвиг
	// Выводим промежуточные результаты.
	for (int i = sizel2 - 1; i >= 0; i--) // number 2
	{
		// Стандартное умножение
		int carry = 0;
		int all = promSize - 1;
		for (int j = sizel1 - 1; j >= 0; j--) // number 1
		{
			int cur = number2[i] * number1[j] + promNumber[all] + carry;

			promNumber[all--] = cur % 10;

			carry = cur / 10;

		}

		promNumber[all] += carry;


		// Вывод числа.
		RemoveZeroes(promNumber, promSize);

		if (promNumber[0] != 0)
		{
			ListH tempLst;
			MakeList(tempLst, promNumber, promSize);

			cout << '\t' << setw(w) << tempLst << endl;

			tempLst.~ListH();
		}
		w--;

		// Очистка числа.
		for (int i = 0; i < begsize; i++)
		{
			promNumber[i] = 0;
		}
		promSize = begsize;

	}




	for (int i = sizel2 - 1; i >= 0; i--) // number 2
	{
		int carry = 0;
		for (int j = sizel1 - 1; j >= 0; j--) // number 1
		{
			int cur = number2[i] * number1[j] + numberR[i + j + 1] + carry;


			numberR[i + j + 1] = cur % 10;

			carry = cur / 10;

		}

		if (carry != 0)
		{
			numberR[i] += carry;
		}
	}

	// Удаление ведущих нулей.
	RemoveZeroes(numberR, sizelr);



	MakeList(result, numberR, sizelr);

	delete[] numberR;


}

// Вспомогательные методы для деления.

// Метод для вывода числа.
std::string Out(int* number, int size)
{
	std::ostringstream oss;
	for (int i = 0; i < size; i++) {
		oss << number[i];
	}
	return oss.str();
}

// Функция вычитания number2 из number1 (number1 >= number2)
void Subtract(int* number1, int size1, int* number2, int size2)
{
	OPEN_LOG
		log << Out(number1, size1) << " - " << Out(number2, size2) << " = ";
	for (int i = 0; i < size2; i++) {
		number1[size1 - size2 + i] -= number2[i];
		if (number1[size1 - size2 + i] < 0) {
			number1[size1 - size2 + i] += 10;
			number1[size1 - size2 + i - 1] -= 1;
		}
	}
	// Обработка заемов
	for (int i = size1 - size2 - 1; i >= 0; i--) {
		if (number1[i] < 0) {
			number1[i] += 10;
			number1[i - 1] -= 1;
		}
	}
	log << Out(number1, size1) << endl;
	CLOSE_LOG
}

// Умножение массива на число.
void MultiplyByNumber(int* number, int& size, int n, int* result)
{

	int result_size = size; // Результат может быть на 1 разряд больше исходного числа

	size--;

	int carry = 0;
	for (int i = size - 1; i >= 0; i--) {
		int product = number[i] * n + carry;
		result[i + 1] = product % 10;
		carry = product / 10;
	}
	result[0] = carry;

	RemoveZeroes(result, result_size);

	size = result_size;

}

// Деление
void Division(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result_list, int& sizelr)
{
	OPEN_LOG

		// Если делимое меньше делителя, результат - 0
		if (Oless(number1, sizel1, number2, sizel2))
		{
			int* zero = new int[1];
			zero[0] = 0;
			MakeList(result_list, zero, 1);
			delete[]zero;
			return;
		}

	// Если числа равны, ответ 1
	if (Oequal(number1, sizel1, number2, sizel2))
	{
		int* one = new int[1];
		one[0] = 1;
		MakeList(result_list, one, 1);
		delete[]one;
		return;
	}


	// Выделение памяти для результата
	sizelr = sizel1 - sizel2 + 1;
	int* result = new int[sizelr]();


	int* tempN = new int[sizel1]();
	int tempN_size = 0;

	int p = 0; // на какой позиции в 1 числе.
	int resulti = 0; // индекс резульата
	for (int i = 0; i < sizelr; i++)
	{
		// Формирую число, на которое делится.
		if (p >= sizel1)
			break;

		// Не забываю, что если сношу две цифры сразу, то ответ нолик
		int y = 0; // Количество снесенных цифр в этот раз.
		while (Orless(tempN, tempN_size, number2, sizel2))
		{
			log << Out(tempN, tempN_size) << "<=" << Out(number2, sizel2) << endl;
			if (p > sizel1)
				break;


			tempN[tempN_size] = number1[p];
			p++;
			tempN_size++;
			y++;

			if (y > 1 && resulti)
			{
				result[resulti++] = 0;
			}


		}
		if (p > sizel1)
			break;

		log << Out(tempN, tempN_size) << ">=" << Out(number2, sizel2) << endl;


		RemoveZeroes(tempN, tempN_size);


		if (i != 0)
			cout << '\t' << setw(p) << Out(tempN, tempN_size) << endl;
		// Начинаем вычитать нужно сделть копию или двоичный поиск.


		for (int c = 1; c <= 9; c++)
		{
			// Объявлем новый массив для работы
			int product_size = sizel2;
			int* product = new int[product_size]();
			for (int i = 0; i < sizel2; i++)
			{
				product[i] = number2[i];
			}


			int* result_product = new int[++product_size]();
			MultiplyByNumber(product, product_size, c, result_product);
			delete[] product; product = result_product;

			log << "Шаг: " << c << " получен " << Out(product, product_size) << endl;

			RemoveZeroes(product, product_size);

			if (Obig(product, product_size, tempN, tempN_size) || c == 9)
			{
				if (!Oequal(product, product_size, tempN, tempN_size) && Obig(product, product_size, tempN, tempN_size))
				{
					// Нам нужно уже предыдущее.
					c--;


					product_size = sizel2;
					delete[] product;
					product = new int[product_size]();
					for (int i = 0; i < sizel2; i++)
					{
						product[i] = number2[i];
					}

					RemoveZeroes(tempN, tempN_size);

					result_product = new int[++product_size]();
					MultiplyByNumber(product, product_size, c, result_product);
					delete[] product; product = result_product;
					RemoveZeroes(product, product_size);
				}

				cout << '\t' << setw(p) << Out(product, product_size);
				if (i == 0) cout << setw(sizel1 - p + 1) << '|';
				cout << endl;
				if (i == 0)
					cout << '\t' << setw(sizel1 + 1) << setfill('-') << "" << setfill(' ') << endl;


				Subtract(tempN, tempN_size, product, product_size);

				RemoveZeroes(tempN, tempN_size);

				log << "Получил промежуточное число: ";
				log << setw(p) << Out(tempN, tempN_size) << endl;
				log << "В ответ добавляется цифра " << c << endl;


				result[resulti++] = c;
				delete[] product;
				break;
			}

		}

	}


	log << "Результат: " << Out(result, resulti);

	sizelr = resulti;

	cout << '\t' << "Ответ: " << Out(result, resulti) << endl;

	RemoveZeroes(result, sizelr);

	MakeList(result_list, result, sizelr);

	delete[] result;
	delete[] tempN;

	CLOSE_LOG
}
