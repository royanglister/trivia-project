#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() : m_loginManager(m_database)
{
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_database(database), m_loginManager(database)
{
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return (new LoginRequestHandler(m_loginManager, *this));
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return m_statisticsManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user)
{
	return (new MenuRequestHandler(user, m_roomManager, *this, m_statisticsManager));
}