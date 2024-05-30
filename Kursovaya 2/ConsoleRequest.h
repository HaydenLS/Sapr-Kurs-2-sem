// Здесь все что связано с запросами и так далее.

#pragma once
#include "Methods.h"
#include "Operations.h"

// Превращает списки в массивы чисел.
void CreateArray(ListH& l1, ListH& l2, int* number1, int sizel1, int* number2, int sizel2);

// Создать из Int список
void MakeList(ListH& list, int* number, int size);

// Выполнение запроса.
void DoRequest(ListV& list, ListH& request);

// Читает файл с запросом.
void ReadRequest(ListV& requests);

// Основной метод с запросами из файла.
void RequestHandler(ListV& list);
