#include "pch.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM parm = {};
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
			{
				throw ERROR_THROW(11)
			}

			if (wcsstr(argv[i], PARM_IN))
				wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));
			else if (wcsstr(argv[i], PARM_OUT))
				wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT));
			else if (wcsstr(argv[i], PARM_LOG))
				wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG));
			else if (wcsstr(argv[i], PARM_AN))
				wcscpy_s(parm.an, argv[i] + wcslen(PARM_AN));
		}
		if (wcslen(parm.in) == 0)
			throw ERROR_THROW(10);
		if (wcslen(parm.out) == 0)
		{
			throw ERROR_THROW(12);
			/*wcscpy_s(parm.out, parm.in);
			wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));*/
		}
		if (wcslen(parm.log) == 0)
		{
			wcscpy_s(parm.log, parm.in);
			wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
		}
		if (wcslen(parm.an) == 0)
		{
			wcscpy_s(parm.an, parm.in);
			wcsncat_s(parm.an, PARM_AN_DEFAULT_EXT, wcslen(PARM_AN_DEFAULT_EXT));
		}
		return parm;
	}
}