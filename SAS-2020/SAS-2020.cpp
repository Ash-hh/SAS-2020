// SAS-2020.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <cwchar>
#include<TCHAR.H>
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "LT.h"
#include "FST.h"
#include <locale>
#include "PolishNotation.h"
#include "MFST.h"
#include "CG.h"

int TestParm(int argc, _TCHAR* argv[]);
int TestIN(int argc, _TCHAR* argv[]);
int TestLog(int argc, _TCHAR* argv[]);
int TestLt(int argc, _TCHAR* argv[]);
int TestAnalyze(int argc, _TCHAR* argv[]);
//int ErrorTest();

int _tmain(int argc, _TCHAR* argv[])
{



	setlocale(LC_ALL, "rus");

	//TestLt(argc,argv);
	//TestParm(argc, argv);
	//TestIN(argc, argv);
	TestLog(argc, argv);
	TestAnalyze(argc, argv);

	return 0;
}

int TestLt(int argc, _TCHAR* argv[])
{
	try
	{
		LT::Create(200);
		return 0;
	}
	catch (Error::ERROR e)
	{
		std::cout << "Error " << e.id << " " << e.message << std::endl;
	}


}

int ErrorTest()
{

	std::cout << "------------ Error::geterror test ------------" << std::endl;

	try
	{
		throw ERROR_THROW(100);
	}
	catch (Error::ERROR e)
	{
		std::cout << "Error" << e.id << " " << e.message << std::endl;
	}

	std::cout << "-----------Error::geterroin test-----" << std::endl;
	try
	{
		throw ERROR_THROW_IN(111, 7, 7);
	}
	catch (Error::ERROR e)
	{
		std::cout << "Error" << e.id << " " << e.message << std::endl;
		std::cout << "row - " << e.inext.line << " col - " << e.inext.col << std::endl;

	}
	system("pause");
	return 0;
}

int TestParm(int argc, _TCHAR* argv[])
{


	std::cout << "-----Test Parm::getparm-----" << std::endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		std::wcout << "-in: " << parm.in << " -out:" << parm.out << " -log:" << parm.log << std::endl;
	}
	catch (Error::ERROR e)
	{
		std::cout << "Error " << e.id << " " << e.message << std::endl;
	};

	system("pause");


	return 0;
}

int TestAnalyze(int argc, _TCHAR* argv[])
{
	try
	{

		LT::Entry en;
		IT::Entry id;
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		LT::LexTable table;
		IT::IdTable idtable;
		table = LT::Create(In::words(in.text));
		idtable = IT::Create(In::words(in.text));
		FST::Analyze(in, table, idtable, en, id);
		
		MFST_TRACE_START
			MFST::Mfst mfst(table, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		mfst.printrules();


		Code::Generation(idtable, table, parm);




		return 0;

	}
	catch (Error::ERROR e)
	{
		std::cout << "Error " << e.id << " " << e.message << std::endl;
		std::cout << e.inext.line << " " << e.inext.col;
	}

}

int TestIN(int argc, _TCHAR* argv[])
{

	Log::LOG log = Log::INITLOG;

	std::cout << "---------testIn::getin-------------" << std::endl;
	try
	{

		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		std::cout << in.text << std::endl;
		std::cout << "total sumbols : " << in.size << std::endl;
		std::cout << "total lines : " << in.lines << std::endl;
		std::cout << "ignored : " << in.ignor << std::endl;
		In::FileOut(parm.out, in);
		delete in.text;

		log = Log::getlog(parm.log);
		Log::WriteLine(log, (wchar_t*)L"Тест:", (wchar_t*)L"без ошибок", (wchar_t*)L" ");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::FileOut(parm.out, in);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		std::cout << "Error" << e.id << " " << e.message << std::endl;
		std::cout << "Line " << e.inext.line << " Position " << e.inext.col << std::endl;
		Log::WriteError(log, e);
	}

	return 0;
}





int TestLog(int argc, wchar_t* argv[])
{
	Log::LOG log = Log::INITLOG;
	try
	{

		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, (wchar_t*)L"Тест:", (wchar_t*)L"без ошибок", (wchar_t*)L" ");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		In::FileOut(parm.out, in);
		Log::WriteIn(log, in);
		Log::Close(log);

	}
	catch (Error::ERROR e)
	{

		Log::WriteError(log, e);
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.