// GProblems.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gray_code.h"


int _tmain(int argc, _TCHAR* argv[])
{
	gray_code<4> gray_from_int = gray_code<4>(6);
	gray_from_int.print_binary();
	gray_from_int.print_gray();

	gray_code<4> gray_from_string = gray_code<4>("0001110");
	gray_from_string.print_binary();
	gray_from_string.print_gray();

	gray_code<4> gray_from_binary = gray_code<4>(std::bitset<4>("0110"));
	gray_from_binary.print_binary();
	gray_from_binary.print_gray();

	gray_from_binary.increment();
	gray_from_binary.print_binary();
	gray_from_binary.print_gray();
	return 0;
}

