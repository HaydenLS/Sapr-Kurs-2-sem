#pragma once
#include "Methods.h"

// Переворачивание строки
void ReverseInt(int* number, int size);

// Удаление ведущих нулей.
void RemoveZeroes(int* number, int& size);

/* Операции сравнения */

// ==
bool Oequal(int* number1, const int sizel1, int* number2, const int sizel2);

// <
bool Oless(int* number1, const int sizel1, int* number2, const int sizel2);

// <=
bool Orless(int* number1, const int sizel1, int* number2, const int sizel2);

// >=
bool Obig(int* number1, const int sizel1, int* number2, const int sizel2);

/* Арифметика */

// Сумма чисел
void Addition(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr);

// Вычитание
void Sub(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr);

// Умножение
void Multiply(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr);

// Вспомогательные методы для деления.

// Метод для вывода числа.
std::string Out(int* number, int size);

// Функция вычитания number2 из number1 (number1 >= number2)
void Subtract(int* number1, int size1, int* number2, int size2);

// Умножение массива на число.
void MultiplyByNumber(int* number, int& size, int n, int* result);

// Деление
void Division(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result_list, int& sizelr);

