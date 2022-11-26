#pragma once
#include "IDatabase.h"
#include "RoomManager.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"


class LoginRequestHandler;
class MenuRequestHandler;
class LoginManager;

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;

public:
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);
	StatisticsManager& getStatisticsManager();
};

