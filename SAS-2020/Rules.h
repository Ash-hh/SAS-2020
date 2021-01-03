#pragma once

#include "Greibach.h"
#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'),				// стартовый символ / дно стека
		6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, 3,		// структура программы
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),

			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,			// конструкции в функциях
			16,
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(6, TS('i'), TS('='), TS('v'), TS('i'), TS(';'), NS('N')),		
			Rule::Chain(5, TS('i'), TS('='), TS('v'), TS('i'), TS(';')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),

			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),


			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),

			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),

			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(8, TS('d'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),


			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),

			Rule::Chain(9, TS('c'), TS('('), TS('i'), TS('w'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS('c'), TS('('), TS('i'), TS('w'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2,			// выражения 
			8,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))

		),
		Rule(NS('M'), GRB_ERROR_SERIES + 3,			// знаки
			4,
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M')),
			Rule::Chain(2, TS('w'), NS('E')),
			Rule::Chain(3, TS('w'), NS('E'), NS('M'))
		),

		Rule(NS('F'), GRB_ERROR_SERIES + 4,			// параметры функции
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 5,			//	параметры в фактическом вызове функции
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		)
	);
}