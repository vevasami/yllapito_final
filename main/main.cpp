// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyRegistryClass.h"
#include "MySysInfo.h"
#include <iostream>
#include <string>
#include "Language.h"

#define LANGUAGE 2

#if LANGUAGE == FINNISH
#include "Finnish.h"
#elif LANGUAGE == ENGLISH
#include "English.h"
#endif




int _tmain(int argc, _TCHAR* argv[])
{
	MyRegistryClass::MyRegistryClass* reg = new MyRegistryClass::MyRegistryClass();
	reg->openRegister("software\\vevarisami_2");
	reg->write("moro", "999777555");

	MySysInfo::MySysInfo* info = new MySysInfo::MySysInfo();

	reg->createKey("software\\ohjelma");
	std::string str = reg->readValue("m");

	if (str.empty())
		std::cout << "str is empty" << std::endl;
	else
		std::cout << "str: " << str << std::endl;

	/*
	komentorivioptioiden parsiminen
	*/


	std::string answer = "";
	while (answer != "3")
	{
		std::cout << HEADER_1 << std::endl;
		std::cout << HEADER_2 << std::endl;
		std::cout << MENU_LINE_1 << std::endl;
		std::cout << MENU_LINE_2 << std::endl;
		std::cout << MENU_LINE_3 << std::endl;
		std::cout << "> ";
		std::cin >> answer;

		if (answer == "1")
		{
			std::cout << "1. Prosessi data" << std::endl;
		}
		else if (answer == "2")
		{
			std::cout << "2. Muisti data" << std::endl;
		}
		else if (answer == "3")
		{
			std::cout << "3. Exit" << std::endl;
			return 0;
		}
		else
		{
			std::cout << "Tuntematon." << std::endl;
		}

		answer.clear();

	}

	return 0;
}