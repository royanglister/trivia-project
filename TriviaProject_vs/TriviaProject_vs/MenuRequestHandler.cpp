#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser& loggedUser, RoomManager& roomManager, RequestHandlerFactory& reqHandlerFactory, StatisticsManager& statsManager) : m_user(loggedUser), m_roomManager(roomManager), m_handleFactory(reqHandlerFactory), m_statisticsManager(statsManager)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo rI)
{
	return (rI.id == CREATE_ROOM_REQUEST_MESSAGE_CODE || rI.id == JOIN_ROOM_REQUEST_MESSAGE_CODE || rI.id == LOGOUT_REQUEST_MESSAGE_CODE || rI.id == GET_ROOMS_REQUEST_MESSAGE_CODE);
}

IRequestHandler::RequestResult MenuRequestHandler::handleRequest(RequestInfo rI)
{
	RequestResult rR;
	JsonResponsePacketSeriallizer::ErrorResponse eR;

	if (!isRequestRelevant(rI))
	{
		rR.newHandler = this;
		eR.message = "Error. Irrelevant request";
		rR.response = JsonResponsePacketSeriallizer::serializeErrorResponse(eR);
		return rR;
	}

	if (rI.id == CREATE_ROOM_REQUEST_MESSAGE_CODE)
	{
		rR = createRoom(rI);
	}
	
	else if (rI.id == JOIN_ROOM_REQUEST_MESSAGE_CODE)
	{
		rR = joinRoom(rI);
	}

	else if (rI.id == LOGOUT_REQUEST_MESSAGE_CODE)
	{
		rR = signout(rI);
	}

	else if (rI.id == GET_ROOMS_REQUEST_MESSAGE_CODE)
	{
		rR = getRooms(rI);
	}

	return rR;
}

IRequestHandler::RequestResult MenuRequestHandler::signout(RequestInfo rI)
{
	RequestResult rR;
	JsonResponsePacketSeriallizer::LogoutResponse lr;

	lr.status = 1;
	rR.response = JsonResponsePacketSeriallizer::serializeLogoutResponse(lr);
	rR.newHandler = m_handleFactory.createLoginRequestHandler();
	m_handleFactory.getLoginManager().logout(m_user.getUsername());

	return rR;
}


IRequestHandler::RequestResult MenuRequestHandler::joinRoom(RequestInfo rI)
{
	RequestResult rR;
	JsonResponsePacketSeriallizer::JoinRoomResponse joinRoomResponse;
	JsonRequestPacketDeserializer::JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(rI.buffer);
	std::string usernamesString = "";

	try
	{
		m_roomManager.getRoom(joinRoomRequest.roomName).addUser(m_user);
		joinRoomResponse.status = 1;

		for (int i = 0; i < m_roomManager.getRoom(joinRoomRequest.roomName).getAllUsers().size(); i++)
		{
			usernamesString += m_roomManager.getRoom(joinRoomRequest.roomName).getAllUsers()[i] + ",";
		}
		
		usernamesString.pop_back(); // Removing last comma.
		joinRoomResponse.usernamesOfRoom = usernamesString;
		rR.response = JsonResponsePacketSeriallizer::serializeJoinRoomResponse(joinRoomResponse);
	}

	catch (std::string error)
	{
		joinRoomResponse.status = 0;
	}

	return rR;
}


IRequestHandler::RequestResult MenuRequestHandler::createRoom(RequestInfo rI)
{
	RequestResult rR;
	JsonResponsePacketSeriallizer::CreateRoomResponse crr;
	GameRoom::RoomData roomData;

	crr.status = 1;
	rR.response = JsonResponsePacketSeriallizer::serializeCreateRoomResponse(crr);
	roomData.name = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(rI.buffer).roomName;
	roomData.numOfPlayers = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(rI.buffer).maxUsers;
	roomData.numOfQuestionsInGame = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(rI.buffer).questionCount;
	roomData.timePerQuestion = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(rI.buffer).answerTimeout;
	roomData.isActive = true;

	m_roomManager.createRoom(m_user, roomData);
	rR.newHandler = this;
	return rR;
}

IRequestHandler::RequestResult MenuRequestHandler::getRooms(RequestInfo rI)
{
	RequestResult rR;
	JsonResponsePacketSeriallizer::GetRoomsResponse grr;

	grr.status = 1;

	for (int i = 0; i < m_roomManager.getRoomsData().size(); i++)
	{
		grr.roomNames += m_roomManager.getRoomsData()[i].name + ",";
	}

	if (m_roomManager.getRoomsData().size() != 0)
	{
		grr.roomNames.pop_back(); // Removing last comma.
	}

	rR.response = JsonResponsePacketSeriallizer::serializeGetRoomsResponse(grr);
	rR.newHandler = this;

	return rR;
}