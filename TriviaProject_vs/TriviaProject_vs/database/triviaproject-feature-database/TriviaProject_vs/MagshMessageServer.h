#pragma once

#include "MagshChat.h"
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include "RecvMessage.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include <map>

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
	void handleNewClient();
	void clientHandler(SOCKET client_socket);
		
	SOCKET _socket;
	MagshChat _doc;

	// Queue for all clients. This way we will know who's the current writer.
	// SOCKET: client socket
	// string: userName
	std::map<SOCKET, LoginRequestHandler> _clients;

	// Queue for messages - Will hold the mssage code and the file data. To add messages use std::ref<const ClientSocket>
	// SOCKET: client socket
	// string: message
	std::queue<RecvMessage*> _messageHandler;

	std::mutex _mtxReceivedMessages;
	std::condition_variable _msgQueueCondition;
};

