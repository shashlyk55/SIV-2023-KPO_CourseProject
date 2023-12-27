#include "pch.h"
#include <locale>
#include <cwchar>

int _tmain(int argc, _TCHAR** argv)
{
	//argc = 3;
	//argv[1] = (_TCHAR*)L"-in:D:\\KPO_3sem\\SIV-2023\\SIV-2023\\in.txt";
	//argv[1] = (_TCHAR*)L"-in:D:\\KPO_3sem\\SIV-2023\\SIV-2023\\SemErrors.txt";
	//argv[2] = (_TCHAR*)L"-out:D:\\KPO_3sem\\SIV-2023\\SIV-2023\\SIV_result.asm";
	//argv[3] = (_TCHAR*)L"-log:D:\\KPO_3sem\\SIV-2023\\SIV-2023\\Logger.txt";
	//argv[4] = (_TCHAR*)L"-an:D:\\KPO_3sem\\SIV-2023\\SIV-2023\\Analize.txt";

	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		std::ofstream clearFile(parm.an, std::ios_base::trunc);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);

		In::IN in = In::GetIn(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::WriteLine(log, "No forbidden characters\n", "");

		Log::WriteLine(log, "Tokenization : ", "");
		Tokens::TokenTable tokentable = Tokens::Tokenize(in);
		Log::WriteLine(log, " Completed successfully\n", "");

		Log::WriteLine(log, "Lexical analysis : ", "");
		LA::LEX lex = LA::FillingInTables(tokentable);
		Log::WriteLine(log, " Completed successfully\n", "");

		LT::SaveToFile(lex.lextable, parm.an);
		IT::SaveToFile(lex.idtable, parm.an);

		ofstream fs(parm.an, std::ios_base::app);
		Log::WriteLine(log, "Syntax analysis : ", "");
		MFST_TRACE_START(fs)
			MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(fs);
		mfst.savededucation();
		mfst.printrules(fs);
		Log::WriteLine(log, " Completed successfully\n", "");

		Log::WriteLine(log, "Semantic analysis : ", "");
		CallSemantic(lex.lextable, lex.idtable);
		Log::WriteLine(log, " Completed successfully\n", "");

		Log::WriteLine(log, "Polish notation  : ", "");
		Polish::CallPolishNotation(lex.lextable, lex.idtable);
		Log::WriteLine(log, " Completed successfully\n", "");

		LT::SaveToFile(lex.lextable, parm.an);	

		Log::WriteLine(log, "Code generation : ", "");
		CodeGeneration::CodeGeneration(lex, parm.out);
		Log::WriteLine(log, " Completed successfully\n", "");


		Log::Close(log);
		std::cout << "Code translation completed successfully\n";
	}
	catch (Error::ERROR e)
	{
		std::cout << "Произошла ошибка\n";
		Log::WriteLine(log, "- ERROR\n", "");
		Log::WriteError(log, e);
	}
	return 0;
}