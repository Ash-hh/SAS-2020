#include "CG.h"
#include "Parm.h"
#include <iostream>
#include "LT.h"

namespace Code
{
	
	void Generation(IT::IdTable idtable, LT::LexTable lextable, Parm::PARM parm)
	{
		std::cout << lextable.size;
		Gen gen;

		int n; //индекс смещения таблицы лексем

		gen.stream = new std::ofstream(parm.generation);

		*gen.stream << gen.start;

		for (int i = 0; i < lextable.size; i++)
		{
			switch (lextable.table[i].lexema[0])
			{
			case LEX_FUNCTION: 
				i += GetFunction(gen, idtable, lextable, i);
				break;
			case LEX_LEFTBRACE: *gen.stream << "{" <<"\n"; break;
			case LEX_BRACELET:  *gen.stream << "}" << "\n"; break;
			case LEX_DEF:
				if (lextable.table[i + 2].lexema[0] != 'f');
				*gen.stream << "\n let "; break;
			case LEX_PRINT: *gen.stream << "\n document.write(  "; GetID(gen, idtable, lextable, ++i); *gen.stream<< ")"; break;
			case LEX_RETURN:  *gen.stream <<"\n return "; break;
			case LEX_CYCLE: i += GetCycle(gen, idtable, lextable, i); break;
			case LEX_ID: GetID(gen, idtable,lextable,i); break;
			case LEX_MAIN: *gen.stream << "\n function main()"; break;
			case LEX_INIT:i+=GetValue(gen, idtable, lextable, i); break;
			case LEX_SEMICOLON: *gen.stream << "; \n";  break;
			}
		}

		*gen.stream << gen.finish;
	}

	int GetFunction(Gen& gen, IT::IdTable idtable, LT::LexTable lextable, int startPos)
	{
		int n =startPos;
		
			*gen.stream << "\n function ";
			startPos++;
		
		
		*gen.stream << idtable.table[lextable.table[startPos++].idxTI].id <<"(";
		
		while ((char)lextable.table[startPos++].lexema[0] != ')')
		{
			if (lextable.table[startPos].lexema[0] == LEX_ID)
			{
				GetID(gen, idtable, lextable, startPos);
			}
			else if (lextable.table[startPos].lexema[0] == LEX_COMMA)
			{
				*gen.stream << ",";
			}
			
		}
		*gen.stream << ") \n";
		
		
		return startPos - n-1;
	}
	int GetValue(Gen& gen, IT::IdTable idtable, LT::LexTable lextable, int startPos)
	{
		*gen.stream << "=";
		int n = startPos+1;

		while ((char)lextable.table[startPos++].lexema[0] != ';')
		{
			switch (lextable.table[startPos].lexema[0])
			{
			case 'v': *gen.stream << lextable.table[startPos].operation; break;
			case 'i': GetID(gen, idtable, lextable, startPos); break;
			case ')': *gen.stream << ")"; break;
			case '(': *gen.stream << "("; break;
			case ',':  *gen.stream << ","; break;
			}
			
			
		}
		return startPos-n-1;
	}

	void GetID(Gen& gen, IT::IdTable idtable, LT::LexTable lextable, int startPos)
	{
		
		if (idtable.table[lextable.table[startPos].idxTI].idtype != IT::IDTYPE::L)
		{
			*gen.stream << " " << idtable.table[lextable.table[startPos].idxTI].id;
		}
		else if(idtable.table[lextable.table[startPos].idxTI].iddatatype == IT::IDDATATYPE::INT)
		{
			*gen.stream << idtable.table[lextable.table[startPos].idxTI].id ;
		}
		else if (idtable.table[lextable.table[startPos].idxTI].iddatatype == IT::IDDATATYPE::STR)
		{
			*gen.stream << '"'<<idtable.table[lextable.table[startPos].idxTI].id<<'"';
		}
		
	}

	int GetCycle(Gen& gen, IT::IdTable idtable, LT::LexTable lextable, int startPos)
	{
		int n = startPos;
		*gen.stream << "\n while(";
		startPos++;
		
		while ((char)lextable.table[startPos++].lexema[0] != ')')
		{
			if (lextable.table[startPos].lexema[0] == LEX_ID)
			{
				GetID(gen, idtable, lextable, startPos);
			}
			else if (lextable.table[startPos].lexema[0] == LEX_M )
			{
				*gen.stream << ">";
			}
			else if (lextable.table[startPos].lexema[0] == LEX_L)
			{
				*gen.stream << "<";
			}
			
		}
		*gen.stream << ") \n";
		startPos++;

		return startPos-n-2;
	}
}
