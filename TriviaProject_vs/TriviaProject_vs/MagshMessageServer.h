#pragma once

#include <WinSock2.h>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include <map>
#include "Helper.h"

#define SIZE 100
#define FIVE 5

// Q: why do we need this class ?
// A: this is the main class which holds all the resources, accept new clients and handle them.
class MagshMessageServer
{
public:
	MagshMessageServer();
	~MagshMessageServer();
	void serve();

private:
	void bindAndListen();
	void acceptClient();
	void clientHandler(SOCKET client_socket);

	IRequestHandler::RequestInfo getRequestInfo(const SOCKET client_socket);

	SOCKET _socket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory m_factory;
	IDatabase* m_database;
};