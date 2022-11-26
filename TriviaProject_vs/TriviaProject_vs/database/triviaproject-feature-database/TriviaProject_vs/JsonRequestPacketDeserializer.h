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

	typedef struct RequestInfo
	{
		int id;
		std::time_t receivalTime = std::time(nullptr);
		std::vector<unsigned char> buffer;
	} RequestInfo;

	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> lr);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> sr);
	
private:
	static std::vector<RequestInfo> requestLog;
};