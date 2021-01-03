#pragma once
#include "LT.h"
#include "TI.h"
#include "In.h"
#include <iostream>






namespace FST
{
	struct RELATION							//11 ребро :символ->вершина графа переходов КА
	{
		char symbol;						// символ перехода
		short nnode;						// номер смежной вершины
		RELATION(char с = 0x00,				// символ перехода
			short ns = NULL);				// новое состояние												
	};

	struct NODE								// вершина графа переходов
	{
		short n_relation;					// количество инциндентных ребер
		RELATION* relations;				// инцидентные ребра
		NODE();                             //конструктор
		NODE(
			short n,						// количество инциндентных ребер
			RELATION rel, ...				// список ребер
		);
	};

	struct FST
	{
		short position = 0;
		char* string;				//цепочка (строка, завершатся 0x00 ) 
						//текущая позиция в цепочке 
		short nstates;						//количество состояний автомата
		NODE* nodes;						//граф переходов: [0] -начальное состояние, [nstate-1]-конечное
		short* rstates;						//возможные состояния автомата на данной позиции.
		FST(
			short ns,					//количество состояний автомата		
			char* s,					//цепочка (строка, завершатся 0x00 )	
			NODE n, ...					//список состояний (граф переходов)			
		);
	};
	struct AL
	{
		int blocklevel = 0;
		int counter = 0;
		bool isgood = false;
		bool cycle = false;
		bool parm = false;
		bool firstentryerror = false;
		bool declare = false;
		bool lefhesis = false;
		bool func = false;
		bool type = false;
		bool init = false;
		bool print = false;
		bool main = false;
		char* typeWord = new char[IN_MAX_LEN_TEXT];;
		char lex;
	};



	AL execute(							// выполнить распознавание цепочки 
		FST& fst, AL& al							//недетерминировнный конечный автомат
	);

	void Analyze(In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable, LT::Entry& en, IT::Entry& id);

	AL WordToLexem(char* str, int line);
};