#pragma once

#define LEXEMA_FIXSIZE 1  //������������� ������ �������
#define LT_MAXSIZE 4096 //����������� ���-�� ����� � ������� ������
#define LT_TI_NULLIX 0xffffffff	//��� ��-�� ������� ���������������
#define LEX_INTEGER 't'		//������� ��� inte
#define LEX_STRING 't'		//������� ��� string
#define LEX_ID 'i'			//������� ��� id
#define LEX_LITERAL 'l'		//������� ��� ��������
#define LEX_FUNCTION 'f'	//������� ��� function
#define LEX_DEF 'd'		//������� ��� declare
#define LEX_RETURN 'r'		//������� ��� return
#define LEX_PRINT 'p'		//������� ��� print
#define LEX_MAIN 'm'		//������� ��� main
#define LEX_SEMICOLON ';'	//������� ��� ;
#define LEX_COMMA ','		//������� ��� ,
#define LEX_LEFTBRACE '{'	//������� ��� {
#define LEX_BRACELET '}'	//������� ��� }
#define LEX_SQUARE '['
#define LEX_RSQUARE ']'
#define LEX_LEFTHESIS '('	//������� ��� (
#define LEX_RIGHTHESIS ')'	//������� ��� )
#define LEX_PLUS 'v'		//������� ��� +
#define LEX_MINUS 'v'		//������� ��� -
#define LEX_STAR 'v'		//������� ��� *
#define LEX_DIRLASH 'v'		//������� ��� /
#define LEX_INIT '='		//������� ��� =
#define LEX_OR 'v'			//��������� ��� or
#define LEX_AND 'v'			//��������� �
#define LEX_NOT 'v'			//��������� ���
#define LEX_CYCLE 'c'		//����
#define LEX_M 'w'		//>
#define LEX_L 'w'	//<

namespace LT
{
	struct Entry	//������ ������� ������
	{
		char lexema[LEXEMA_FIXSIZE];	//�������
		int sn;							//����� ������ � �������� ������
		int idxTI;						//������ � ������� ��������������� ��� LT_TI_NULLIDX
		char operation;
		int priority;
	};

	struct LexTable		//��������� ������� ������
	{			
		int maxsize;	//������� ������� ������ <	LT_MAXSIZE			
		int size;		// ������� ������ ������� ������ < maxsize
		Entry* table;	// ������ ����� ������� ������

	};

	LexTable Create(	//������� ������� ������
		int size		// ������� ������� ������ < LT_MAXSIZE 
	);

	void Add(					//�������� ������ � ������� ������
		LexTable& lextable,		//��������� ������� ������
		Entry entry				//������ ������� ������
	);

	Entry GetEntry(				//�������� ������ ������� ������
		LexTable& lextable,		//��������� ������� ������
		int n					//����� ���������� ������
	);

	void Delete(				//������� ������� ������ (���������� ������)
		LexTable& lextable
	);

		


}