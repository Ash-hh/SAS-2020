#pragma once
#include "LT.h"
#include "TI.h"

namespace Polish
{

	bool StringCheck(char* str);

	void Notation(IT::IdTable& idtable, LT::LexTable& lextable);
	
	bool PolishNotation(int startposition, IT::IdTable& idtable, LT::LexTable& lextable);
}