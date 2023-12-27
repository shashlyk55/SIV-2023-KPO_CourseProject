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
	// ���������� ��� �������
	char LexType(Tokens::Token token);
	// ���������� ������
	LEX FillingInTables(Tokens::TokenTable tokenTable);
	// ����� id � �������
	int SearchID(stack<int> areaOfVisibility, string id, IT::IdTable& idTable);
	// ����� id ������� � �������
	int SearchGlobalFunctionID(int globalAreaOfVisibility, string id, IT::IdTable& idTable);
}