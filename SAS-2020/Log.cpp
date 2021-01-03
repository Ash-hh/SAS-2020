#include <cwchar>

#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include "time.h"
#include <iostream>

namespace Log
{


	LOG getlog(wchar_t file[])
	{
		LOG log;

		if (!wcslen(file))
		{
			wcscpy_s(log.logfile, PARM_LOG_DEFAULT_EXT);
		}
		else
		{
			wcscpy_s(log.logfile, file);
		}

		log.stream = new std::ofstream(file);

		if (!log.stream->is_open())
		{
			ERROR_THROW(112);
		}

		return log;
	}



	void WriteLine(LOG log, char* c, ...)
	{
		char** buff = &c;
		while (*buff != " ")
		{
			*log.stream << *buff << " ";
			buff++;
		}
		*log.stream << std::endl;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{

		wchar_t** buff = &c;


		while (*buff != L" ")
		{
			char buf[256];

			wcstombs_s(0, buf, *buff, 256);
			*log.stream << buf;

			buff++;
		}
		*log.stream << std::endl;

	}
	void WriteLog(LOG log)
	{
		char buffer[100];
		struct tm local;
		time_t t;

		time(&t);
		localtime_s(&local, &t);

		strftime(buffer, 100, "����: %d.%m.%y %r ------", &local);

		*log.stream << "---- �������� ------" << std::endl;
		*log.stream << buffer << std::endl;
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char buff[256];

		*log.stream << "----------Parms:------\n";
		wcstombs_s(0, buff, parm.in, 256);
		*log.stream << " -in: " << buff << std::endl;
		wcstombs_s(0, buff, parm.out, 256);
		*log.stream << " -out: " << buff << std::endl;
		wcstombs_s(0, buff, parm.log, 256);
		*log.stream << " -log: " << buff << std::endl;


	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "------------�������� ������-------\n";
		*log.stream << " ���������� ��������: " << in.size << " \n ����������������: " << in.ignor << "\n ���-�� �����: " << in.lines << std::endl;

	}
	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "������" << error.id << " " << error.message << " ������ " << error.inext.line << " ������� " << error.inext.col << std::endl;
	}
	void Close(LOG log)
	{
		log.stream->close();
	}


}