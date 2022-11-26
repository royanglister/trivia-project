#include "MagshMessageServer.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include "IRequestHandler.h"
#include <thread>
#include "SqliteDataBase.h"

// using static const instead of macros 
static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

MagshMessageServer::MagshMessageServer() : m_database(new SqliteDataBase())
{
	// Stepping out to the global namespace for the resolution of the function socket.
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception( __FUNCTION__ " - socket");

	m_factory = RequestHandlerFactory(m_database);
}

MagshMessageServer::~MagshMessageServer()
{
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
		acceptClient();
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

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void MagshMessageServer::acceptClient()
{
	std::string data = "";
	char buffer[SIZE] = { 0 };
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	
	// create new thread for client	and detach from it
	std::thread tr(&MagshMessageServer::clientHandler, this, client_socket);
	tr.detach();

	m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, m_factory.createLoginRequestHandler()));
}

void MagshMessageServer::clientHandler(SOCKET client_socket)
{
	IRequestHandler::RequestInfo requestInfo;
	IRequestHandler::RequestResult requestResult;

	try
	{	
		while (true)
		{
			requestInfo = getRequestInfo(client_socket);
			requestResult = m_clients[client_socket]->handleRequest(requestInfo);
			m_clients[client_socket] = requestResult.newHandler;
			Helper::sendData(client_socket, requestResult.response);
		}
	}

	catch (const std::exception& e)
	{
		//m_factory.getLoginManager().logout(the username);
	}

	closesocket(client_socket);
}

IRequestHandler::RequestInfo MagshMessageServer::getRequestInfo(const SOCKET client_socket)
{
	IRequestHandler::RequestInfo requestInfo;
	int msgSize = 0;

	requestInfo.id = Helper::getIntPartFromSocket(client_socket, 1);
	msgSize = Helper::getIntPartFromSocket(client_socket, 4);
	requestInfo.buffer = Helper::getPartFromSocket(client_socket, msgSize);
	
	return requestInfo;
}