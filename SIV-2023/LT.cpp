#include "pch.h"

namespace LT
{
	LexTable Create(int size)								//	Ф-ция создания таблицы лексем
	{
		if (size > LT_MAXSIZE)								//	Ошибка, если size > LT_MAXSIZE
			throw ERROR_THROW(111);

		LexTable lextable;									//	Создание таблицы лексем
		lextable.maxsize = size;							//	Размер таблицы лексем
		lextable.size = 0;									//	Текущий размер таблица лексем
		lextable.table = new Entry[lextable.maxsize];		//	Массив строк таблиц лексем

		return lextable;									//	Возвращает заполненную структуру
	}

	void Add(LexTable& lextable, Entry entry)				//	Добавление строки в таблицу лексем
	{
		if (lextable.size > lextable.maxsize)				//	Проверка: есть ли свободное место в таблице лексем
			throw ERROR_THROW(112);							//	Если нет, то ошибка

		lextable.table[lextable.size] = entry;				//	Добавление строки в таблицу под индексом = текущему размеру таблицы
		lextable.size++;									//	Увеличение текущего размера таблицы, т.к. была добавлена новая строка
	}

	Entry GetEntry(LexTable& lextable, int n)				//	Получение строки таблицы лексем
	{
		if (n > (lextable.size - 1))						//	Проверка: есть ли строка с таким номером входит в таблицу лексем
			throw ERROR_THROW(113);							//	Если нет, то ошибка

		return lextable.table[n];							//	Возвращает строку таблицы идентификаторов
	}

	void Delete(LexTable& lextable)							//	Удаление таблицы лексем (Освобождение памяти)
	{
		delete[] lextable.table;							//  Освобождение ранее выделенной памяти
	}

	void SaveLexTableInFile(LexTable lextable, wchar_t outfile[])
	{
		std::ofstream out(outfile);
		if (!out.is_open())
			throw ERROR_THROW(22);

		int line = 0;
		out << std::right << std::setw(3) << line << "  ";
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].sn == line)
			{
				out << lextable.table[i].lexema;
			}
			else
			{
				out << std::endl;
				line += (lextable.table[i].sn - line);
				out << std::right << std::setw(3) << line << "  " << lextable.table[i].lexema;
			}
		}
		out.close();
	}

	void SaveToFile(LexTable& lextable, wchar_t outfile[])
	{
		std::ofstream file(outfile, std::ios_base::app);
		if (!file.is_open())
			throw ERROR_THROW(22);

		file << std::setfill('=') << std::setw(23) << "LEX TABLE" << std::setw(17) << "\n\n";
		file << '+' << std::setfill('-') << std::setw(6) << '+' << std::setw(10) <<
			'+' << std::setw(10) << '+' << std::setw(11) << '+' << std::endl;
		file << '|' << std::setfill(' ') << std::setw(5) << std::left << "№" << '|' << std::setw(9) << std::left << "Line" << '|'
			<< std::setw(9) << std::left << "Lexema" << '|' << std::setw(10) << std::left << "ID from IT" << '|' << std::endl;

		for (int i = 0; i < lextable.size; i++)
		{
			file << '|' << std::setfill(' ') << std::setw(5) << std::left << i << '|' << std::setw(9) << std::left << lextable.table[i].sn << '|'
				<< std::setw(9) << std::left << lextable.table[i].lexema << '|';

			if (lextable.table[i].idxTI == TI_NULLIDX)
				file << std::setw(10) << std::left << '-' << '|' << std::endl;
			else
				file << std::setw(10) << std::left << lextable.table[i].idxTI << '|' << std::endl;
		}

		file.close();
	}

	Entry CreateEntry(char lexema, int line)
	{
		Entry entry;
		entry.lexema = lexema;
		entry.sn = line;
		entry.idxTI = LT_TI_NULLTDX;

		return entry;
	}

	Entry CreateEntry(char lexema, int line, int idTI)
	{
		Entry result;
		result.lexema = lexema;
		result.sn = line;
		result.idxTI = idTI;

		return result;
	}
}