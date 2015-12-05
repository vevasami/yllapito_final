/**

käsittelee ja hyödyntää Windows - rekisteriä:
- luo ja lukee rekisteri - avaimia ja - arvoja ohjelman käynnistyksen yhteydessä
- kirjoittaa arvot takaisin rekisteriin, kun ohjelma suljetaan

*/

#include <string>
#include <iostream>
#include <vector>
#include "Windows.h"



namespace MyRegistryClass
{
	 class __declspec(dllexport) MyRegistryClass
	{
	public:
		MyRegistryClass();
		~MyRegistryClass();
		void openRegister(std::string regName);
		void write(std::string keyName, std::string value);
		void write(std::string keyName, DWORD value);
		void closeRegister();
		void deleteValue(std::string subkey);
		DWORD numberOfValues();
		void addValue(std::string name, std::string content);
		//void addValue(std::string name, std::string content, unsigned int type);
		//void getAllValues(std::vector<MyPair>* vector);

	private:
		// variables 
		HKEY key;

		// methods
		DWORD subKeyType(std::string sKey); // THIS IS A PRIVATE METHOD, HERE (in public methods) BECAUSE TESTING
	};
} // namespace MyRegistryClass