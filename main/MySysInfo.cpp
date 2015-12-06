#include "MySysInfo.h"
#include <TlHelp32.h>
#include <Psapi.h>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <wchar.h>
//#include <stdio.h>

#define LANGUAGE 1
#define DIV 1024 // used for byte -> KB -conversion

#if LANGUAGE == 1
//#include "english.h"
#endif // LANGUAGE == "english"

namespace MySysInfo
{

	/**
	prints all processes
	*/
	void MySysInfo::printAllProcessesWithInfo()
	{
		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;
		DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printError("CreateToolhelp32Snapshot (of processes)");
			return;
		}

		// Set the size of the structure before using it.
		pe32.dwSize = sizeof(PROCESSENTRY32);

		// Retrieve information about the first process, and exit if unsuccessful
		if (Process32First(hProcessSnap, &pe32) == FALSE)
		{
			printError("Process32First"); // show cause of failure
			CloseHandle(hProcessSnap);          // clean the snapshot object
			return;
		}

		// Now walk the snapshot of processes, and display information about each process in turn
		do
		{
			this->numberOfProcesses++;
			wprintf(TEXT("\nPROCESS:  %s"), pe32.szExeFile);

			// Retrieve the priority class.
			dwPriorityClass = 0;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			if (hProcess == NULL)
			{
				std::cout << " | ERROR AT: ";
				printError("OpenProcess");
			}
			else
			{
				dwPriorityClass = GetPriorityClass(hProcess);
				if (!dwPriorityClass)
				{
					printError("GetPriorityClass");
				}
				CloseHandle(hProcess);
			}
			std::cout << std::endl << "\t  Process ID		= " << pe32.th32ProcessID << std::endl;
			std::cout << "\t  Thread count		= " << pe32.cntThreads << std::endl;
			std::cout << "\t  Parent process ID	= " << pe32.th32ParentProcessID << std::endl;
			std::cout << "\t  Priority base		= " << pe32.pcPriClassBase << std::endl;
			if (dwPriorityClass)
				std::cout << "\t  Priority class	= " << dwPriorityClass << std::endl;

		} while (Process32Next(hProcessSnap, &pe32));

		std::cout << std::endl << "number of process: " << this->numberOfProcesses << std::endl;
		this->numberOfProcesses = 0;
		CloseHandle(hProcessSnap);
		return;
	}

	void MySysInfo::printAllProcessesWithNoInfo()
	{
		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;
		DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printError("CreateToolhelp32Snapshot (of processes)");
			return;
		}

		// Set the size of the structure before using it.
		pe32.dwSize = sizeof(PROCESSENTRY32);

		// Retrieve information about the first process, and exit if unsuccessful
		if (Process32First(hProcessSnap, &pe32) == FALSE)
		{
			printError("Process32First"); // show cause of failure
			CloseHandle(hProcessSnap);          // clean the snapshot object
			return;
		}

		// Now walk the snapshot of processes, and display information about each process in turn
		do
		{
			this->numberOfProcesses++;
			wprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
		} while (Process32Next(hProcessSnap, &pe32));

		std::cout << std::endl << "number of process: " << this->numberOfProcesses << std::endl;
		this->numberOfProcesses = 0;
		CloseHandle(hProcessSnap);
		return;
	}

	void MySysInfo::printAllProcessesWithDetailedInfo()
	{
		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;
		DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printError("CreateToolhelp32Snapshot (of processes)");
			return;
		}

		// Set the size of the structure before using it.
		pe32.dwSize = sizeof(PROCESSENTRY32);

		// Retrieve information about the first process, and exit if unsuccessful
		if (Process32First(hProcessSnap, &pe32) == FALSE)
		{
			printError("Process32First"); // show cause of failure
			CloseHandle(hProcessSnap);          // clean the snapshot object
			return;
		}

		// Now walk the snapshot of processes, and display information about each process in turn
		do
		{
			this->numberOfProcesses++;
			wprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);

			// Retrieve the priority class.
			dwPriorityClass = 0;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			if (hProcess == NULL)
			{
				std::cout << std::endl << "{";
				printError("OpenProcess");
				std::cout << std::endl << "}" << std::endl;
			}
			else
			{
				dwPriorityClass = GetPriorityClass(hProcess);
				if (!dwPriorityClass)
				{
					std::cout << "{";
					printError("GetPriorityClass");
					std::cout << std::endl << "}" << std::endl;
				}
				CloseHandle(hProcess);
			}

			std::cout << std::endl << "\t  Process ID		= " << pe32.th32ProcessID << std::endl;
			std::cout << "\t  Thread count		= " << pe32.cntThreads << std::endl;
			std::cout << "\t  Parent process ID	= " << pe32.th32ParentProcessID << std::endl;
			std::cout << "\t  Priority base		= " << pe32.pcPriClassBase << std::endl;
			if (dwPriorityClass)
				std::cout << "\t  Priority class	= " << dwPriorityClass << std::endl;

		} while (Process32Next(hProcessSnap, &pe32));

		std::cout << std::endl << "number of process: " << this->numberOfProcesses << std::endl;
		this->numberOfProcesses = 0;
		CloseHandle(hProcessSnap);
		return;

	}

	void MySysInfo::printSystemMemory()
	{
		MEMORYSTATUSEX memStats;
		memStats.dwLength = sizeof(memStats);
		GlobalMemoryStatusEx(&memStats);

		std::cout << "Total memory in use: " << memStats.dwMemoryLoad << "% / " << (memStats.ullAvailPhys / 1048576) << "MB" << std::endl;
		std::cout << "Total memory in system: " << memStats.ullTotalPhys << "kB" << std::endl;
		std::cout << "Total memory in use: " << memStats.ullAvailPhys << "kB" << std::endl;
		std::cout << "GB: " << this->BytesToGB(memStats.ullTotalPhys) << std::endl;

		return;
	}

	void MySysInfo::printProcess(std::wstring name)
	{
		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;
		DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printError("CreateToolhelp32Snapshot (of processes)");
			return;
		}

		// Set the size of the structure before using it.
		pe32.dwSize = sizeof(PROCESSENTRY32);

		// Retrieve information about the first process, and exit if unsuccessful
		if (Process32First(hProcessSnap, &pe32) == FALSE)
		{
			printError("Process32First"); // show cause of failure
			CloseHandle(hProcessSnap);          // clean the snapshot object
			return;
		}

		// Now walk the snapshot of processes, and display information about each process in turn
		do
		{
			if (_wcsicmp(pe32.szExeFile, name.data()) == 0)
			{
				wprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);

				// Retrieve the priority class.
				dwPriorityClass = 0;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if (hProcess == NULL)
				{
					std::cout << std::endl << "{";
					printError("OpenProcess");
					std::cout << std::endl << "}" << std::endl;
				}
				else
				{
					dwPriorityClass = GetPriorityClass(hProcess);
					if (!dwPriorityClass)
					{
						std::cout << "{";
						printError("GetPriorityClass");
						std::cout << std::endl << "}" << std::endl;
					}
					CloseHandle(hProcess);
				}

				std::cout << std::endl << "\t  Process ID		= " << pe32.th32ProcessID << std::endl;
				std::cout << "\t  Thread count		= " << pe32.cntThreads << std::endl;
				std::cout << "\t  Parent process ID	= " << pe32.th32ParentProcessID << std::endl;
				std::cout << "\t  Priority base		= " << pe32.pcPriClassBase << std::endl;
				if (dwPriorityClass)
					std::cout << "\t  Priority class	= " << dwPriorityClass << std::endl;
			}
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);
		return;
	}

	bool MySysInfo::printProcess(DWORD pid)
	{
		return this->PrintProcessNameAndID(pid);
	}


	/***************************
	*
	*		PRIVATE METHODS
	*
	***************************/

	bool MySysInfo::PrintProcessNameAndID(DWORD processID)
	{

		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;
		DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printError("CreateToolhelp32Snapshot (of processes)");
			return 0;
		}

		// Set the size of the structure before using it.
		pe32.dwSize = sizeof(PROCESSENTRY32);

		// Retrieve information about the first process, and exit if unsuccessful
		if (Process32First(hProcessSnap, &pe32) == FALSE)
		{
			printError("Process32First"); // show cause of failure
			CloseHandle(hProcessSnap);          // clean the snapshot object
			return 0;
		}

		// Now walk the snapshot of processes, and display information about each process in turn
		do
		{
			if (processID == pe32.th32ProcessID)
			{
				wprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);

				// Retrieve the priority class.
				dwPriorityClass = 0;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if (hProcess == NULL)
				{
					std::cout << std::endl << "{";
					printError("OpenProcess");
					std::cout << std::endl << "}" << std::endl;
				}
				else
				{
					dwPriorityClass = GetPriorityClass(hProcess);
					if (!dwPriorityClass)
					{
						std::cout << "{";
						printError("GetPriorityClass");
						std::cout << std::endl << "}" << std::endl;
					}
					CloseHandle(hProcess);
				}

				std::cout << std::endl << "\t  Process ID		= " << pe32.th32ProcessID << std::endl;
				std::cout << "\t  Thread count		= " << pe32.cntThreads << std::endl;
				std::cout << "\t  Parent process ID	= " << pe32.th32ParentProcessID << std::endl;
				std::cout << "\t  Priority base		= " << pe32.pcPriClassBase << std::endl;
				if (dwPriorityClass)
				{
					std::cout << "\t  Priority class	= " << dwPriorityClass << std::endl;
				}
				CloseHandle(hProcessSnap);
				return 1;
			}
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);
		return 0;
	}



	inline void MySysInfo::printError(std::string msg)
	{
		std::cout << msg << ", ERROR: " << GetLastError();
		return;
	}

	/********************************************
	*
	*		CONVERSIONS:
	*		1 megabits
	*		(informal notation: kilobyte = 1024 bytes)
	*		bits		1048576
	*		bytes		131072
	*		kilobits	1024
	*		kilobytes	128
	*		megabits	1
	*		megabytes	0.125
	*		gigabits	0.0009765625
	*		gigabytes	0.0001220703125
	*		terabytes	1.19209289550781e-07
	*		petabytes	1.16415321826935e-10
	*
	*******************************************/


	inline int MySysInfo::BytesToMB(DWORD amount)
	{
		return  (amount / 1048576);
	}

	inline int MySysInfo::BytesToGB(DWORD amount)
	{
		return  (amount / 1048576);
	}
} // namespace MySysInfo