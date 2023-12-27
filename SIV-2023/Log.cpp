#include "pch.h" 
#include "Log.h"
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>

namespace Log
{

	LOG getlog(wchar_t logfile[])
	{
		LOG temp;
		temp.stream = new std::ofstream(logfile);
		if (!temp.stream->is_open())
			throw ERROR_THROW(21);
		wcscpy_s(temp.logfile, logfile);
		return temp;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;

		if (log.stream == nullptr || !log.stream->is_open())
		{
			while (strlen(*ptr))
			{
				std::cout << *ptr;
				++ptr;
			}
		}
		else
		{
			while (strlen(*ptr))
			{
				*log.stream << *ptr;
				++ptr;
			}
		}
	}

	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		while (wcslen(*ptr))
		{
			char out[PARM_MAX_SIZE];
			size_t charsConverted = 0;
			wcstombs_s(&charsConverted, out, *ptr, PARM_MAX_SIZE);
			*log.stream << out;
			++ptr;
		}
		*log.stream << std::endl;
	}

	void WriteLog(LOG log)
	{
		time_t  t = time(nullptr);
		tm  now;
		localtime_s(&now, &t);
		char date[PARM_MAX_SIZE];
		strftime(date, PARM_MAX_SIZE, "%d.%m.%Y %H:%M:%S", &now);
		*log.stream << "-------------- Протокол ----------------\nДата: " << date << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "------------- Параметры ----------------" << std::endl;
		char out[PARM_MAX_SIZE];
		size_t charsConverted(0);
		wcstombs_s(&charsConverted, out, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.an, PARM_MAX_SIZE);
		*log.stream << "-an: " << out << std::endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---------- Исходные данные -------------" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано:     " << in.ignor << std::endl;
		*log.stream << "Количество строк:    " << in.lines << std::endl;
		*log.stream << "----------------------------------------" << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;

		if (!(log.stream == nullptr || !log.stream->is_open()))
		{
			*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		}
	}

	void Close(LOG log)
	{
		if (log.stream != nullptr)
		{
			log.stream->close();
			delete log.stream;
		}
	}
}