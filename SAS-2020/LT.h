#pragma once

#define LEXEMA_FIXSIZE 1  //фиксированный размер лексемы
#define LT_MAXSIZE 4096 //максимально кол-во строк в таблице лексем
#define LT_TI_NULLIX 0xffffffff	//нет эл-та таблицы идентификаторов
#define LEX_INTEGER 't'		//лексема для inte
#define LEX_STRING 't'		//лексема для string
#define LEX_ID 'i'			//лексема для id
#define LEX_LITERAL 'l'		//лексема для литерала
#define LEX_FUNCTION 'f'	//лексема для function
#define LEX_DEF 'd'		//лексема для declare
#define LEX_RETURN 'r'		//лексема для return
#define LEX_PRINT 'p'		//лексема для print
#define LEX_MAIN 'm'		//лексема для main
#define LEX_SEMICOLON ';'	//лексема для ;
#define LEX_COMMA ','		//лексема для ,
#define LEX_LEFTBRACE '{'	//лексема для {
#define LEX_BRACELET '}'	//лексема для }
#define LEX_SQUARE '['
#define LEX_RSQUARE ']'
#define LEX_LEFTHESIS '('	//лексема для (
#define LEX_RIGHTHESIS ')'	//лексема для )
#define LEX_PLUS 'v'		//лексема для +
#define LEX_MINUS 'v'		//лексема для -
#define LEX_STAR 'v'		//лексема для *
#define LEX_DIRLASH 'v'		//лексема для /
#define LEX_INIT '='		//лексема для =
#define LEX_OR 'v'			//побитовое или or
#define LEX_AND 'v'			//побитовое и
#define LEX_NOT 'v'			//побитовое нет
#define LEX_CYCLE 'c'		//цикл
#define LEX_M 'w'		//>
#define LEX_L 'w'	//<

namespace LT
{
	struct Entry	//строка таблицы лексем
	{
		char lexema[LEXEMA_FIXSIZE];	//лексема
		int sn;							//номер строки в исходном тексте
		int idxTI;						//индекс в таблице идентификаторов или LT_TI_NULLIDX
		char operation;
		int priority;
	};

	struct LexTable		//экземпляр таблицы лексем
	{			
		int maxsize;	//ёмкость тыблицы лексем <	LT_MAXSIZE			
		int size;		// текущий размер таблицы лексем < maxsize
		Entry* table;	// массив строк таблицы лексем

	};

	LexTable Create(	//создать таблицу лексем
		int size		// ёмкость таблицы лексем < LT_MAXSIZE 
	);

	void Add(					//добавить строку в таблицу лексем
		LexTable& lextable,		//экземпляр таблицы лексем
		Entry entry				//строка таблицы лексем
	);

	Entry GetEntry(				//получить строку таблицы лексем
		LexTable& lextable,		//экземпляр табоицы лексем
		int n					//номер получаемой строки
	);

	void Delete(				//удалить таблицу лексем (освободить память)
		LexTable& lextable
	);

		


}