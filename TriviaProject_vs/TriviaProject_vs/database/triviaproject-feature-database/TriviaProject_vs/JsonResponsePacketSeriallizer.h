#pragma once

#include <iostream>
#include <string>
#include <vector>

class JsonResponsePacketSeriallizer
{
public:

	typedef struct LoginResponse
	{
		std::string username;
		std::string password;
	} LoginResponse;

	typedef struct SignupResponse
	{
		std::string username;
		std::string password;
		std::string mail;
	} SignupResponse;

	typedef struct ErrorResponse
	{
		std::string message;
	} ErrorResponse;

	static std::vector<unsigned char> SerializeLoginResponse(LoginResponse lr);
	static std::vector<unsigned char> SerializeSignupResponse(SignupResponse sr);
	static std::vector<unsigned char> SerializeErrorResponse(ErrorResponse er);
};

