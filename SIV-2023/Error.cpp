#include "pch.h"
#include "Error.h"
#include <iostream>
#include <cstring>

namespace Error
{
	// 0-99		 Cистемные ошибки
	// 100-109	 Ошибки параметров
	// 110-119	 Ошибки открытия и чтения файлов
	// 120-129	 Ошибки заполнения таблиц Лексем и Идентификаторов
	// 130-139	 Ошибки заполнения таблицы токенов

	// Таблица ошибок
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		// Код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(0,"Системная ошибка: Недопустимый код ошибки"),
		ERROR_ENTRY(1,"Системная ошибка: Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3),
		ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY(10, "Ошибка параметра: Параметр -in должен быть задан"),
		ERROR_ENTRY(11, "Ошибка параметра: Превышена длина входного параметра"),
		ERROR_ENTRY(12, "Ошибка параметра: Параметр -out должен быть задан"),
		ERROR_ENTRY_NODEF(13),
		ERROR_ENTRY_NODEF(14), ERROR_ENTRY_NODEF(15), ERROR_ENTRY_NODEF(16), ERROR_ENTRY_NODEF(17),
		ERROR_ENTRY_NODEF(18), ERROR_ENTRY_NODEF(19),
		ERROR_ENTRY(20, "Ошибка файла: Ошибка при открытии файла с исходным кодом (-in:)"),
		ERROR_ENTRY(21, "Ошибка файла: Ошибка при создании файла протокола (-log:)"),
		ERROR_ENTRY(22, "Ошибка файла: Ошибка при открытии файла с таблицей лексем (-lex:)"),
		ERROR_ENTRY(23, "Ошибка файла: Ошибка при открытии файла с таблицей идентификаторов (-id:)"),
		ERROR_ENTRY_NODEF(24), ERROR_ENTRY_NODEF(25), ERROR_ENTRY_NODEF(26),
		ERROR_ENTRY_NODEF(27), ERROR_ENTRY_NODEF(28), ERROR_ENTRY_NODEF(29),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY_NODEF10(100),
		ERROR_ENTRY(110, "Ошибка лексического анализатора: Недопустимый символ в исходном файле (-in:)"),
		ERROR_ENTRY(111, "Ошибка лексического анализатора: Превышена емкость таблицы лексем"),
		ERROR_ENTRY(112, "Ошибка лексического анализатора: Превышено количество строк в таблице лексем"),
		ERROR_ENTRY(113, "Ошибка лексического анализатора: В таблице лексем отсутствует строка с заданным номером"),
		ERROR_ENTRY(114, "Ошибка лексического анализатора: Превышена емкость таблицы идентификаторов"),
		ERROR_ENTRY(115, "Ошибка лексического анализатора: Превышено количество строк в таблице идентификаторов"),
		ERROR_ENTRY(116, "Ошибка лексического анализатора: В таблице идентификаторов отсутствует строка с заданным номером"),
		ERROR_ENTRY(117, "Ошибка лексического анализатора: Не удалось определить тип лексемы"),
		ERROR_ENTRY(118, "Ошибка лексического анализатора: Превышена емкость таблицы токенов"),
		ERROR_ENTRY(119, "Ошибка лексического анализатора: Превышено количество токенов в таблице токенов"),
		ERROR_ENTRY(120, "Ошибка лексического анализатора: Ошибка с разбиением исходного текста на токены"),
		ERROR_ENTRY(121, "Ошибка лексического анализатора: Ошибка с разбором строкового литерала"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124), ERROR_ENTRY_NODEF(125),
		ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "Ошибка семантического анализа: Превышена длина строки в 255 символов"),
		ERROR_ENTRY(131, "Ошибка семантического анализа: Функция main уже имеет реализацию"),
		ERROR_ENTRY(132, "Ошибка семантического анализа: Превышена длина лексемы"),
		ERROR_ENTRY(133, "Ошибка семантического анализа: Превышено значение целочисленного литерала (2 byte)"),
		ERROR_ENTRY(134, "Ошибка семантического анализа: Не найдена точка входа в программу (main)"),
		ERROR_ENTRY(135, "Ошибка семантического анализа: Идентификатор с таким именем не найден"),
		ERROR_ENTRY(136, "Ошибка семантического анализа: Повторное объявление идентификатора"),
		ERROR_ENTRY(137, "Ошибка семантического анализа: Несоответствие типов в выражении"),
		ERROR_ENTRY(138, "Ошибка семантического анализа: Слишком много параметров в функции"),
		ERROR_ENTRY(139, "Ошибка семантического анализа: Превышено количество функций"),
		ERROR_ENTRY(140, "Ошибка семантического анализа: Несоответствие параметров объявленной и вызываемой функций"),
		ERROR_ENTRY(141, "Ошибка семантического анализа: Несоответствие параметров встроенной функции"),
		ERROR_ENTRY(142, "Ошибка семантического анализа: Левостороннее выражение не является идентификатором и не должно являться функцией"),
		ERROR_ENTRY(143, "Ошибка семантического анализа: Данная функция уже имеет реализацию"),
		ERROR_ENTRY(144, "Ошибка семантического анализа: В вызове функции отсутствуют ()"),
		ERROR_ENTRY(145, "Ошибка семантического анализа: Тип возвращаемого значения не соответствует типу функции"),
		ERROR_ENTRY(146, "Ошибка семантического анализа: Оператор не предназначен для работы со строками"),
		ERROR_ENTRY(147, "Ошибка семантического анализа: В функции отсутствует возвращаемое значение"),
		ERROR_ENTRY(148, "Ошибка семантического анализа: Деление на 0 недопустимо"),
		ERROR_ENTRY(149, "Ошибка семантического анализа: Недопустимый строковый литерал"),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Ошибка синтаксического анализа: Неверная структура программы"),
		ERROR_ENTRY(601, "Ошибка синтаксического анализа: Ошибка в конструкции блока кода"),
		ERROR_ENTRY(602, "Ошибка синтаксического анализа: Ошибка в выражении"),
		ERROR_ENTRY(603, "Ошибка синтаксического анализа: Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "Ошибка синтаксического анализа: Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605, "Ошибка синтаксического анализа: Ошибочный оператор"),
		ERROR_ENTRY(606, "Ошибка синтаксического анализа: Ошибка в условной конструкции"),
		ERROR_ENTRY(607, "Ошибка синтаксического анализа: Ошибка типа"),
		ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900),
	};

	ERROR geterror(int id)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			error_info.id = errors[id].id;
			strcpy(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col + 1;
			error_info.inext.line = line + 1;
			strcpy(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0;
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy(error_info.message, errors[0].message);
			return error_info;
		}
	};
};