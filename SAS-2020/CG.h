#pragma once

#include "TI.h"
#include "LT.h"
#include <iostream>
#include "Parm.h"
#include <fstream>
#include <string.h>

namespace Code
{
	struct Gen
	{
		std::ofstream* stream;

		std::string start = "<html> <head> <title> SAS-2020 </title> </head><body onload='main'><script> ";
 
		std::string finish = "</script></body> </html>";
	};

	void Generation(IT::IdTable idtable, LT::LexTable lextable, Parm::PARM parm);

	void GetID(Gen& gen, IT::IdTable idtable, LT::LexTable lextable, int startPos);

	int GetValue(Gen& gen, IT::IdTable idtable, LT::LexTable lextable, int startPos);

	int GetFunction(Gen& gen, IT::IdTable idtable, LT::LexTable lextable,int startPos);

	int GetCycle(Gen& gen, IT::IdTable idtable, LT::LexTable lextable, int startPos);
}