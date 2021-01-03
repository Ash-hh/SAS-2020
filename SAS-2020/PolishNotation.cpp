#include "PolishNotation.h"
#include <string.h>
#include "In.h"
#include <iostream>
#include <stack>

namespace Polish
{

	bool StringCheck(char* str)
	{
		for (int f = 0; f < strlen(str); f++)
		{
			if (str[f] == 'v' || str[f] == '(')
			{
				return true;
			}
		}
		return false;
	}

	bool PolishNotation(int startposition, IT::IdTable& idtable, LT::LexTable& lextable)
	{
		
		std::stack <char> notation;
		int bpriority = -1; //приоритет предыдущей запси
		int position = startposition; //позиция в таблице лексем
		char* resultstr = new char[IN_MAX_LEN_TEXT]; //результирующшая строка
		int resultsize = 0; //размер результирующей строки
		bool func = false; //вхождение идентификатора функции
		int nsize = 0; //последовательность n для функции 
		int fucntionpos = 0; //позиция id функции в таблице лексем
		while (lextable.table[position].lexema[0] != ';')
		{
			if (lextable.table[position].lexema[0] == ',')
			{
				position++;
			}

			if (lextable.table[position].lexema[0] == 'i')
			{
				if (func)
				{
					nsize++;
				}
				if (idtable.table[lextable.table[position].idxTI].idtype == IT::IDTYPE::F)
				{
					func = true;
					nsize = 0;
					fucntionpos = position;
					lextable.table[position].lexema[0] = '@';
					lextable.table[position + 1].lexema[0] = '[';
					lextable.table[position + 1].priority = 4;
					
					int j = position+2;
					while (lextable.table[j].lexema[0] != ')')
					{
						j++;
					}
					lextable.table[j].lexema[0] = ']';
					lextable.table[j].priority = 4;
					

				}
				else
				{
					resultstr[resultsize++] = lextable.table[position].lexema[0];
				}
				
			}
			else
			{
				if (bpriority >= lextable.table[position].priority && lextable.table[position].lexema[0] != ')' && lextable.table[position].lexema[0] !='(' && lextable.table[position].lexema[0] != '[' && lextable.table[position].lexema[0] != ']')
				{					
					while (!notation.empty())
					{
						resultstr[resultsize++] = notation.top();
						notation.pop();
					}
					notation.push(lextable.table[position].lexema[0]);
					bpriority = lextable.table[position].priority;
				}
				else if (lextable.table[position].lexema[0] ==')' || lextable.table[position].lexema[0] == ']')
				{
					char buff;
					

					while (true)
					{
						
						buff = notation.top();
						if (buff != '(' && buff !='[')
						{
							resultstr[resultsize++] = notation.top();
							notation.pop();
						}	
						if (!notation.empty())
						{
							notation.pop();
						}
						
						break;
					}
					if (lextable.table[position].lexema[0] == ']')
					{
						func = false;
						resultstr[resultsize++] = lextable.table[fucntionpos].lexema[0];
						resultstr[resultsize++] = 48+nsize;
					}
				}
				else if (lextable.table[position].lexema[0] == '(' || lextable.table[position].lexema[0] == '[')
				{
					notation.push(lextable.table[position].lexema[0]);
					bpriority = lextable.table[position].priority;
				}
				else
				{
					notation.push(lextable.table[position].lexema[0]);
					bpriority = lextable.table[position].priority;
				}
			}
			position++;
		}
		while (!notation.empty())
		{
			resultstr[resultsize++] = notation.top();
			notation.pop();
		}
		resultstr[resultsize] = '\0';
		
		std::cout << resultstr << std::endl;
		return true;
	}

	

	void Notation(IT::IdTable& idtable, LT::LexTable& lextable)
	{
		bool isgood;
		int chainstart;
		char* str = new char[IN_MAX_LEN_TEXT];

		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema[0] == '=')
			{
				int j = i-1;
				int s = 0;
				int startposition = i + 1;
				while (lextable.table[j].lexema[0] != ';')
				{
					str[s] = lextable.table[j].lexema[0];
					j++;
					s++;
				}
				str[s] = '\0';
				i += j - i;
				
				isgood = StringCheck(str);
				if (isgood)
				{
					std::cout << str << std::endl;
					PolishNotation(startposition, idtable, lextable);
				}
				
			}
		}		
	}
}
