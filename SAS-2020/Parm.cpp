#include "Parm.h"
#include <cwchar>
#include <iostream>
#include "Error.h"
#include "In.h"
#include "Log.h"
#include<TCHAR.H>


namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM parms = { L"",L"",L"",L""};

		bool in = false;
		bool out = false;
		bool log = false;
		bool gen = false;

		if (argc > PARM_MAX_SIZE)
			throw ERROR_THROW(104);

		for (int i = 1; i < argc; i++)
		{
			if (wcsstr(argv[i], PARM_IN))
			{
				in = true;
				wcscpy_s(parms.in, argv[i] + wcslen(PARM_IN));
			}

			if (wcsstr(argv[i], PARM_OUT))
			{
				out = true;
				wcscpy_s(parms.out, argv[i] + wcslen(PARM_OUT));
			}

			if (wcsstr(argv[i], PARM_LOG))
			{
				log = true;
				wcscpy_s(parms.log, argv[i] + wcslen(PARM_LOG));
			}

			if (wcsstr(argv[i], PARM_GEN))
			{
				gen = true;
				wcscpy_s(parms.generation, argv[i] + wcslen(PARM_LOG));
			}

		}
		if (out != true)
		{
			wcscpy_s(parms.out, parms.in);
			wcscat_s(parms.out, PARM_OUT_DEFAULT_EXT);

		}
		if (log != true)
		{
			wcscpy_s(parms.log, parms.in);
			wcscat_s(parms.log, PARM_LOG_DEFAULT_EXT);
		}

		if (in != true)
		{
			throw ERROR_THROW(100);
		}
		
		if (!gen)
		{
			wcscpy_s(parms.generation, L"geneartion");
			wcscat_s(parms.generation, PARM_LOG_DEFAULT_EXT);
		}


		return parms;
	}
}