#include "LT.h"
#include "Error.h"
#include <iostream>

namespace LT
{
	LexTable Create(int size) //������ 210  (�� ����� 4096)
	{
		LexTable lex;
		lex.maxsize = size;
		lex.size = 0;
		
		
		if (size > LT_MAXSIZE)
		{
			throw ERROR_THROW(205);
		}
		else
		{
			lex.maxsize = size;
			lex.size = 0;
			lex.table = new Entry[size];
		}
		return lex;
	}

	void Add(LexTable& lextable, Entry entry)					//�������� ������ � ������� ������
	{
		if (lextable.maxsize <= lextable.size)
		{
			throw ERROR_THROW(205);					//������ ���������� �������
		}
		else
		{
			lextable.table[lextable.size++] = entry;
		}
	}	
		
	

	Entry GetEntry(LexTable& lextable, int n)		//�������� ������ ������� ������	//�� ������� ����� ��-�?
	{
		//std::cout << lextable.table[n].lexema;
		//std::cout << lextable.table[n].idxTI;
		//std::cout << lextable.table[n].sn;	

		return lextable.table[n];
	}

	void Delete(LexTable& lextable)			//������� ������� ������ (���������� ������)
	{
		delete &lextable;
	}
	
}