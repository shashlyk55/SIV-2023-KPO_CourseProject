#pragma once
#include "pch.h"
#define TOKEN_SEPARATORS " \t\n+-*/%=<>(){},;!"
#define TOKEN_MAXSIZE 4096

namespace Tokens
{
	// Структура токена
	struct Token
	{
		char token[258];
		int length;
		int line;
		int linePosition;
	};
	// Структура таблицы токенов
	struct TokenTable
	{
		int maxsize;
		int size;
		Token* table;
	};
	// Создание таблицы токенов
	TokenTable CreateTokenTable(int size);
	// Добавление токенов
	void AddToken(TokenTable& tokens, char* token, int line, int linePosition, int length);
	// Процесс представления кода в виде потока токенов
	TokenTable Tokenize(In::IN in);
	// Проверка на сепаратор
	bool IsSeparator(char ch);
	// Создание токена состоящего из одного символа
	char* SepToken(char sep);
}