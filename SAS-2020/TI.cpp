#include "TI.h"
#include "Error.h"
#include <string>


namespace IT
{
	IdTable Create(int size)		//������� ������� ��������������� 	// < TI_MAXSIZE
	{
		IdTable table;
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(200);
		}
		else
		{
			table.maxsize = size;
			table.size = 0;
			table.table = new Entry[TI_MAXSIZE];
		}
		
		return table;
	}
	

	void Add(IdTable& idtable, Entry entry)				//�������� ������ � ������� ���������������
	{
		if (idtable.maxsize <= idtable.size)
		{
			throw ERROR_THROW(210);
		}
		else
		{
			idtable.table[idtable.size++] = entry;
		}
	}
	

		
	Entry GetEntry(IdTable& idtable, int n)			//�������� ������ ������� ���������������
	{
		return idtable.table[n];
	}


	int IsId(IdTable& idtable, char id[ID_MAXSIZE])							//�������: ����� ������(���� ����), TI_NULLIDX(���� ���)
	{
		bool is = false;
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id))
			{
				return idtable.table[i].idxfirstLE;
				is = true;
			}			
		}

		return (TI_NULLIDX);
	}	

	void Delete(IdTable& idtable)
	{
		delete &idtable;
	}
}