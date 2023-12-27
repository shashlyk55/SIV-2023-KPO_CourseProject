#include "pch.h"

namespace LT
{
	LexTable Create(int size)								//	�-��� �������� ������� ������
	{
		if (size > LT_MAXSIZE)								//	������, ���� size > LT_MAXSIZE
			throw ERROR_THROW(111);

		LexTable lextable;									//	�������� ������� ������
		lextable.maxsize = size;							//	������ ������� ������
		lextable.size = 0;									//	������� ������ ������� ������
		lextable.table = new Entry[lextable.maxsize];		//	������ ����� ������ ������

		return lextable;									//	���������� ����������� ���������
	}

	void Add(LexTable& lextable, Entry entry)				//	���������� ������ � ������� ������
	{
		if (lextable.size > lextable.maxsize)				//	��������: ���� �� ��������� ����� � ������� ������
			throw ERROR_THROW(112);							//	���� ���, �� ������

		lextable.table[lextable.size] = entry;				//	���������� ������ � ������� ��� �������� = �������� ������� �������
		lextable.size++;									//	���������� �������� ������� �������, �.�. ���� ��������� ����� ������
	}

	Entry GetEntry(LexTable& lextable, int n)				//	��������� ������ ������� ������
	{
		if (n > (lextable.size - 1))						//	��������: ���� �� ������ � ����� ������� ������ � ������� ������
			throw ERROR_THROW(113);							//	���� ���, �� ������

		return lextable.table[n];							//	���������� ������ ������� ���������������
	}

	void Delete(LexTable& lextable)							//	�������� ������� ������ (������������ ������)
	{
		delete[] lextable.table;							//  ������������ ����� ���������� ������
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
		file << '|' << std::setfill(' ') << std::setw(5) << std::left << "�" << '|' << std::setw(9) << std::left << "Line" << '|'
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