// ����� ��� ��� ������� � ��������� � ��� �����.

#pragma once
#include "Methods.h"
#include "Operations.h"

// ���������� ������ � ������� �����.
void CreateArray(ListH& l1, ListH& l2, int* number1, int sizel1, int* number2, int sizel2);

// ������� �� Int ������
void MakeList(ListH& list, int* number, int size);

// ���������� �������.
void DoRequest(ListV& list, ListH& request);

// ������ ���� � ��������.
void ReadRequest(ListV& requests);

// �������� ����� � ��������� �� �����.
void RequestHandler(ListV& list);
