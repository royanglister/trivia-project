#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

class JsonResponsePacketSeriallizer
{
public:
	typedef struct LoginResponse
	{
		unsigned int status;
	}LoginResponse;
	
	typedef struct LogoutResponse
	{
		unsigned int status;
	}LogoutResponse;

	typedef struct SignupResponse
	{
		unsigned int status;
	}SignupResponse;

	typedef struct ErrorResponse
	{
		std::string message;
	}ErrorResponse;
	
	typedef struct CreateRoomResponse
	{
		unsigned int status;
	}CreateRoomResponse;
	
	typedef struct JoinRoomResponse
	{
		unsigned int status;
		std::string usernamesOfRoom;
	}JoinRoomResponse;

	typedef struct GetRoomsResponse
	{
		unsigned int status;
		std::string roomNames;
	}GetRoomsResponse;

	static std::vector<unsigned char> serializeLoginResponse(LoginResponse lr);
	static std::vector<unsigned char> serializeLogoutResponse(LogoutResponse lr);
	static std::vector<unsigned char> serializeSignupResponse(SignupResponse sr);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse er);
	static std::vector<unsigned char> serializeCreateRoomResponse(CreateRoomResponse crr);
	static std::vector<unsigned char> serializeJoinRoomResponse(JoinRoomResponse jrr);
	static std::vector<unsigned char> serializeGetRoomsResponse(GetRoomsResponse grr);
};

