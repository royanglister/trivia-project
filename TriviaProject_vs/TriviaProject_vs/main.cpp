#pragma comment (lib, "ws2_32.lib")
// TODO lean and mean
#include "MagshMessageServer.h"
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>

// In a lot of places in the code we pass to function constant reference (const Bla&) to an object and not the object itself.

int main()
{
	// Q: why is this try necessary ?
	// A: we want to know what happened that made the server crush
	try
	{
		// NOTICE at the end of this block the WSA will be closed 
		WSAInitializer wsa_init;
		MagshMessageServer md_server;
		md_server.serve();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main!" << std::endl;
	}
}
