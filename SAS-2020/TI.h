#pragma once

#define ID_MAXSIZE 50				//максимальное кол-во символово в идентификаторе
#define TI_MAXSIZE 4096				//максимальное кол-во строк в таблице идентификаторов
#define TI_INT_DEFAULT 0x00000000	//значение по умолчанию дл€ типа инт
#define TI_STR_DEFAULT 0x00			//значение по умолчанию дл€ типа стринг
#define TI_NULLIDX 0xffffffff		//нет эл-та таблицы индетификаторов
#define TI_STR_MAXSIZE 255			//макс размер строик????

namespace IT
{
	enum IDDATATYPE{INT=1, STR=2};		//типы данных идентификаторов: инт стринг
	enum IDTYPE {V=1, F=2, P=3, L=4};	//типы идентификаторов: перемена€, функци€, параметр, литерал

	struct Entry	//строка таблицы идентификаторов
	{
		int levelvisible;
		int idxfirstLE;			//индекс первой строки в таблице лексем
		char id[ID_MAXSIZE];	//идентификатор (автомат усекаетса до макс. значени)
		IDDATATYPE iddatatype;	//тип данных
		IDTYPE idtype;			//тип идентификатора
		union
		{
			int vint;		//значенрие int
			struct
			{
				char len;							//кол-во символво стринг int??
				char str[TI_STR_MAXSIZE - 1];		//символы string
			}vstr[TI_STR_MAXSIZE];					//значение string
		}value; //зна€ение идентификатора

	};

	struct IdTable			//экземпл€р таблицы идентификаторов
	{
		int maxsize;		//емкость таблицы идентификаторов < TI_MAXSIZE
		int size;			// текущий размер таблицы < maxsize
		Entry* table;		//массив строк таблицы идентификаторов
	};

	IdTable Create(			//создать таблицу идентификаторов
		int size			// < TI_MAXSIZE
	);

	void Add(				//добавить строку в таблицу идентификаторов
		IdTable& idtable,	//экземпл€р таблицы идентификаторов
		Entry entry			//строка таблицы идентификаторов
	);

	Entry GetEntry(			//получить строку таблицы идентификаторов
		IdTable& idtable,	// экземпл€р таблицы идентификаторов
		int n				//номер получаемой строки
	);

	int IsIs(					//¬ќ«¬–ј“: номер строки(если есть), TI_NULLIDX(елси нет)
		IdTable& idtable,		//экземпл€р таблицы идентификаторов
		char id[ID_MAXSIZE]		//идентификатор
	);

	void Delete(				//удаление таблицы
		IdTable& idtable
	);
}