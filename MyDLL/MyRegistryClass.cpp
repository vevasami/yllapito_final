#include "MyRegistryClass.h"
#include <stdio.h>
#include "Windows.h"

/*
TO DO:
- kun luokka toimii kunnolla, virheet kirjataan logiin (?).
*/

MyRegistryClass::MyRegistryClass::MyRegistryClass()
{
	return;
}

/**
avaa rekisterin
*/
void MyRegistryClass::MyRegistryClass::openRegister(std::string keyName)
{
	int n = 0;

	if ((n = RegOpenKeyExA(HKEY_CURRENT_USER, (LPCSTR)(keyName.data()), 0, KEY_ALL_ACCESS, &key)) == ERROR_SUCCESS)
	{
		std::cout << "Registry open success." << std::endl;
	}
	else
	{
		std::cout << "ERROR: " << n << ". Registry open fail." << std::endl;
	}
	return;
}

/**
write method for string values
*/
void MyRegistryClass::MyRegistryClass::write(std::string keyName, std::string value)
{
	int n = 0;

	if ((n = RegSetValueExA(key, (LPCSTR)(keyName.data()), 0, this->subKeyType(keyName), (const BYTE*)(value.data()), value.size() + 1)) == ERROR_SUCCESS)
	{
		std::cout << "successfull write at: " << keyName << std::endl;
	}
	else
	{
		std::cout << "unsuccessfull write at: " << keyName << std::endl;
	}
}

/* DWORD ==  unsigned long */
/**
write method for DWORD values
*/
void MyRegistryClass::MyRegistryClass::write(std::string keyName, DWORD value)
{
	int n = 0;

	int o = 0;

	if ((n = RegSetValueExA(key, (LPCSTR)(keyName.data()), 0, this->subKeyType(keyName), (const BYTE*)&value, sizeof(value)) == ERROR_SUCCESS))
	{
		std::cout << "successfull write at: " << keyName << std::endl;
	}
	else
	{
		std::cout << "unsuccessfull write at: " << keyName << std::endl;
	}
}

/**
Avaimen tyypin haku
*/
DWORD MyRegistryClass::MyRegistryClass::subKeyType(std::string sKey)
{
	int retCode = -1;
	DWORD type;

	retCode = RegQueryValueExA(key,
		sKey.data(),
		NULL,
		&type,
		NULL,
		NULL);

	if (retCode == ERROR_SUCCESS)
	{
		/*
		DWORD ==  unsigned long
		REG_NONE 0
		REG_SZ 1
		REG_EXPAND_SZ 2
		REG_BINARY 3
		REG_DWORD 4
		REG_DWORD_LITTLE_ENDIAN 4
		REG_DWORD_BIG_ENDIAN 5
		REG_LINK 6
		REG_MULTI_SZ 7
		REG_RESOURCE_LIST 8
		REG_FULL_RESOURCE_DESCRIPTOR 9
		REG_RESOURCE_REQUIREMENTS_LIST 10
		REG_QWORD 11
		REG_QWORD_LITTLE_ENDIAN 11
		*/
		return (DWORD)type;
	}
	return 42;
}

/**
poistaa rekisteristä arvon
*/
void MyRegistryClass::MyRegistryClass::deleteValue(std::string subkey)
{
	int n = RegDeleteValueA(key, (LPCSTR)(subkey.data()));
	if (n == ERROR_SUCCESS)
	{
		std::cout << "subkey \"" << subkey << "\" deleted successfully." << std::endl;
	}
	else
	{
		/* ERROR: 2 == subkey not found  */
		std::cout << "ERROR: " << n << std::endl;
		std::cout << "unable to delete subkey \"" << subkey << "\"." << std::endl;
	}

}

/**
laskee rekisterin arvojen määrän
*/
DWORD MyRegistryClass::MyRegistryClass::numberOfValues()
{
	DWORD numberOfValues = 0;
	int retCode = RegQueryInfoKey(
		key,						// key handle 
		NULL,              // buffer for class name 
		NULL,         // size of class string 
		NULL,						// reserved 
		NULL,             // number of subkeys 
		NULL,          // longest subkey size 
		NULL,          // longest class string 
		&numberOfValues,              // number of values for this key 
		NULL,          // longest value name 
		NULL,       // longest value data 
		NULL, // security descriptor 
		NULL);     // last write time 

	if (retCode == ERROR_SUCCESS)
	{
		return numberOfValues;
	}
	else
	{
		return -1;
	}
}

/**
lisää arvon rekisteriin
*/
void MyRegistryClass::MyRegistryClass::addValue(
	std::string valueName,
	std::string content)
{
	int n = 0;

	if ((n = RegSetValueExA(key, (LPCSTR)(valueName.data()), 0, REG_SZ, (const BYTE*)(content.data()), content.size() + 1)) == ERROR_SUCCESS)
	{
		std::cout << "successfull creation of: " << valueName << std::endl;
	}
	else
	{
		std::cout << "successfull creation of: " << valueName << std::endl;
	}
}

/**
sulkee rekisterin
*/
void MyRegistryClass::MyRegistryClass::closeRegister()
{
	RegCloseKey(key);
	key = NULL;
	return;
}