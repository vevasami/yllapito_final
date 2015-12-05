// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyRegistryClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	MyRegistryClass::MyRegistryClass* reg = new MyRegistryClass::MyRegistryClass();
	reg->openRegister("software\\vevarisami_2");
	reg->write("moro", "999777555");




	return 0;
}

