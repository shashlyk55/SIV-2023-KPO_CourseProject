#include <iostream>

extern "C"
{

	int __stdcall _pow(int a, int b)
	{
		return pow(b, a);
	}
	int __stdcall _abs(int a)
	{
		return abs(a);
	}
	int __stdcall noutl(int value)
	{
		std::cout << value << std::endl;
		return 0;
	}
	int __stdcall soutl(char* ptr)
	{
		setlocale(LC_ALL, "Rus");
		if (ptr == nullptr)
		{
			std::cout << std::endl;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
		std::cout << std::endl;
		return 0;
	}
	int __stdcall SYSPAUSE()
	{
		system("pause");
		return 0;
	}
}