/**
Rekisterin muokkaus- ja luku -luokka
*/

#include <string>
#include <iostream>
#include <vector>
#include "Windows.h"

/**

TO DO:
	- parannella konstruktiota
	- DWORD:ien kirjoitus (tämä on kyllä jo) ja haku (tätä ei ole vielä)
	- virheiden ilmoituksen parantaminen
	- avainten vahvempi tarkastelu

*/

namespace MyRegistryClass
{
	/// Luokka rekisterin muokkausta varten
	class __declspec(dllexport) MyRegistryClass
	{
	public:
		MyRegistryClass();
		~MyRegistryClass();
		/** Avaa rekisterin */
		void openRegister(std::string regName);
		/** Kirjoittaa rekisteriin */
		void write(std::string keyName, std::string value);
		/** Kirjoittaa rekisteriin, TOSIN EI OLE KÄYTÖSSÄ */
		//void write(std::string keyName, DWORD value);
		/** Sulkee rekisterin */
		void closeRegister();
		/** poistaa arvon rekisteristä */
		void deleteValue(std::string subkey);
		/** laskee rekisterin arvojen määrän */
		DWORD numberOfValues();
		/** lisää string tyyppisen muuttujan rekisteriin */
		void addValue(std::string name, std::string content);
		/** Luo uuden avaimen rekisteriin */
		void createKey(std::string name);
		/** Tarkistaa onko avain jo olemassa */
		bool keyExists(std::string name);
		/** Palauttaa avaimen sisällön */
		std::string readValue(std::string name);


	private:
		/* variables  */
		HKEY key;

		/** methods */
		/** Kertoo avaimen arvon tyypin */
		DWORD subKeyType(std::string sKey);
	};
} // namespace MyRegistryClass