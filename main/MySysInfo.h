#include <iostream>
#include <string>
#include <windows.h>

namespace MySysInfo
{	
	/**

	TO DO:
		- parannella printtaus prosessia
			- siirt�� kaiken parametrina annettuun vectoriin.
		- korjailla luokkaa yleisesti
	
	*/

	class MySysInfo
	{
	public:
		MySysInfo() : numberOfProcesses{ 0 } {};
		~MySysInfo(){};
		/** Printtaa prosessin tiedot PID:in perusteella */
		bool printProcess(DWORD pid);
		/** printaa prosessien tiedot nimen perusteella */
		void printProcess(std::wstring pid);
		/** Printtaa prosession kaikki tiedot minimaalisin tiedoin */
		void printAllProcessesWithInfo();
		/** Printtaa kaikkien kaikki tiedot */
		void printAllProcessesWithDetailedInfo();
		/** Printtaa prosessit ilman tietoja */
		void printAllProcessesWithNoInfo();
		/** printtaa j�rjestelm�n muistin tiedot */
		void printSystemMemory();

	private:
		/* Printtaa prosessin tiedot PID:in perusteella */
		bool PrintProcessNameAndID(DWORD processID);
		/** Prosessien m��r�, k�yt�nn�ss� t�ysin turha muuttuja */
		int numberOfProcesses;
		/** Tavu megatavu muunnos */
		int BytesToMB(DWORD amount);
		/** Tavu gigatavu muunnos */
		int BytesToGB(DWORD amount);
		/** printtaa virheen + parametrin� annetun virheviestin */
		void printError(std::string msg);
		/** hakee virheviestin, en oikeastaan tarpeellinen */
		std::string getError();
	};
} // namespace MySysInfo