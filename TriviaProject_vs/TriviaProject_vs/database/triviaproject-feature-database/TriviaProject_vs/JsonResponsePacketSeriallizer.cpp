#include "JsonResponsePacketSeriallizer.h"

/*
This function serializes the login response.
Input: A login response object.
Output: An unsigned char vector that contains the serialized response.
*/
std::vector<unsigned char> JsonResponsePacketSeriallizer::SerializeLoginResponse(LoginResponse lr)
{
	std::vector<unsigned char> serializedResponse;

	std::string sr("{\"username\":" + lr.username + ",\"password\":" + lr.password + "}");

	serializedResponse.push_back((unsigned char)(1));
	serializedResponse.push_back((unsigned char)sr.length() >> 24);
	serializedResponse.push_back((unsigned char)((sr.length() >> 16) & 255));
	serializedResponse.push_back((unsigned char)((sr.length() >> 8) & 255));
	serializedResponse.push_back((unsigned char)(sr.length()& 255));
	std::copy(sr.begin(), sr.end(), std::back_inserter(serializedResponse));
	return serializedResponse;
}

/*
This function serializes the sign up response.
Input: A signup response object.
Output: An unsigned char vector that contains the serialized response.
*/
std::vector<unsigned char> JsonResponsePacketSeriallizer::SerializeSignupResponse(SignupResponse lr)
{
	std::vector<unsigned char> serializedResponse;

	std::string sr("{\"username\":" + lr.username + ",\"password\":" + lr.password + ",\"mail\":" + lr.mail + "}");

	serializedResponse.push_back((unsigned char)(2));
	serializedResponse.push_back((unsigned char)sr.length() >> 24);
	serializedResponse.push_back((unsigned char)((sr.length() >> 16) & 255));
	serializedResponse.push_back((unsigned char)((sr.length() >> 8) & 255));
	serializedResponse.push_back((unsigned char)(sr.length() & 255));
	std::copy(sr.begin(), sr.end(), std::back_inserter(serializedResponse));
	return serializedResponse;
}

/*
This function serializes the error response.
Input: An error response object.
Output: An unsigned char vector that contains the serialized response.
*/
std::vector<unsigned char> JsonResponsePacketSeriallizer::SerializeErrorResponse(ErrorResponse er)
{
	return std::vector<unsigned char>(er.message.begin(), er.message.end());
}