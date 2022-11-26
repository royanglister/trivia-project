#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include <ctime>

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	typedef struct LoginRequest
	{
		std::string username;
		std::string password;
	} LoginRequest;

	typedef struct SignupRequest
	{
		std::string username;
		std::string password;
		std::string mail;
	} SignupRequest;

	typedef struct GetPlayersInRoomRequest
	{
		unsigned int roomId;
	} GetPlayersInRoomRequest;

	typedef struct JoinRoomRequest
	{
		std::string roomName;
	} JoinRoomRequest;

	typedef struct CreateRoomRequest
	{
		std::string roomName;
		unsigned int maxUsers;
		unsigned int questionCount;
		unsigned int answerTimeout;
	} CreateRoomRequest;

	typedef struct RequestInfo
	{
		int id;
		std::time_t receivalTime = std::time(nullptr);
		std::vector<unsigned char> buffer;
	} RequestInfo;

	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> request);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> request);

	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::vector<unsigned char> request);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> request);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> request);

private:
	static std::vector<RequestInfo> requestLog;
};
