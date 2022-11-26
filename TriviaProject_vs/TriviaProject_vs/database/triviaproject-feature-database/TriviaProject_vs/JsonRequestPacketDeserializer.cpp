#include "JsonRequestPacketDeserializer.h"

std::vector<JsonRequestPacketDeserializer::RequestInfo> JsonRequestPacketDeserializer::requestLog;

/*
This function deserializes the login request of the client.
Input: A login request object.
Output: A buffer that contains the deserialized message.
*/
JsonRequestPacketDeserializer::LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> lr)
{
	std::string jsonPartOfLr(lr.begin() + 5, lr.end());
	requestLog.push_back(RequestInfo{ lr[0] , std::time(nullptr), lr });
	return LoginRequest({ json(jsonPartOfLr).value("username", ""), json(jsonPartOfLr).value("password", "") });
}

/*
This function deserializes the  request of the client.
Input: A login request object.
Output: A buffer that contains the deserialized message.
*/
JsonRequestPacketDeserializer::SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> sr)
{
	std::string jsonPartOfSr(sr.begin() + 5, sr.end());
	requestLog.push_back(RequestInfo({ sr[0] , std::time(nullptr), sr }));
	return SignupRequest({ json(jsonPartOfSr).value("username", ""), json(jsonPartOfSr).value("password", ""), json(jsonPartOfSr).value("mail", "") });
}
