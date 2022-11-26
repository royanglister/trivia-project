#include "JsonRequestPacketDeserializer.h"

std::vector<JsonRequestPacketDeserializer::RequestInfo> JsonRequestPacketDeserializer::requestLog;

/*
This function deserializes the login request of the client.
Input: A login request object.
Output: A buffer that contains the deserialized message.
*/
JsonRequestPacketDeserializer::LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> request)
{
	LoginRequest lr;
	json j = json::parse(request);
	requestLog.push_back(RequestInfo{ request[0] , std::time(nullptr), request });
	
	lr.username = j.at("username");
	lr.password = j.at("password");
	return lr;
}

/*
This function deserializes the  request of the client.
Input: A login request object.
Output: A buffer that contains the deserialized message.
*/
JsonRequestPacketDeserializer::SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> request)
{
	SignupRequest sr;
	json j = json::parse(request);
	requestLog.push_back(RequestInfo{ request[0] , std::time(nullptr), request });

	sr.username = j.at("username");
	sr.password = j.at("password");
	sr.mail = j.at("email");
	return sr;
}

/*
JsonRequestPacketDeserializer::GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector<unsigned char> request)
{
	requestLog.push_back(RequestInfo({ request[0] , std::time(nullptr), request }));
	return GetPlayersInRoomRequest({ json(std::string(request.begin() + 5, request.end()))["roomId"].get<unsigned int>() });
}
*/

JsonRequestPacketDeserializer::JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> request)
{
	JoinRoomRequest jrr;
	json j = json::parse(request);
	requestLog.push_back(RequestInfo{ request[0] , std::time(nullptr), request });

	jrr.roomName = j.at("roomName");
	return jrr;
}


JsonRequestPacketDeserializer::CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> request)
{
	CreateRoomRequest crr;
	json j = json::parse(request);
	requestLog.push_back(RequestInfo{ request[0] , std::time(nullptr), request });

	crr.roomName = j.at("roomName");
	crr.maxUsers = j.at("numOfPlayers");
	crr.questionCount = j.at("numOfQuestionsInGame");
	crr.answerTimeout = j.at("timePerQuestion");
	return crr;
}