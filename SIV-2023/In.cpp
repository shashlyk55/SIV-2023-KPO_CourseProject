#include "pch.h"
#include "In.h"
#include "Error.h"
#include <fstream>
#include <string>
#include <iostream>

namespace In
{

	IN GetIn(wchar_t infile[], wchar_t outfile[])
	{
		int currentLine = 0, currentCol = 0;
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };
		std::ifstream in(infile);
		if (in.fail())
			throw ERROR_THROW(20);

		std::string fulltext;
		std::string temp;
		while (!in.eof())
		{
			Info.lines++;

			std::getline(in, temp);
			temp += '\n';
			fulltext += temp;
		}

		Info.text = new unsigned char[fulltext.size() + 1];
		unsigned char* Ptemp = Info.text;

		for (int i = 0; i < fulltext.size(); ++i)
		{
			if (Info.code[(unsigned char)fulltext[i]] == IN::F)
			{
				throw ERROR_THROW_IN(110, currentLine, currentCol)
			}
			else if (Info.code[(unsigned char)fulltext[i]] == IN::I)
				++Info.ignor;
			else if (Info.code[(unsigned char)fulltext[i]] == IN::T)
			{
				*Ptemp = fulltext[i];
				++Ptemp;
			}
			else
			{
				*Ptemp = Info.code[(unsigned char)fulltext[i]];
				++Ptemp;
			}
			if (fulltext[i] == '\n')
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}



		*Ptemp = IN_CODE_ENDL;
		Info.size = strlen((char*)Info.text) - Info.lines;

		in.close();
		return Info;
	}
}