#include "pch.h"
#include "CodeGeneration.h"

namespace CodeGeneration
{
	void CodeGeneration(LA::LEX lex, wchar_t outfile[])
	{
		ofstream generation(outfile);

		generation << START;
		generation << PROTOTYPES;

		generation << ".CONST\n";
		generation << "\tnull_division BYTE \'ERROR: DIVISION BY ZERO\', 0\n";
		generation << "\tOVER_FLOW BYTE \'ERROR: OVERFLOW\', 0\n";
		generation << "\ttrue BYTE \'true', 0\n";
		generation << "\tfalse BYTE \'false', 0\n";

		generation << "\tempty_string BYTE 0\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::L)
			{
				generation << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					generation << " BYTE " << lex.idtable.table[i].value.vstr.str << ", 0\n";
				}
				else if (lex.idtable.table[i].idDataType == IT::SHORT)
				{
					generation << " SDWORD " << lex.idtable.table[i].value.vshort << endl;
				}
				else
				{
					generation << " DWORD " << lex.idtable.table[i].value.vshort << endl;
				}
			}
		}

		generation << ".DATA\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::IDTYPE::V)
			{
				generation << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::BOOL)
				{
					generation << " DWORD 0\n";
				}
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					generation << " DWORD empty_string\n";
				}
				if (lex.idtable.table[i].idDataType == IT::SHORT)
				{
					generation << " SDWORD 0\n";
				}
			}
		}

		stack<int> stk;
		stack<int> ifi;
		int num_of_ret = 0,
			num_of_logical = 0,
			num_of_boolCompare = 0,
			num_of_if = 0;
		string func_name = "";
		bool flag_func = false,
			flag_return = false,
			flag_main = false,
			flag_if = false,
			flag_else = false;
		generation << "\n.CODE\n\n";

		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				generation << (func_name = lex.idtable.table[lex.lextable.table[++i].idxTI].id) << " PROC ";
				int ind = i;
				for (; lex.lextable.table[ind].lexema != LEX_RIGHTHESIS; ind++);

				i = ind;
				while (lex.lextable.table[ind].lexema != LEX_LEFTHESIS)
				{
					if (lex.idtable.table[lex.lextable.table[ind].idxTI].idType == IT::P)
					{
						generation << lex.idtable.table[lex.lextable.table[ind].idxTI].id << " : ";
						if (lex.idtable.table[lex.lextable.table[ind].idxTI].idDataType == IT::SHORT)
						{
							generation << "SDWORD";
						}
						else if (lex.idtable.table[lex.lextable.table[ind].idxTI].idDataType == IT::STR)
						{
							generation << "DWORD";
						}
						else
						{
							generation << "DWORD";
						}
					}
					if (lex.lextable.table[ind].lexema == LEX_COMMA)
					{
						generation << ", ";
					}
					ind--;
				}
				flag_func = true;
				generation << endl;
				break;
			}
			case LEX_MAIN:
			{
				flag_main = true;
				generation << "main PROC\n";
				break;
			}
			case LEX_EQUAL:
			{
				int result_position = i - 1;
				while (lex.lextable.table[i].lexema != LEX_SEMICOLON)
				{
					switch (lex.lextable.table[i].lexema)
					{
					case LEX_POW:
						generation << "\tcall _pow\n\tpush eax\n";
						break;
					case LEX_ABS:
						generation << "\tcall _abs\n\tpush eax\n";
						break;
					case LEX_LITERAL:
					{
						if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::IDDATATYPE::STR)
						{
							generation << "\tpush offset " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
							break;
						}
						else
						{
							generation << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
							break;
						}
					}
					case LEX_ID:
					{
						if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::IDTYPE::F)
						{
							generation << "\tcall " << lex.idtable.table[lex.lextable.table[i].idxTI].id << "\n\tpush eax\n";
							break;
						}
						generation << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
						break;
					}
					case LEX_STAR:
					{
						generation << "\tpop eax\n\tpop ebx\n";
						generation << "\tmul ebx\n\tpush eax\n";
						break;
					}
					case LEX_PLUS:
					{
						generation << "\tpop eax\n\tpop ebx\n";
						generation << "\tadd eax, ebx\n\tpush eax\n";
						break;
					}
					case LEX_MINUS:
					{
						generation << "\tpop ebx\n\tpop eax\n";
						generation << "\tsub eax, ebx\n\tpush eax\n";
						break;
					}
					case LEX_DIRSLASH:
					{
						generation << "\tpop ebx\n\tpop eax\n";
						generation << "\tcmp ebx,0\n"\
							"\tje SOMETHINGWRONG\n";
						generation << "\tcdq\n";
						generation << "\tidiv ebx\n\tpush eax\n";
						break;
					}
					case LEX_REMDIV:
					{
						generation << "\tpop ebx\n\tpop eax\n";
						generation << "\tcmp ebx,0\n"\
							"\tje SOMETHINGWRONG\n";
						generation << "\tcdq\n";
						generation << "\tidiv ebx\n\tpush edx\n";
						break;
					}
					default:
						break;
					}
					i++;
				}
				if (lex.idtable.table[lex.lextable.table[result_position].idxTI].idDataType == IT::IDDATATYPE::SHORT)
				{
					generation << "\tpop eax\n";
					generation << "\tcmp eax, 32767\n";
					generation << "\tjg overflow\n";
					generation << "\tcmp eax, -32768\n";
					generation << "\tjl overflow\n";
					generation << "\tmov " << lex.idtable.table[lex.lextable.table[result_position].idxTI].id << ", eax";
				}
				else
				{
					generation << "\tpop " << lex.idtable.table[lex.lextable.table[result_position].idxTI].id << "\n";
				}
				generation << endl;
				break;
			}
			case LEX_RETURN:
			{
				generation << "\tpush ";
				i++;
				if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::L && lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::IDDATATYPE::SHORT)
				{
					generation << lex.idtable.table[lex.lextable.table[i++].idxTI].value.vshort << endl;
				}
				else if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::L && lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::IDDATATYPE::STR)
				{
					generation << "OFFSET " << lex.idtable.table[lex.lextable.table[i++].idxTI].id << endl;
				}
				else
				{
					generation << lex.idtable.table[lex.lextable.table[i++].idxTI].id << endl;
				}
				if (flag_func)
				{
					generation << "\tjmp local" << num_of_ret << endl;
					flag_return = true;
				}
				if (flag_main)
				{
					generation << "\tjmp theend\n";
					flag_return = true;
				}
				break;
			}
			case LEX_RIGHTBRACE:
			{
				if (flag_main && !flag_func && lex.lextable.table[i + 1].lexema == LEX_SEMICOLON)
				{
					if (flag_return)
					{
						generation << "theend:\n";
						flag_return = false;
					}
					//generation << FINISH;
					break;
				}
				if (flag_func && lex.lextable.table[i + 1].lexema == LEX_SEMICOLON)
				{
					if (flag_return)
					{
						generation << "local" << num_of_ret++ << ":\n";
						generation << "\tpop eax\n\tret\n";
						flag_return = false;
					}
					generation << func_name << " ENDP\n\n";
					flag_func = false;
				}
				if (!stk.empty())
				{
					switch (stk.top())
					{
					case 1:
						if (lex.lextable.table[i + 1].lexema == LEX_ELSE)
						{
							generation << "\tjmp ifEnd" << ifi.top() << endl;
						}
						else
						{
							generation << "else" << ifi.top() << ":\n";
							ifi.pop();
						}
						stk.pop();
						break;
					case 2:
						generation << "ifEnd" << ifi.top() << ":\n";
						ifi.pop();
						flag_else = false;
						stk.pop();
						break;
					default:
						break;
					}
				}
				break;
			}
			case LEX_LEFTBRACE:
				if (num_of_if && !flag_else && flag_if)
				{
					generation << "ifi" << ifi.top() << ":\n";
					flag_if = false;
				}
				if (flag_else && lex.lextable.table[i - 1].lexema == LEX_ELSE)
				{
					generation << "else" << ifi.top() << ":\n";
				}
				break;
			case LEX_IF:
			{
				flag_if = true;
				stk.push(1);
				num_of_if++;
				ifi.push(num_of_if);
				break;
			}
			case LEX_LEFTHESIS:
			{
				if (num_of_if && lex.lextable.table[i - 1].lexema == LEX_IF)
				{
					generation << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
					generation << "\tcmp eax, " << lex.idtable.table[lex.lextable.table[i + 3].idxTI].id << endl;
					if (lex.lextable.table[i + 2].lexema == LEX_MORE)
					{
						generation << "\tjg ifi" << num_of_if << endl;
						generation << "\tjle else" << num_of_if << endl;
					}
					else if (lex.lextable.table[i + 2].lexema == LEX_LESS)
					{
						generation << "\tjl ifi" << num_of_if << endl;
						generation << "\tjge else" << num_of_if << endl;
					}
					else if (lex.lextable.table[i + 2].lexema == LEX_EQUALEQUAL)
					{
						generation << "\tjz ifi" << num_of_if << endl;
						generation << "\tjnz else" << num_of_if << endl;
					}
					else if (lex.lextable.table[i + 2].lexema == LEX_NOTEQUAL)
					{
						generation << "\tjnz ifi" << num_of_if << endl;
						generation << "\tjz else" << num_of_if << endl;
					}
					else if (lex.lextable.table[i + 2].lexema == LEX_MOREEQUAL)
					{
						generation << "\tjge ifi" << num_of_if << endl;
						generation << "\tjl else" << num_of_if << endl;
					}
					else if (lex.lextable.table[i + 2].lexema == LEX_LESSEQUAL)
					{
						generation << "\tjle ifi" << num_of_if << endl;
						generation << "\tjg else" << num_of_if << endl;
					}
				}
				break;
			}
			case LEX_ELSE:
			{
				flag_else = true;
				stk.push(2);
				break;
			}
			case LEX_PRINT:
			{
				switch (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idDataType)
				{
				case IT::IDDATATYPE::SHORT:
					generation << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall noutl\n";
					break;
				case IT::IDDATATYPE::BOOL:
					generation << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
					generation << "\tcmp eax, 0" << endl;
					generation << "\tjz " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "T" << endl;
					generation << "\tjnz " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "F" << endl;
					generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "T:" << endl;;
					generation << "\npush offset false" << "\ncall soutl\n";
					generation << "\njmp " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << endl;
					generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "F:" << endl;;
					generation << "\npush offset true" << "\ncall soutl\n";
					generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << ":" << endl;;

					num_of_boolCompare++;
					break;
				case IT::IDDATATYPE::STR:
					if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idType == IT::IDTYPE::L)
						generation << "\npush offset " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall soutl\n";
					else
						generation << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall soutl\n";
					break;
				}
				break;
			}
			}
		}
		generation << FINISH;
		generation.close();
	}
}