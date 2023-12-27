#pragma once
#include "pch.h"
#include "LexAnalyzer.h"

#define START \
".586\n"\
".model flat, stdcall\n"\
"includelib libucrt.lib\n"\
"includelib kernel32.lib\n"\

#define PROTOTYPES \
"\nExitProcess PROTO:DWORD "\
"\nSYSPAUSE PROTO "\
"\nsoutl PROTO : BYTE "\
"\nnoutl PROTO : SDWORD "\
"\n_pow PROTO  : SDWORD, : SDWORD "\
"\n_abs PROTO  : SDWORD "\
"\n\n.STACK 4096\n\n"

#define FINISH \
"\tcall SYSPAUSE"\
"\n\tpush 0"\
"\n\tcall ExitProcess"\
"\nSOMETHINGWRONG::"\
"\n\tpush offset null_division"\
"\n\tcall soutl"\
"\njmp THEEND"\
"\noverflow::"\
"\n\tpush offset OVER_FLOW"\
"\n\tcall soutl"\
"\nTHEEND:"\
"\n\tcall SYSPAUSE"\
"\n\tpush -1"\
"\n\tcall ExitProcess"\
"\nmain ENDP\nend main"


namespace CodeGeneration
{
	void CodeGeneration(LA::LEX lex, wchar_t outfile[]);
}