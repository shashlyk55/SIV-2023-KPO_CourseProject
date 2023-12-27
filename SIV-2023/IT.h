#pragma once

#define TI_MAXSIZE      4096                    
#define TI_INT_DEFAULT  0x00000000              
#define TI_STR_DEFAULT  0x00                    
#define TI_NULLIDX      0xffffffff              
#define TI_STR_MAXSIZE  255                     

namespace IT
{
	enum IDDATATYPE { UNDF = 0, SHORT = 1, STR = 2, BOOL = 3 };

	enum IDTYPE { N = 0, F = 1, V = 2, P = 3, L = 4 };		// типы идентификаторов: переменная, функция, параметр, литерал, не определено

	struct Entry
	{
		int         idxfirstLE;		// идекс первого вхождения в таблицу лексем
		std::string id;				// идентификатор
		IDDATATYPE  idDataType;		// тип данных
		IDTYPE      idType;			// тип идентиикатора
		struct
		{
			int vshort;				// целочисленное значение
			struct
			{
				int len;			// длин астроки
				std::string str;	// строка
			} vstr;
		} value;
	};

	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	void Delete(IdTable& idtable);
	void SaveToFile(IdTable& idtable, wchar_t outfile[]);

	Entry GetEntry(IdTable& idtable, int n);

	int IsId(IdTable& idtable, std::string id);

	Entry CreateEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType);
	Entry CreateEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, int vint);
	Entry CreateEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, std::string vstr);

}