#pragma once
#include "Methods.h"

// ��������������� ������
void ReverseInt(int* number, int size);

// �������� ������� �����.
void RemoveZeroes(int* number, int& size);

/* �������� ��������� */

// ==
bool Oequal(int* number1, const int sizel1, int* number2, const int sizel2);

// <
bool Oless(int* number1, const int sizel1, int* number2, const int sizel2);

// <=
bool Orless(int* number1, const int sizel1, int* number2, const int sizel2);

// >=
bool Obig(int* number1, const int sizel1, int* number2, const int sizel2);

/* ���������� */

// ����� �����
void Addition(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr);

// ���������
void Sub(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr);

// ���������
void Multiply(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr);

// ��������������� ������ ��� �������.

// ����� ��� ������ �����.
std::string Out(int* number, int size);

// ������� ��������� number2 �� number1 (number1 >= number2)
void Subtract(int* number1, int size1, int* number2, int size2);

// ��������� ������� �� �����.
void MultiplyByNumber(int* number, int& size, int n, int* result);

// �������
void Division(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result_list, int& sizelr);

