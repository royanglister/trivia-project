#include "MagshMessageServer.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>

// using static const instead of macros 
static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

MagshMessageServer::MagshMessageServer()
{
	// notice that we step out to the global namespace
	// for the resolution of the function socket
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception( __FUNCTION__ " - socket");
}

MagshMessageServer::~MagshMessageServer()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_socket);
	}
	catch (...) {}
}

void MagshMessageServer::serve()
{
	bindAndListen();

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");
		handleNewClient();
	}
}

void getDirectInputOfExit()
{
	std::string input = "";
	getline(std::cin, input);

	if (input == "EXIT")
	{
		_exit(0);
	}
}


// listen to connecting requests from clients
// accept them, and create thread for each client
void MagshMessageServer::bindAndListen()
{
	std::thread t(getDirectInputOfExit);
	t.detach();

	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

void MagshMessageServer::handleNewClient()
{
	std::string data = "";
	LoginRequestHandler rqstHndlr;
	char buffer[SIZE] = { 0 };
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted!");
	// Inserting the client into the map of clients.
	std::pair <SOCKET, LoginRequestHandler> client(client_socket, rqstHndlr);
	_clients.insert(client);
	
	

	// create new thread for client	and detach from it
	std::thread tr(&MagshMessageServer::clientHandler, this, client_socket);
	tr.detach();

	/*
	Helper::sendData(client_socket, "Hello");
	data = recv(client_socket, buffer, (SIZE - 1), 0); // Receiving the client's response.
	data = Helper::getStringPartFromSocket(client_socket, FIVE);
	cout << "data: " << data << endl;

	if (data == "Hello")
	{
		//printf("Client's response: %s\n", buffer);
	}
	*/
}

void MagshMessageServer::clientHandler(SOCKET client_socket)
{
	
	closesocket(client_socket);
}
