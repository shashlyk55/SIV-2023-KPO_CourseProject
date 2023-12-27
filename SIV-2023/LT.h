#pragma once
#include "pch.h"

#define LEXEMA_FIXSIZE 1               
#define LT_MAXSIZE 4096                 
#define LT_TI_NULLTDX 0xffffffff        

#define LEX_SHORT		'd'             
#define LEX_STRING      's'             
#define LEX_BOOL		'b'				
#define LEX_ID          'i'            
#define LEX_LITERAL     'l'            
#define LEX_IF			'c'				
#define LEX_ELSE		'e'							
#define LEX_FUNCTION    'f'            
#define LEX_NEW		    'n'            
#define LEX_RETURN      'r'                     
#define LEX_PRINT		'o'				
#define LEX_MAIN		'm'				
#define LEX_POW			'p'				
#define LEX_ABS			'a'				
#define LEX_SEMICOLON   ';'             
#define LEX_COMMA       ','             
#define LEX_LEFTBRACE   '{'             
#define LEX_RIGHTBRACE  '}'            
#define LEX_LEFTHESIS   '('             
#define LEX_RIGHTHESIS  ')'             
#define LEX_PLUS        '+'             
#define LEX_MINUS       '-'             
#define LEX_STAR        '*'             
#define LEX_DIRSLASH    '/'             
#define LEX_REMDIV		'%'				
#define LEX_EQUAL		'='				
#define LEX_EQUALEQUAL	'&'				
#define LEX_LESS		'<'				
#define LEX_MORE		'>'				
#define LEX_NOTEQUAL	'!'				
#define LEX_MOREEQUAL   ']'				
#define LEX_LESSEQUAL   '['				

namespace LT
{
	struct Entry
	{
		char lexema;		// символ лексемы
		int sn;				// номер строки в коде
		int idxTI;			// номер в IT
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	void Delete(LexTable& lextable);
	void SaveToFile(LexTable& lextable, wchar_t outfile[]);

	Entry GetEntry(LexTable& lextable, int n);

	Entry CreateEntry(char lexema, int line);
	Entry CreateEntry(char lexema, int line, int idTI);
	void SaveLexTableInFile(LexTable lextable, wchar_t outfile[]);
};