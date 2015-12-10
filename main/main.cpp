// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <codecvt>

#include "MyRegistryClass.h"
#include "MySysInfo.h"
#include "Language.h"

#define LANGUAGE 2

#if LANGUAGE == FINNISH
#include "Finnish.h"
#elif LANGUAGE == ENGLISH
#include "English.h"
#endif

void printOptions();

int _tmain(int argc, _TCHAR* argv[])
{
	MyRegistryClass::MyRegistryClass* reg = new MyRegistryClass::MyRegistryClass();
	MySysInfo::MySysInfo* info = new MySysInfo::MySysInfo();

	// check if the key exists, if not, it'll be created
	if (reg->keyExists("software\\Process_program_vevasami") == false)
		reg->createKey("software\\Process_program_vevasami");

	reg->openRegister("software\\Process_program_vevasami");
	reg->write("moro", "00000000");
	std::string regIn = reg->readValue("moro");
	std::cout << "regIn: " << regIn << std::endl;

	/*
	komentorivioptioiden parsiminen

	-h
	- kerrotaan kaikki parametrit ja merkitykset
	-pid <NUMERO_TAHAN>
	-name "tänne nimi"
	-memory
	-noMenu

	*/

	bool menu = true;

	for (int i = 1; argc > i; i++)
	{
		if (_tcscmp(L"-h", argv[i]) == 0)
		{
			printOptions();
		}
		else
			if (_tcscmp(L"-pid", argv[i]) == 0)
			{
				int j = i + 1;
				int n = _tstoi(argv[j]);
				info->printProcess(n);
			}
			else
				if (_tcscmp(L"-name", argv[i]) == 0)
				{
					int j = i + 1;
					std::wstring name = argv[j];
					info->printProcess(name);
				}
				else
					if (_tcscmp(L"-memory", argv[i]) == 0)
					{
						info->printSystemMemory();
					}
					else
						if (_tcscmp(L"-noMenu", argv[i]) == 0 || _tcscmp(L"-nomenu", argv[i]) == 0)
						{
							menu = false;
						}
	}

	if (menu == true){
		std::string answer = "";
		while (answer != "3")
		{
			std::cout << HEADER_1 << std::endl;
			std::cout << HEADER_2 << std::endl;
			std::cout << "1. " << MENU_LINE_PROCESS_ALL << std::endl;
			std::cout << "2. " << MENU_LINE_MEMORY << std::endl;
			std::cout << "3. " << MENU_LINE_PROCESS_SEARCH << std::endl;
			std::cout << "4. " << MENU_LINE_EXIT << std::endl;
			std::cout << "> ";
			std::cin >> answer;

			// PROCESS DATA
			if (answer == "1")
			{
				std::cout << "1. " << INFO_LEVEL_1 << std::endl;
				std::cout << "2. " << INFO_LEVEL_2 << std::endl;
				std::cout << "3. " << INFO_LEVEL_3 << std::endl;

				std::cout << INFO_QUESTION << std::endl;
				std::cout << "> ";
				int ans = 0;
				std::cin >> ans;

				switch (ans)
				{
				case 1:
				{
					info->printAllProcessesWithNoInfo();
				}
				break;
				case 2:
				{

					info->printAllProcessesWithInfo();
				}
				break;
				case 3:
				{

					info->printAllProcessesWithDetailedInfo();
				}
				break;
				}


			}
			else
				// MEMORY DATA
				if (answer == "2")
				{
					std::cout << MEMORY_STATS_HEADER << std::endl;
					info->printSystemMemory();
				}
				else
					// PROCESSES SEARCH
					if (answer == "3")
					{
						std::cout << "1. " << QUESTION_PROMT_PID << std::endl;
						std::cout << "2. " << QUESTION_PROMT_NAME << std::endl;
						std::string answer = "";
						std::cin >> answer;

						if (answer == "1")
						{
							std::cout << ENTER_PROCESS_PID << std::endl;
							std::cout << "> ";
							int answer = 0;
							std::cin >> answer;
							info->printProcess(answer);
						}
						else
							if (answer == "2")
							{
								std::cout << ENTER_PROCESS_NAME << std::endl;
								std::cout << "> ";
								std::wstring answer = L"";
								std::wcin >> answer;
								info->printProcess(answer);
								std::cout << std::endl;
							}
					}
					else
						// EXIT
						if (answer == "4")
						{
							std::cout << GOODBYE << std::endl;
							break;
						}
						else
						{
							std::cout << ERROR_ANSWER_UNKNOWN << std::endl;
						}

			answer.clear();
		}
	}

	reg->write("moro", "11111111");
	regIn = reg->readValue("moro");
	std::cout << "regIn: " << regIn << std::endl;

	char c;
	std::cin >> c;

	return 0;
}

void printOptions()
{
	/*
	komentorivioptioiden parsiminen

	-h
	- kerrotaan kaikki parametrit ja merkitykset
	-pid <NUMERO_TAHAN>
	-name "tänne nimi"
	-memory
	-noMenu
	*/

	std::cout << "-h" << std::endl;
	std::cout << COMMAND_H << std::endl;

	std::cout << "-pid" << std::endl;
	std::cout << COMMAND_PID << std::endl;

	std::cout << "-name" << std::endl;
	std::cout << COMMAND_NAME << std::endl;

	std::cout << "-memory" << std::endl;
	std::cout << COMMAND_MEMORY << std::endl;

	std::cout << "-noMenu" << std::endl;
	std::cout << COMMAND_NOMENU << std::endl;
}