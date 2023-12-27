#include "pch.h"
#pragma once
#define MAX_FUNCTION_PARAMS_COUNT 8
#define MAX_FUNCTIONS_COUNT 255

struct Entry
{
	int index;
	int countOfParam;
	IT::IDDATATYPE types[MAX_FUNCTION_PARAMS_COUNT];
};

struct Functions
{
	int maxsize;
	int size;
	Entry* table;
};

// Создание таблицы функций
Functions Create(int size);
// Добавленеи строки в таблицу
void Add(Functions& functions, Entry entry);

// Запуск семантического анализатора
void CallSemantic(LT::LexTable& lextable, IT::IdTable& idtable);
// Проверка параметров библиотечных функций функции 
void CheckFuncParamCount(LT::LexTable& lextable, IT::IdTable& idtable);
// Проверка выражжений и соответсвия типов
void CheckTypeMatching(LT::LexTable& lextable, IT::IdTable& idtable);
// Проверка количества параметров в функции и последующее ее добавленеи в таблицу
void FillFunctions(Functions& functions, IT::IdTable& idtable, LT::LexTable& lextable);
// Проверка типа возвращаемого значения функции
void CheckReturnType(LT::LexTable& lextable, IT::IdTable& idtable);
// Проверка параметров и типов функций
void CheckFuncParam(Functions& functions, IT::IdTable& idtable, LT::LexTable& lextable);
// Сравнение параметров в вызываемой и объявленной функции
bool isEqual(Entry& entry1, Entry& entry2);