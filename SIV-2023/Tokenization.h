#pragma once
#include "pch.h"
#define TOKEN_SEPARATORS " \t\n+-*/%=<>(){},;!"
#define TOKEN_MAXSIZE 4096

namespace Tokens
{
	// ��������� ������
	struct Token
	{
		char token[258];
		int length;
		int line;
		int linePosition;
	};
	// ��������� ������� �������
	struct TokenTable
	{
		int maxsize;
		int size;
		Token* table;
	};
	// �������� ������� �������
	TokenTable CreateTokenTable(int size);
	// ���������� �������
	void AddToken(TokenTable& tokens, char* token, int line, int linePosition, int length);
	// ������� ������������� ���� � ���� ������ �������
	TokenTable Tokenize(In::IN in);
	// �������� �� ���������
	bool IsSeparator(char ch);
	// �������� ������ ���������� �� ������ �������
	char* SepToken(char sep);
}