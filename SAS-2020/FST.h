#pragma once
#include "LT.h"
#include "TI.h"
#include "In.h"
#include <iostream>






namespace FST
{
	struct RELATION							//11 ����� :������->������� ����� ��������� ��
	{
		char symbol;						// ������ ��������
		short nnode;						// ����� ������� �������
		RELATION(char � = 0x00,				// ������ ��������
			short ns = NULL);				// ����� ���������												
	};

	struct NODE								// ������� ����� ���������
	{
		short n_relation;					// ���������� ������������ �����
		RELATION* relations;				// ����������� �����
		NODE();                             //�����������
		NODE(
			short n,						// ���������� ������������ �����
			RELATION rel, ...				// ������ �����
		);
	};

	struct FST
	{
		short position = 0;
		char* string;				//������� (������, ���������� 0x00 ) 
						//������� ������� � ������� 
		short nstates;						//���������� ��������� ��������
		NODE* nodes;						//���� ���������: [0] -��������� ���������, [nstate-1]-��������
		short* rstates;						//��������� ��������� �������� �� ������ �������.
		FST(
			short ns,					//���������� ��������� ��������		
			char* s,					//������� (������, ���������� 0x00 )	
			NODE n, ...					//������ ��������� (���� ���������)			
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



	AL execute(							// ��������� ������������� ������� 
		FST& fst, AL& al							//������������������ �������� �������
	);

	void Analyze(In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable, LT::Entry& en, IT::Entry& id);

	AL WordToLexem(char* str, int line);
};