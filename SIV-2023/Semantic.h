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

// �������� ������� �������
Functions Create(int size);
// ���������� ������ � �������
void Add(Functions& functions, Entry entry);

// ������ �������������� �����������
void CallSemantic(LT::LexTable& lextable, IT::IdTable& idtable);
// �������� ���������� ������������ ������� ������� 
void CheckFuncParamCount(LT::LexTable& lextable, IT::IdTable& idtable);
// �������� ���������� � ����������� �����
void CheckTypeMatching(LT::LexTable& lextable, IT::IdTable& idtable);
// �������� ���������� ���������� � ������� � ����������� �� ���������� � �������
void FillFunctions(Functions& functions, IT::IdTable& idtable, LT::LexTable& lextable);
// �������� ���� ������������� �������� �������
void CheckReturnType(LT::LexTable& lextable, IT::IdTable& idtable);
// �������� ���������� � ����� �������
void CheckFuncParam(Functions& functions, IT::IdTable& idtable, LT::LexTable& lextable);
// ��������� ���������� � ���������� � ����������� �������
bool isEqual(Entry& entry1, Entry& entry2);