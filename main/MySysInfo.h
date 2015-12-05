#include <iostream>
#include <string>
#include <windows.h>

namespace MySysInfo
{
	class MySysInfo
	{
	public:
		MySysInfo() : numberOfProcesses{ 0 } {};
		~MySysInfo(){};
		bool printProcess(DWORD pid);
		void printProcess(std::wstring pid);
		void printAllProcessesWithInfo();
		void printAllProcessesWithDetailedInfo();
		void printAllProcessesWithNoInfo();
		void printSystemMemory();

	private:
		bool PrintProcessNameAndID(DWORD processID);
		int numberOfProcesses;
		int BytesToMB(DWORD amount);
		int BytesToGB(DWORD amount);
		void printError(std::string msg);
		std::string getError();
	};
} // namespace MySysInfo