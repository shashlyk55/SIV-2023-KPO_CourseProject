#include "pch.h"

namespace Tokens
{
	// Этап разбиения кода на токены
	TokenTable Tokenize(In::IN in)
	{
		TokenTable tokens = CreateTokenTable(TOKEN_MAXSIZE);
		char buffer[256];
		bool isNegativeNum = false;
		int NumOfCharRecorded = 0;
		int CurrentLine = 0;
		int LinePosition = 0;


		for (int CharPointer = 0; in.text[CharPointer] != IN_CODE_ENDL; CharPointer++)
		{
			if (NumOfCharRecorded == 256)
				throw ERROR_THROW_IN(132, CurrentLine, LinePosition - NumOfCharRecorded);

			// Проверка на комментарий (комментарий начинается с //...)
			// комментарии пропускаем
			if (in.text[CharPointer] == '/' && in.text[CharPointer + 1] == '/')
			{
				while (in.text[CharPointer + 1] != '\n')
					CharPointer++;
				continue;
			}
			// Обработка сепараторов
			if (IsSeparator(in.text[CharPointer]))
			{
				if (in.text[CharPointer] == ' ' && isNegativeNum)
					continue;

				// создание токена ключевого слова
				if (NumOfCharRecorded)
				{
					buffer[NumOfCharRecorded] = IN_CODE_ENDL;
					AddToken(tokens, buffer, CurrentLine, LinePosition - NumOfCharRecorded, NumOfCharRecorded);
					NumOfCharRecorded = 0;
					isNegativeNum = false;
				}

				if (in.text[CharPointer] == '!' && in.text[CharPointer + 1] == '=')
				{
					buffer[0] = '!';
					buffer[1] = '=';
					buffer[2] = IN_CODE_ENDL;
					AddToken(tokens, buffer, CurrentLine, LinePosition - NumOfCharRecorded, 2);
					CharPointer++;

					continue;
				}

				if (in.text[CharPointer] == '=' && in.text[CharPointer + 1] == '=')
				{
					buffer[0] = '=';
					buffer[1] = '=';
					buffer[2] = IN_CODE_ENDL;
					AddToken(tokens, buffer, CurrentLine, LinePosition - NumOfCharRecorded, 2);
					CharPointer++;

					continue;
				}

				if (in.text[CharPointer] == '>' && in.text[CharPointer + 1] == '=')
				{
					buffer[0] = '>';
					buffer[1] = '=';
					buffer[2] = IN_CODE_ENDL;
					AddToken(tokens, buffer, CurrentLine, LinePosition - NumOfCharRecorded, 2);
					CharPointer++;

					continue;
				}

				if (in.text[CharPointer] == '<' && in.text[CharPointer + 1] == '=')
				{
					buffer[0] = '<';
					buffer[1] = '=';
					buffer[2] = IN_CODE_ENDL;
					AddToken(tokens, buffer, CurrentLine, LinePosition - NumOfCharRecorded, 2);
					CharPointer++;

					continue;
				}

				if (in.text[CharPointer] == '\n')
				{
					CurrentLine++;
					LinePosition = 0;
					continue;
				}
				// Отрицательное число
				if (in.text[CharPointer] == '-')
				{
					if (!isdigit(tokens.table[tokens.size - 1].token[tokens.table[tokens.size - 1].length - 1]) &&
						!isalpha(tokens.table[tokens.size - 1].token[tokens.table[tokens.size - 1].length - 1]) &&
						tokens.table[tokens.size - 1].token[tokens.table[tokens.size - 1].length - 1] != ')')
					{
						isNegativeNum = true;
						buffer[NumOfCharRecorded] = in.text[CharPointer];
						NumOfCharRecorded++;
						LinePosition++;
						continue;
					}
				}
				// Создание токенов для операторов состоящих из одного символа
				if (in.text[CharPointer] != ' ' && in.text[CharPointer] != '\t' && in.text[CharPointer] != '\n')
					AddToken(tokens, SepToken(in.text[CharPointer]), CurrentLine, LinePosition - NumOfCharRecorded, 1);

				LinePosition++;
				continue;
			}
			// создание токена для строкового литерала
			if (in.text[CharPointer] == '\"')
			{
				if (NumOfCharRecorded)
					throw ERROR_THROW_IN(120, CurrentLine, LinePosition);
				do
				{
					if (in.text[CharPointer] == '\n')
						throw ERROR_THROW_IN(121, CurrentLine, 0);
					if (NumOfCharRecorded == 256)
						throw ERROR_THROW_IN(130, CurrentLine, 0);

					buffer[NumOfCharRecorded] = in.text[CharPointer];
					CharPointer++;
					NumOfCharRecorded++;
					LinePosition++;
				} while (in.text[CharPointer] != '\"');

				buffer[NumOfCharRecorded] = in.text[CharPointer];
				NumOfCharRecorded++;

				buffer[NumOfCharRecorded] = IN_CODE_ENDL;
				AddToken(tokens, buffer, CurrentLine, LinePosition - NumOfCharRecorded, NumOfCharRecorded);
				NumOfCharRecorded = 0;

				continue;
			}

			buffer[NumOfCharRecorded] = in.text[CharPointer];
			NumOfCharRecorded++;
			LinePosition++;
		}
		return tokens;
	}

	// Проверка на сепараторы
	bool IsSeparator(char ch)
	{
		char separators[] = TOKEN_SEPARATORS;
		int index = 0;

		while (separators[index] != IN_CODE_ENDL)
		{
			if (ch == separators[index])
				return true;
			index++;
		}

		return false;
	}

	// Функция создания токенов для операторов состоящих из одного символа
	char* SepToken(char sep)
	{
		char* separator = new char[2];
		separator[0] = sep;
		separator[1] = IN_CODE_ENDL;

		return separator;
	}
	// Функция создания таблицы токенов
	TokenTable CreateTokenTable(int size)
	{
		if (size > TOKEN_MAXSIZE)
			throw ERROR_THROW(118);

		TokenTable tokentable;
		tokentable.maxsize = size;
		tokentable.size = 0;
		tokentable.table = new Token[tokentable.maxsize];

		return tokentable;
	}
	// Функция добавления токенов
	void AddToken(TokenTable& tokens, char* token, int line, int linePosition, int length)
	{
		if (tokens.size > tokens.maxsize)
			throw ERROR_THROW(119);

		Token item;
		strcpy(item.token, token);
		item.line = line;
		item.linePosition = linePosition;
		item.length = length;

		tokens.table[tokens.size] = item;
		tokens.size++;
	}
}