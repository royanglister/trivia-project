#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

#define GET_ROOMS_REQUEST_MESSAGE_CODE 6
#define CREATE_ROOM_REQUEST_MESSAGE_CODE 7
#define JOIN_ROOM_REQUEST_MESSAGE_CODE 8
#define LOGOUT_REQUEST_MESSAGE_CODE 9

class RequestHandlerFactory;
class StatisticsManager;

class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handleFactory;
	StatisticsManager& m_statisticsManager;

	RequestResult signout(RequestInfo rI);
	RequestResult getRooms(RequestInfo rI);
	RequestResult getPlayersInRoom(RequestInfo rI);
	RequestResult getPersonalStats(RequestInfo rI);
	RequestResult getHighScore(RequestInfo rI);
	RequestResult joinRoom(RequestInfo rI);
	RequestResult createRoom(RequestInfo rI);

public:
	MenuRequestHandler(LoggedUser& loggedUser, RoomManager& roomManager, RequestHandlerFactory& reqHandlerFactory, StatisticsManager& statsManager);
	virtual bool isRequestRelevant(RequestInfo rI);
	virtual RequestResult handleRequest(RequestInfo rI);
};