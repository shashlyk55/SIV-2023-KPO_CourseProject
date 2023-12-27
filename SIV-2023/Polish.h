#pragma once
#include "pch.h"
#include "LT.h"
#include "IT.h"
#include <iostream>
#include <stack>
#include <queue>

namespace Polish
{
	void CallPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable);
	void polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
	int priorityIs(LT::Entry entry);
}