#include "pch.h"
using namespace std;

namespace LA
{
	// КОнструктор таблиц
	LEX::LEX(int lexTableSize, int idTableSize)
	{
		this->lextable = LT::Create(lexTableSize);
		this->idtable = IT::Create(idTableSize);
	};
	LEX::LEX() { };

	GRAPH graph[] =
	{
		{ LEX_SHORT, FST::FST(GRAPH_SHORT) },
		{ LEX_STRING, FST::FST(GRAPH_STRING) },
		{ LEX_BOOL, FST::FST(GRAPH_BOOL) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_NEW, FST::FST(GRAPH_NEW) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_PRINT, FST::FST(GRAPH_PRINT) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_BOOL_TRUE) },
		{ LEX_LITERAL, FST::FST(GRAPH_BOOL_FALSE) },
		{ LEX_SEMICOLON, FST::FST(GRAPH_SEMICOLON) },
		{ LEX_COMMA, FST::FST(GRAPH_COMMA) },
		{ LEX_LEFTBRACE, FST::FST(GRAPH_LEFTBRACE_OPEN) },
		{ LEX_RIGHTBRACE, FST::FST(GRAPH_RIGHTBRACE_CLOSE) },
		{ LEX_LEFTHESIS, FST::FST(GRAPH_LEFTHESIS_OPEN) },
		{ LEX_RIGHTHESIS, FST::FST(GRAPH_RIGHTHESIS_CLOSE) },
		{ LEX_PLUS, FST::FST(GRAPH_PLUS) },
		{ LEX_MINUS, FST::FST(GRAPH_MINUS) },
		{ LEX_STAR, FST::FST(GRAPH_STAR) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_DIRSLASH) },
		{ LEX_REMDIV, FST::FST(GRAPH_REMDIV) },
		{ LEX_LESS, FST::FST(GRAPH_LESS) },
		{ LEX_LESSEQUAL, FST::FST(GRAPH_LESSEQUAL) },
		{ LEX_MORE, FST::FST(GRAPH_MORE) },
		{ LEX_MOREEQUAL, FST::FST(GRAPH_MOREEQUAL) },
		{ LEX_EQUAL, FST::FST(GRAPH_EQUALS) },
		{ LEX_EQUALEQUAL, FST::FST(GRAPH_EQUALSEQUALS) },
		{ LEX_NOTEQUAL, FST::FST(GRAPH_NOTEQUALS) },
		{ LEX_IF, FST::FST(GRAPH_IF) },
		{ LEX_ELSE, FST::FST(GRAPH_ELSE) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL_2) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL_8) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL_16) },
		{ LEX_ABS, FST::FST(GRAPH_ABS) },
		{ LEX_POW, FST::FST(GRAPH_POW) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL_16) },
		{ LEX_ID, FST::FST(GRAPH_ID) }
	};

	// Определяем тип лексемы
	char LexType(Tokens::Token token)
	{
		for (int i = 0; i < LENGTHOF(graph); i++)
		{
			FST::FST fstlex = FST::FST(token.token, graph[i].graph);
			if (FST::execute(fstlex))
			{
				return graph[i].lex;
			}
		}
		throw ERROR_THROW_IN(117, token.line, 0);
	}

	LEX FillingInTables(Tokens::TokenTable tokenTable)
	{
		LEX lex = LEX(LT_MAXSIZE, TI_MAXSIZE);
		char lexema;
		string id;
		int lineIT = TI_NULLIDX;
		stack<int> areaOfVisibility;
		areaOfVisibility.push(0);
		int globalAreaOfVisibility = 0;
		char* currentVisibility = new char[0];
		IT::IDTYPE idType = IT::IDTYPE::P;
		IT::IDDATATYPE idDataType = IT::IDDATATYPE::UNDF;
		int isNotGlobal = 0;
		bool isMain = false;
		int numOfLit = 0;
		bool isDeclare = false;
		bool GlobalFunIsFound = false;

		for (int index = 0; index < tokenTable.size; index++)
		{
			switch (lexema = LexType(tokenTable.table[index]))
			{
			case LEX_ID:
				lineIT = SearchID(areaOfVisibility, string(tokenTable.table[index].token), lex.idtable);
				// Если id переменной не найден в IT то ищем id функции
				if (lineIT == TI_NULLIDX)
				{
					lineIT = SearchGlobalFunctionID(globalAreaOfVisibility, string(tokenTable.table[index].token), lex.idtable);
					if (lineIT != TI_NULLIDX)
						GlobalFunIsFound = true;
				}
				// Если id не найден в IT то это объявление
				if (lineIT == TI_NULLIDX && isDeclare || lineIT == TI_NULLIDX && !isNotGlobal)
				{
					lineIT = lex.idtable.size;
					id = string(tokenTable.table[index].token) + to_string(areaOfVisibility.top());
					IT::Add(lex.idtable, IT::CreateEntry(lex.lextable.size, id, idDataType, idType));
				}
				else if (lineIT == TI_NULLIDX)
				{
					throw ERROR_THROW_IN(135, tokenTable.table[index].line, tokenTable.table[index].linePosition);
				}
				// Если id есть в IT
				else if (lineIT != TI_NULLIDX && isDeclare)
				{
					if ((IT::GetEntry(lex.idtable, lineIT)).id == string(tokenTable.table[index].token) + to_string(areaOfVisibility.top()) || GlobalFunIsFound
						|| (IT::GetEntry(lex.idtable, lineIT)).id == string(tokenTable.table[index].token) + to_string(globalAreaOfVisibility) && ((IT::GetEntry(lex.idtable, lineIT)).idType == IT::IDTYPE::F)
						|| (IT::GetEntry(lex.idtable, lineIT)).id == string(tokenTable.table[index].token) + to_string(globalAreaOfVisibility) && ((IT::GetEntry(lex.idtable, lineIT)).idType == IT::IDTYPE::P) && (isNotGlobal == 1))
					{
						throw ERROR_THROW_IN(136, tokenTable.table[index].line, tokenTable.table[index].linePosition);
					}
					else
					{
						lineIT = lex.idtable.size;
						id = string(tokenTable.table[index].token) + to_string(areaOfVisibility.top());
						IT::Add(lex.idtable, IT::CreateEntry(lex.lextable.size, id, idDataType, idType));
					}
				}
				// Такая функция уже объявлена
				else if (lineIT != TI_NULLIDX && idType == IT::IDTYPE::F)
					throw ERROR_THROW_IN(143, tokenTable.table[index].line, tokenTable.table[index].linePosition);


				LT::Add(lex.lextable, LT::CreateEntry(lexema, tokenTable.table[index].line, lineIT));
				idType = IT::IDTYPE::P;
				idDataType = IT::IDDATATYPE::UNDF;
				GlobalFunIsFound = false;
				isDeclare = false;
				break;
			case LEX_LITERAL:
				// Строковый литерал
				if (tokenTable.table[index].token[0] == '"')
				{
					if (tokenTable.table[index].length == 2)
					{
						throw ERROR_THROW_IN(149, tokenTable.table[index].line, tokenTable.table[index].linePosition);
					}
					id = "str" + to_string(numOfLit++);
					IT::Add(lex.idtable, IT::CreateEntry(lex.lextable.size, id, IT::IDDATATYPE::STR, IT::IDTYPE::L, string(tokenTable.table[index].token)));
				}
				// Литерал bool
				else if (tokenTable.table[index].token[0] == 't' || tokenTable.table[index].token[0] == 'f')
				{
					bool vBool;
					if (tokenTable.table[index].token[0] == 't')
						vBool = true;
					else vBool = false;

					id = "bool" + to_string(numOfLit++);
					IT::Add(lex.idtable, IT::CreateEntry(lex.lextable.size, id, IT::IDDATATYPE::BOOL, IT::IDTYPE::L, vBool));
				}
				// Целочисленный литерал
				else
				{
					int vShort;
					switch (tokenTable.table[index].token[strlen(tokenTable.table[index].token) - 1])
					{
					case 'B':
						vShort = strtol(tokenTable.table[index].token, NULL, 2);
						break;
					case 'O':
						vShort = strtol(tokenTable.table[index].token, NULL, 8);
						break;
					case 'H':
						vShort = strtol(tokenTable.table[index].token, NULL, 16);
						break;
					default:
						vShort = strtol(tokenTable.table[index].token, NULL, 10);
						break;
					}
					if (vShort < -32768 || vShort > 32767)
						throw ERROR_THROW_IN(133, tokenTable.table[index].line, tokenTable.table[index].linePosition);
					id = "short" + to_string(numOfLit++);
					IT::Add(lex.idtable, IT::CreateEntry(lex.lextable.size, id, IT::IDDATATYPE::SHORT, IT::IDTYPE::L, vShort));
				}
				LT::Add(lex.lextable, LT::CreateEntry(lexema, tokenTable.table[index].line, lex.idtable.size - 1));
				break;
			default:
				LT::Add(lex.lextable, LT::CreateEntry(lexema, tokenTable.table[index].line));

				switch (lexema)
				{
				case LEX_LEFTBRACE:
					areaOfVisibility.push(lex.lextable.size - 1);
					isNotGlobal++;
					break;
				case LEX_RIGHTBRACE:
					areaOfVisibility.pop();
					isNotGlobal--;
					break;
				case LEX_SHORT:
					idDataType = IT::IDDATATYPE::SHORT;
					break;
				case LEX_STRING:
					idDataType = IT::IDDATATYPE::STR;
					break;
				case LEX_BOOL:
					idDataType = IT::IDDATATYPE::BOOL;
					break;
				case LEX_NEW:
					idType = IT::IDTYPE::V;
					isDeclare = true;
					break;
				case LEX_FUNCTION:
					idType = IT::IDTYPE::F;
					if (!isNotGlobal)
					{
						globalAreaOfVisibility++;
						if (areaOfVisibility.top() != 0)
							areaOfVisibility.pop();
						areaOfVisibility.push(globalAreaOfVisibility);
					}
					break;
				case LEX_MAIN:
					if (isMain)
						throw ERROR_THROW_IN(131, tokenTable.table[index].line, tokenTable.table[index].linePosition);
					isMain = true;
					if (!isNotGlobal)
					{
						globalAreaOfVisibility++;
						if (areaOfVisibility.top() != 0)
							areaOfVisibility.pop();
						areaOfVisibility.push(globalAreaOfVisibility);
					}
					break;
				default:
					break;
				}

				break;
			}
		}
		if (!isMain)
			throw ERROR_THROW(134);
		return lex;
	}

	// Поиск id в IT
	int SearchID(stack<int> areaOfVisibility, string id, IT::IdTable& idtable)
	{
		char* currentVisibility = new char[0];
		string searchingID;
		int result = TI_NULLIDX;
		while (areaOfVisibility.top() != 0)
		{
			itoa(areaOfVisibility.top(), currentVisibility, 10);
			areaOfVisibility.pop();
			searchingID = id + string(currentVisibility);
			result = IT::IsId(idtable, searchingID);
			if (result != TI_NULLIDX)
				return result;

		}
		return result;
	}

	// Поиск id функции в IT
	int SearchGlobalFunctionID(int globalAreaOfVisibility, string id, IT::IdTable& idtable)
	{
		int result = TI_NULLIDX;
		string searchingID;
		for (int i = 1; i < globalAreaOfVisibility; i++)
		{
			searchingID = id + to_string(i);
			result = IT::IsId(idtable, searchingID);
			if (result != TI_NULLIDX && idtable.table[result].idType == IT::IDTYPE::F)
				return result;
		}
		return TI_NULLIDX;
	}
}