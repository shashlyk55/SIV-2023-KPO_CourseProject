#pragma once
#include "pch.h"
#include "IT.h"
#include "LT.h"
using namespace std;

namespace LA
{
	struct LEX
	{
		IT::IdTable idtable;
		LT::LexTable lextable;
		LEX();
		LEX(int lexTableSize, int idTableSize);
	};
	// Определяем тип лексемы
	char LexType(Tokens::Token token);
	// Заполнение таблиц
	LEX FillingInTables(Tokens::TokenTable tokenTable);
	// Поиск id в таблице
	int SearchID(stack<int> areaOfVisibility, string id, IT::IdTable& idTable);
	// Поиск id функции в таблице
	int SearchGlobalFunctionID(int globalAreaOfVisibility, string id, IT::IdTable& idTable);
}