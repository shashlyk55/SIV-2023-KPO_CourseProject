#include "pch.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
			throw ERROR_THROW(114);

		IdTable idtable;
		idtable.maxsize = size;
		idtable.size = 0;
		idtable.table = new Entry[idtable.maxsize];

		return idtable;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size > idtable.maxsize)
			throw ERROR_THROW(115);

		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n > (idtable.size - 1))
			throw ERROR_THROW(116);
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, std::string id)
	{
		if (idtable.size > 0)
		{
			for (int i = 0; i < idtable.size; i++)
			{
				if (idtable.table[i].id == id)
				{
					return i;
				}
			}
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}

	Entry CreateEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType)
	{
		Entry result;
		result.idxfirstLE = lineLT;
		result.id = id;
		result.idDataType = idDataType;
		result.idType = idType;
		return result;
	}

	Entry CreateEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, int vint)
	{
		Entry result;
		result.idxfirstLE = lineLT;
		result.id = id;
		result.idDataType = idDataType;
		result.idType = idType;
		result.value.vshort = vint;
		return result;
	}

	Entry CreateEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, std::string vstr)
	{
		Entry result;
		result.idxfirstLE = lineLT;
		result.id = id;
		result.idDataType = idDataType;
		result.idType = idType;
		result.value.vstr.str = vstr;
		result.value.vstr.len = vstr.size();
		return result;
	}

	void SaveToFile(IdTable& idtable, wchar_t outfile[])
	{
		std::ofstream file(outfile, std::ios_base::app);
		if (!file.is_open())
			throw ERROR_THROW(23);

		int iddatatype;
		int idtype;
		int counter = 0;

		file << std::setfill('=') << std::setw(43) << "ID TABLE" << std::setw(48) << "\n\n";
		file << '+' << std::setfill('-') << std::setw(6) << '+' << std::setw(13) << '+' << std::setw(16) << '+' << std::setw(16) << '+'
			<< std::setw(16) << '+' << std::setw(21) << '+' << std::endl;
		file << '|' << std::setfill(' ') << std::setw(5) << std::left << "¹" << '|' << std::setw(12) << std::left << "Name" << '|'
			<< std::setw(15) << std::left << "Type" << '|' << std::setw(15) << std::left << "Data type" << '|' <<
			std::setw(15) << std::left << "First in LT" << '|' << std::setw(20) << std::left << "Value" << '|' << std::endl;

		for (int i = 0; i < idtable.size; i++)
		{
			iddatatype = idtable.table[i].idDataType;
			idtype = idtable.table[i].idType;
			file << '|' << std::setfill(' ') << std::setw(5) << std::left << i;
			file << '|' << std::setfill(' ') << std::setw(12) << std::left << idtable.table[i].id;

			switch (idtype)
			{
			case IDTYPE::F:
				file << '|' << std::setw(15) << std::left << "Function";
				break;
			case IDTYPE::V:
				file << '|' << std::setw(15) << std::left << "Variable";
				break;
			case IDTYPE::P:
				file << '|' << std::setw(15) << std::left << "Parameter";
				break;
			case IDTYPE::L:
				file << '|' << std::setw(15) << std::left << "Literal";
				break;
			case IDTYPE::N:
				file << '|' << std::setw(15) << std::left << "Undefined";
				break;
			}

			switch (iddatatype)
			{
			case IDDATATYPE::STR:
				file << '|' << std::setw(15) << std::left << "Str";
				break;
			case IDDATATYPE::SHORT:
				file << '|' << std::setw(15) << std::left << "Int";
				break;
			case IDDATATYPE::BOOL:
				file << '|' << std::setw(15) << std::left << "Bool";
				break;
			case IDDATATYPE::UNDF:
				file << '|' << std::setw(15) << std::left << "Undefined";
				break;
			}

			file << '|' << std::setw(15) << std::left << idtable.table[i].idxfirstLE;

			if (idtype == IDTYPE::L)
			{
				switch (iddatatype)
				{
				case IDDATATYPE::BOOL:
					if (idtable.table[i].value.vshort)
						file << '|' << std::setw(20) << std::left << "true";
					else
						file << '|' << std::setw(20) << std::left << "false";
					break;
				case IDDATATYPE::SHORT:
					file << '|' << std::setw(20) << std::left << idtable.table[i].value.vshort;
					break;
				case IDDATATYPE::STR:
					file << '|' << std::setw(20) << std::left << idtable.table[i].value.vstr.str;
					break;
				}
			}
			else
			{
				file << '|' << std::setw(20) << std::left << '-';
			}
			file << '|';
			file << std::endl;
		}
		file.close();
	}
}