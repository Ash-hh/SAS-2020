#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cstring>
#include "FST.h"
#include "TI.h"
#include "Error.h"
#include <string.h>
#include "Log.h"



using namespace std;

namespace FST
{
	

	RELATION::RELATION(char c, short ns)
	{
		symbol = c;
		nnode = ns;
	};

	NODE::NODE()
	{
		n_relation = 0;
		RELATION* relations = NULL;
	};

	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++)
		{
			relations[i] = p[i];
		}
	};

	FST::FST(short ns, char* s, NODE n, ...)
	{
		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE* p = &n;

		for (int i = 0; i < ns; i++)
		{
			nodes[i] = p[i];
		}

		rstates = new short[nstates];	
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	};

	bool step(FST& fst, short*& rstates)
	{
		bool rc = false;
		swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
			{
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
				};
			};
		};
		return rc;
	};

	AL execute(FST& fst, AL& al)	//	распознавание цепочки
	{		
		
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			al.counter++;
			fst.position++;
			rc = step(fst, rstates); //	один шаг автомата	
			
		}
		delete[] rstates;
		al.isgood = (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
		return (al);
	};

	AL WordToLexem(char* str, int line, AL& al)
	{
		char* text = new char[IN_MAX_LEN_TEXT];

		FST integer(4, text, \
			NODE(1, RELATION('i', 1)), \
			NODE(1, RELATION('n', 2)), \
			NODE(1, RELATION('t', 3)), \
			NODE());

		FST string(7, text, \
			NODE(1, RELATION('s', 1)), \
			NODE(1, RELATION('t', 2)), \
			NODE(1, RELATION('r', 3)), \
			NODE(1, RELATION('i', 4)), \
			NODE(1, RELATION('n', 5)), \
			NODE(1, RELATION('g', 6)), \
			NODE());

		FST function(9, text, \
			NODE(1, RELATION('f', 1)), \
			NODE(1, RELATION('u', 2)), \
			NODE(1, RELATION('n', 3)), \
			NODE(1, RELATION('c', 4)), \
			NODE(1, RELATION('t', 5)), \
			NODE(1, RELATION('i', 6)), \
			NODE(1, RELATION('o', 7)), \
			NODE(1, RELATION('n', 8)), \
			NODE());

		FST declare(4, text, \
			NODE(1, RELATION('d', 1)), \
			NODE(1, RELATION('e', 2)), \
			NODE(1, RELATION('f', 3)), \
			NODE());

		FST print(6, text, \
			NODE(1, RELATION('p', 1)), \
			NODE(1, RELATION('r', 2)), \
			NODE(1, RELATION('i', 3)), \
			NODE(1, RELATION('n', 4)), \
			NODE(1, RELATION('t', 5)), \
			NODE());

		FST Return(7, text, \
			NODE(1, RELATION('r', 1)), \
			NODE(1, RELATION('e', 2)), \
			NODE(1, RELATION('t', 3)), \
			NODE(1, RELATION('u', 4)), \
			NODE(1, RELATION('r', 5)), \
			NODE(1, RELATION('n', 6)), \
			NODE());

		FST main(5, text, \
			NODE(1, RELATION('m', 1)), \
			NODE(1, RELATION('a', 2)), \
			NODE(1, RELATION('i', 3)), \
			NODE(1, RELATION('n', 4)), \
			NODE());


		FST lefthesis(2, text, \
			NODE(1, RELATION('(', 1)), \
			NODE());

		FST righthesis(2, text, \
			NODE(1, RELATION(')', 1)), \
			NODE());

		FST leftbrace(2, text, \
			NODE(1, RELATION('{', 1)), \
			NODE());

		FST rightbrace(2, text, \
			NODE(1, RELATION('}', 1)), \
			NODE());

		FST plus(2, text, \
			NODE(1, RELATION('+', 1)), \
			NODE());

		FST minus(2, text, \
			NODE(1, RELATION('-', 1)), \
			NODE());

		FST multi(2, text, \
			NODE(1, RELATION('*', 1)), \
			NODE());

		FST dirslash(2, text, \
			NODE(1, RELATION('/', 1)), \
			NODE());

		FST comma(2, text, \
			NODE(1, RELATION(',', 1)), \
			NODE());

		FST semicolon(2, text, \
			NODE(1, RELATION(';', 1)), \
			NODE());
		
		FST init(2, text, NODE(1, RELATION('=', 1)), NODE());

		FST OR(3, text, \
			NODE(1, RELATION('o', 1)), \
			NODE(1, RELATION('r', 2)), \
			NODE());

		FST AND(2, text, \
			NODE(1, RELATION('&', 1)), \
			NODE());

		FST NOT(2, text, \
			NODE(1, RELATION('~', 1)), \
			NODE());

		FST FOR(6, text, \
			NODE(1, RELATION('w', 1)), \
			NODE(1, RELATION('h', 2)), \
			NODE(1, RELATION('i', 3)), \
			NODE(1, RELATION('l', 4)), \
			NODE(1, RELATION('e', 5)), \
			NODE());

		FST more(2, text, \
			NODE(1, RELATION('>', 1)), \
			NODE());

		FST less(2, text, \
			NODE(1, RELATION('<', 1)), \
			NODE());

		FST sqrl(2, text, \
			NODE(1, RELATION('[', 1)), \
			NODE());

		FST sqrr(2, text, \
			NODE(1, RELATION(']', 1)), \
			NODE());
		
		FST chain[] = { integer, string, function, declare, print, Return, main , lefthesis, righthesis, leftbrace, rightbrace,plus, minus, multi, dirslash, comma, semicolon, init, OR, AND, NOT, FOR, more, less ,sqrl, sqrr };
		char Lexems[] = { LEX_INTEGER, LEX_STRING, LEX_FUNCTION, LEX_DEF, LEX_PRINT, LEX_RETURN,
						LEX_MAIN, LEX_LEFTHESIS, LEX_RIGHTHESIS, LEX_LEFTBRACE, LEX_BRACELET, LEX_PLUS,
						LEX_MINUS, LEX_STAR, LEX_DIRLASH, LEX_COMMA, LEX_SEMICOLON, LEX_INIT, LEX_OR, LEX_AND, LEX_NOT, LEX_CYCLE, LEX_M, LEX_L, LEX_SQUARE, LEX_RSQUARE 
		};
		
		al.lex = 'i';
	
		al.firstentryerror = false;
			for (int j = 0; j < 26; j++) ///strlen(Lexems);
			{				
				strcpy(chain[j].string, str);

				execute(chain[j], al);
				
				if (al.isgood)
				{
					al.lex = Lexems[j];
					break;
				}
				
			}
			switch (al.lex)
			{
			case 't': al.type = true;
				strcpy(al.typeWord, text);
				
				break;
			case 'f': al.func = true; break;
				
			case 'd': al.declare = true;  break;
				
			case '(': al.lefhesis = true; break;
				
			case ')': al.func = false; 
				if (!al.lefhesis)
				{
					//exception
				}
				break;		
			case 'm': 
				if (!al.main)
				{
					al.main = true;
				}
				else
				{
					throw ERROR_THROW(201);
				}
				break;
			case 'c': 
				if (al.cycle)
				{
					al.cycle = false;
				}
				else
				{
					al.cycle = true;
				}
				 
			break;
			case '=': al.init = true; break;
			case 'w': al.init = true; break;
			
			case '}': al.blocklevel++;
			case ';': 
				al.init = false; 
				al.print = false;  break;
				
			case 'i':
				if (al.func && al.type && al.lefhesis)
				{		
					al.type = false;
					al.parm = true;
					return al;
				}
				else
				{
					if (al.func && al.type)
					{
						
						al.type = false;
						return al;
					}
					else
					{
						if (al.declare && al.type)
						{
							al.declare = false;
							al.type = false;
							
							return al;
						}
						else
						{
							if (!al.init)
							{
								
								al.firstentryerror = true; //ошибка второго вхождения
																
							}
							
						}
					}
				}
 
				break;
			}
			return al;
			delete [] text;			
	}


	
	void Analyze(In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable, LT::Entry& en, IT::Entry& id )
	{
		char* str = new char [IN_MAX_LEN_TEXT];	//слова
		char lexem; //лексема возвращаемая WordToLex
		int line = 0, pos=0;
		bool isid = false; //есть ли id в таблице
		bool isline = false;
		int block = 0; //отслеживает блок { }
		int k = 0; //параметр для поиска по таблицу id 
		bool firstentry = false;

		AL al;
				
		try
		{
			for (int i = 0; i < in.size; i++)
			{				
				switch (in.text[i]) //запись слов и поиск пробелов для вызова функции
				{
				case ' ': 
					str[pos] = '\0';

					if (strcmp(str, " ") == 0 || strcmp(str, "") == 0)
						break;
					else if (isline)
					{
						str[pos++] = ' ';
						break;
					}

					WordToLexem(str, line, al); //конвертация слов в лексемы
					lexem = al.lex;

					if (lexem == 'v')
					{
						en.operation = str[0];
						switch (str[0])
						{
						case '(': en.priority = 0; break;
						case ')': en.priority = 0; break;
						case ',': en.priority = 1; break;
						case '+': en.priority = 2; break;
						case '-': en.priority = 2; break;
						case '&': en.priority = 2; break;
						case '~': en.priority = 2; break;
						case 'o': en.priority = 2; en.operation = '|'; break;
						case '*': en.priority = 3; break;
						case '/': en.priority = 3; break;

						}
					}
					else
					{
						en.operation = NULL;
						en.priority = NULL;
					}

					if (lexem != 'i') 
					{
						
						en.lexema[0] = lexem;						
						en.sn = line;						
						en.idxTI = LT_TI_NULLIX;
						//std::cout << en.sn << " " << en.lexema[0] << " " << en.idxTI << std::endl;
						LT::Add(lextable, en);
						pos = 0;
					}
					else
					{
						// параметр для поиска
						isid = false; //для поиска
						if (block != al.blocklevel && !al.cycle) //фывыфвыфвыфвввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввввв
						{
							block++;
						}

						if (!al.parm)
						{
							for (int j = 0; j < idtable.size; j++) //поиск id в таблице идентифкаторов
							{
								if (strcmp(idtable.table[j].id, str) == 0 && !firstentry && (block == idtable.table[j].levelvisible || idtable.table[j].levelvisible == 0))
								{
									firstentry = true;
									isid = true;
									al.firstentryerror = false;
									en.idxTI = j;
									en.lexema[0] = lexem;
									en.sn = line;
									LT::Add(lextable, en);
									pos = 0;
									id = idtable.table[j];
								}

							}
							firstentry = false;
						}			
						

						if(!isid) //зарегестрированно первое вхождение
						{							
							if (al.firstentryerror && lextable.table[lextable.size-1].lexema[0] !='r' && lextable.table[lextable.size - 1].lexema[0] != 'p')					//
							{
								throw ERROR_THROW_IN(206, line, al.counter);
							}

							switch (lextable.table[lextable.size - 1].lexema[0]) //присуждение типа идентификатору
							{
							case 't':	//переменная параметр 
								strcpy(id.id, str);
								id.idxfirstLE = line;
								id.levelvisible = block;
								if (strcmp(al.typeWord, (char*)"string") == 0)
								{
									id.iddatatype = IT::IDDATATYPE::STR;
								}
								else
								{
									id.iddatatype = IT::IDDATATYPE::INT;
								}

								if (*lextable.table[lextable.size - 2].lexema == '(' || *lextable.table[lextable.size - 2].lexema == ',') //проверка на параметр
								{
									al.parm = false;
									id.idtype = IT::IDTYPE::P;
								}
								else
								{
									id.idtype = IT::IDTYPE::V;
								}
								break;

							case 'f': 
								strcpy(id.id, str);
								id.idxfirstLE = line;
								id.idtype = IT::IDTYPE::F;
								id.levelvisible = 0;
								if (strcmp(al.typeWord, (char*)"string") == 0)
								{
									id.iddatatype = IT::IDDATATYPE::STR;
								}
								else
								{
									id.iddatatype = IT::IDDATATYPE::INT;
								}
								
								break;
							case 'p' : //в случае если в print указана строка а не переменная; можно выкинуть ошибку (отсутствие кавычек)
								strcpy(id.id, str);
								id.idxfirstLE = line;
								id.idtype = IT::IDTYPE::L;
								if (int((unsigned char)str[0]) == 39 && int((unsigned char)str[strlen(str) - 1]) == 39) //проверка на тип значения
								{
									id.iddatatype = IT::IDDATATYPE::STR;
									id.value.vstr->len = strlen(str);
									strcpy(id.value.vstr->str, str);
								}
								else
								{
									if (int((unsigned char)str[0]) == 39 || int((unsigned char)str[strlen(str) - 1]) == 39)
									{
										ERROR_THROW_IN(206, line, 1);
									}
									else
									{										
										id.iddatatype = IT::IDDATATYPE::INT;
										id.value.vint = int(str);
									}
								}
								break; 

							default: //Литерал 
								strcpy(id.id, str);
								id.idxfirstLE = line;
								id.idtype = IT::IDTYPE::L;
								if (int((unsigned char)str[0]) == 39 && int((unsigned char)str[strlen(str) - 1]) == 39) //проверка на тип значения
								{
									id.iddatatype = IT::IDDATATYPE::STR;
									id.value.vstr->len = strlen(str);
									strcpy(id.value.vstr->str, str);
								}
								else
								{
									if (int((unsigned char)str[0]) == 39 || int((unsigned char)str[strlen(str) - 1]) == 39)
									{
										ERROR_THROW_IN(206, line, 2);
									}
									else
									{
										id.iddatatype = IT::IDDATATYPE::INT;
										id.value.vint = int(str);
									}
								}
								break;
							}
							en.lexema[0] = lexem;
							en.sn = line;
							en.idxTI = idtable.size;
							LT::Add(lextable, en);
							pos = 0;
							// запись в таблицу лексем
							
							IT::Add(idtable, id);

						}						
					}
					
					break;
				case '|': pos = 0; line++; al.counter = 0; break;
				default: 
					if ((int)in.text[i] == 39)
					{
						if (!isline)
							isline = true;
						else
							isline = false;
					}
					str[pos] = in.text[i]; pos++; break;
				}
			}

			line = 0;

			for (int f = 0; f < lextable.size; f++)
			{
				en = LT::GetEntry(lextable, f);	
				if (en.sn > line)
				{
					std::cout << '\n';
					std::cout << *en.lexema;
					line++;
				}
				else
				{
					std::cout << *en.lexema;
				}
			}
			std::cout << "----------------------" << std::endl;
			for (int i = 0; i < lextable.size; i++)
			{
				en = LT::GetEntry(lextable, i);
				std::cout << "Строка: " << en.sn << " " << "| " << en.lexema[0] << " " <<en.operation;
				if (en.idxTI != -1)
				{
					id = IT::GetEntry(idtable, en.idxTI);
					std::cout << " Идентифкатор " << id.id<< " | Номер в таблице идентификаторов " << en.idxTI;
				}
				std::cout<<'\n';
			} 
			std::cout << "----------------------" << std::endl <<"Таблица идентификаторов"<<std::endl;
			for (int j = 0; j < idtable.size; j++)
			{
				char* type= new char[10];
				id = IT::GetEntry(idtable, j);
				if (id.iddatatype == 1)
				{
					strcpy(type, (char*)"integer");
				}
				else
				{
					strcpy(type, (char*)"string");
				}
				switch (id.idtype)
				{
				case IT::IDTYPE::F: std::cout <<  " Функция " << id.id << " Тип данных "<<type<<" : Строка-" <<id.idxfirstLE<<std::endl; break;
				case IT::IDTYPE::V: std::cout <<  " Переменная " << id.id << " Тип данных " << type << " : Строка-" << id.idxfirstLE << ::endl;  break;
				case IT::IDTYPE::L: std::cout <<  " Литерал "<< id.id << " Тип данных " << type << " : Строка-"<< id.idxfirstLE<< std::endl;  break;
				case IT::IDTYPE::P: std::cout << " Параметр "<< id.id << " Тип данных " << type << " : Строка-"  << id.idxfirstLE<< std::endl; break;
				}
			}
		}
		catch (Error::ERROR e)
		{
			
			std::cout << "Error " << e.id << " " << e.message << std::endl;
			std::cout << "Line " << e.inext.line << " Position " << e.inext.col << std::endl;
			
		}

		
		
	}

}
