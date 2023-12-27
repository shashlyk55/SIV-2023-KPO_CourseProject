#pragma once
#include "Greibach.h"

#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), TS('$'),
		9,
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // Неверная структура программы
			14,
			Rule::Chain(5, TS(LEX_MAIN), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(6, TS(LEX_MAIN), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS(LEX_SHORT), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS(LEX_SHORT), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(10, TS(LEX_BOOL), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS(LEX_BOOL), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(10, TS(LEX_STRING), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS(LEX_STRING), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(11, TS(LEX_SHORT), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS(LEX_SHORT), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(11, TS(LEX_BOOL), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS(LEX_BOOL), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(11, TS(LEX_STRING), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS(LEX_STRING), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,    // Конструкции в функциях
			22,
			Rule::Chain(5, TS(LEX_NEW), NS('T'), TS(LEX_ID), TS(';'), NS('N')),
			Rule::Chain(7, TS(LEX_NEW), NS('T'), TS(LEX_ID), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS(LEX_NEW), NS('T'), TS(LEX_ID), TS(';')),
			Rule::Chain(6, TS(LEX_NEW), NS('T'), TS(LEX_ID), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS(LEX_ID), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS(LEX_ID), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS(LEX_PRINT), NS('L'), TS(';'), NS('N')),
			Rule::Chain(3, TS(LEX_PRINT), NS('L'), TS(';')),
			Rule::Chain(6, TS(LEX_POW), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS(LEX_POW), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS(LEX_ABS), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS(LEX_ABS), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS(LEX_ID), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS(LEX_ID), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(5, TS(LEX_ID), TS('('), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS(LEX_ID), TS('('), TS(')'), TS(';')),
			Rule::Chain(6, TS(LEX_IF), NS('Q'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(5, TS(LEX_IF), NS('Q'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(9, TS(LEX_IF), NS('Q'), TS('{'), NS('N'), TS('}'), TS(LEX_ELSE), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS(LEX_IF), NS('Q'), TS('{'), NS('N'), TS('}'), TS(LEX_ELSE), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(4, TS(LEX_RETURN), NS('L'), TS(';'), NS('N')),
			Rule::Chain(3, TS(LEX_RETURN), NS('L'), TS(';'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,    // Ошибка в выражении
			14,
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(1, TS(LEX_LITERAL)),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS(LEX_ID), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS(LEX_ID), TS('('), TS(')')),
			Rule::Chain(4, TS(LEX_POW), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('a'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS(LEX_ID), NS('M')),
			Rule::Chain(2, TS(LEX_LITERAL), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS(LEX_ID), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS(LEX_ID), TS('('), TS(')'), NS('M')),
			Rule::Chain(5, TS(LEX_POW), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(5, TS(LEX_ABS), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 3,    // Ошибка в параметрах функции
			6,
			Rule::Chain(2, TS(LEX_SHORT), TS(LEX_ID)),
			Rule::Chain(2, TS(LEX_STRING), TS(LEX_ID)),
			Rule::Chain(2, TS(LEX_BOOL), TS(LEX_ID)),
			Rule::Chain(4, TS(LEX_SHORT), TS(LEX_ID), TS(','), NS('F')),
			Rule::Chain(4, TS(LEX_STRING), TS(LEX_ID), TS(','), NS('F')),
			Rule::Chain(4, TS(LEX_BOOL), TS(LEX_ID), TS(','), NS('F'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,    // Ошибка в параметрах вызываемой функции 
			12,
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(1, TS(LEX_LITERAL)),
			Rule::Chain(3, TS(LEX_ID), TS(','), NS('W')),
			Rule::Chain(3, TS(LEX_LITERAL), TS(','), NS('W')),
			Rule::Chain(3, TS(LEX_ID), TS('('), TS(')')),
			Rule::Chain(5, TS(LEX_ID), TS('('), TS(')'), TS(','), NS('W')),
			Rule::Chain(4, TS(LEX_ID), TS('('), NS('W'), TS(')')),
			Rule::Chain(6, TS(LEX_ID), TS('('), NS('W'), TS(')'), TS(','), NS('W')),
			Rule::Chain(4, TS(LEX_POW), TS('('), NS('W'), TS(')')),
			Rule::Chain(6, TS(LEX_POW), TS('('), NS('W'), TS(')'), TS(','), NS('W')),
			Rule::Chain(4, TS(LEX_ABS), TS('('), NS('W'), TS(')')),
			Rule::Chain(6, TS(LEX_ABS), TS('('), NS('W'), TS(')'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,    // Оператор
			16,
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(2, TS('%'), NS('E')),
			Rule::Chain(3, TS('%'), NS('E'), NS('M')),
			Rule::Chain(2, TS(LEX_NOTEQUAL), NS('L')),
			Rule::Chain(2, TS(LEX_EQUALEQUAL), NS('L')),
			Rule::Chain(2, TS('>'), NS('L')),
			Rule::Chain(2, TS('<'), NS('L')),
			Rule::Chain(2, TS(LEX_MOREEQUAL), NS('L')),
			Rule::Chain(2, TS(LEX_LESSEQUAL), NS('L'))
		),
		Rule(
			NS('Q'), GRB_ERROR_SERIES + 6,		// Условные операторы
			6,									// Q->  (L<L)  |  (L>L)
			Rule::Chain(5, TS('('), NS('L'), TS('<'), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS('>'), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS(LEX_NOTEQUAL), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS(LEX_EQUALEQUAL), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS(LEX_MOREEQUAL), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS(LEX_LESSEQUAL), NS('L'), TS(')'))
		),
		Rule(
			NS('L'), GRB_ERROR_SERIES + 6,		// Литералы и идентификаторы
			2,									// L->  (l)  |  (i)
			Rule::Chain(1, TS(LEX_LITERAL)),
			Rule::Chain(1, TS(LEX_ID))
		),
		Rule(
			NS('T'), GRB_ERROR_SERIES + 7,
			3,
			Rule::Chain(1, TS(LEX_SHORT)),
			Rule::Chain(1, TS(LEX_STRING)),
			Rule::Chain(1, TS(LEX_BOOL))
		)
	);
}