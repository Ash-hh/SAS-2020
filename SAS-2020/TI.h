#pragma once

#define ID_MAXSIZE 50				//������������ ���-�� ��������� � ��������������
#define TI_MAXSIZE 4096				//������������ ���-�� ����� � ������� ���������������
#define TI_INT_DEFAULT 0x00000000	//�������� �� ��������� ��� ���� ���
#define TI_STR_DEFAULT 0x00			//�������� �� ��������� ��� ���� ������
#define TI_NULLIDX 0xffffffff		//��� ��-�� ������� ���������������
#define TI_STR_MAXSIZE 255			//���� ������ ������????

namespace IT
{
	enum IDDATATYPE{INT=1, STR=2};		//���� ������ ���������������: ��� ������
	enum IDTYPE {V=1, F=2, P=3, L=4};	//���� ���������������: ���������, �������, ��������, �������

	struct Entry	//������ ������� ���������������
	{
		int levelvisible;
		int idxfirstLE;			//������ ������ ������ � ������� ������
		char id[ID_MAXSIZE];	//������������� (������� ��������� �� ����. �������)
		IDDATATYPE iddatatype;	//��� ������
		IDTYPE idtype;			//��� ��������������
		union
		{
			int vint;		//��������� int
			struct
			{
				char len;							//���-�� �������� ������ int??
				char str[TI_STR_MAXSIZE - 1];		//������� string
			}vstr[TI_STR_MAXSIZE];					//�������� string
		}value; //�������� ��������������

	};

	struct IdTable			//��������� ������� ���������������
	{
		int maxsize;		//������� ������� ��������������� < TI_MAXSIZE
		int size;			// ������� ������ ������� < maxsize
		Entry* table;		//������ ����� ������� ���������������
	};

	IdTable Create(			//������� ������� ���������������
		int size			// < TI_MAXSIZE
	);

	void Add(				//�������� ������ � ������� ���������������
		IdTable& idtable,	//��������� ������� ���������������
		Entry entry			//������ ������� ���������������
	);

	Entry GetEntry(			//�������� ������ ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		int n				//����� ���������� ������
	);

	int IsIs(					//�������: ����� ������(���� ����), TI_NULLIDX(���� ���)
		IdTable& idtable,		//��������� ������� ���������������
		char id[ID_MAXSIZE]		//�������������
	);

	void Delete(				//�������� �������
		IdTable& idtable
	);
}