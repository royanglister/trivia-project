#include "JsonResponsePacketSeriallizer.h"

void pushInt(std::vector<unsigned char>& pushInto, int num);

/*
This function serializes the login response.
Input: A login response object.
Output: An unsigned char vector that contains the serialized response.
*/
std::vector<unsigned char> JsonResponsePacketSeriallizer::serializeLoginResponse(LoginResponse lr)
{
	std::vector<unsigned char> serializedResponse;

	std::string statusMsg("{status:" + std::to_string(lr.status) + "}");

	serializedResponse.push_back((unsigned char)(1));
	pushInt(serializedResponse, statusMsg.length());
	std::copy(statusMsg.begin(), statusMsg.end(), std::back_inserter(serializedResponse));
	return serializedResponse;
}

std::vector<unsigned char> JsonResponsePacketSeriallizer::serializeLogoutResponse(LogoutResponse lr)
{
	std::vector<unsigned char> serializedResponse;

	std::string statusMsg("{status:" + std::to_string(lr.status) + "}");

	serializedResponse.push_back((unsigned char)(1));
	pushInt(serializedResponse, statusMsg.length());
	std::copy(statusMsg.begin(), statusMsg.end(), std::back_inserter(serializedResponse));
	return serializedResponse;
}

/*
This function serializes the sign up response.
Input: A signup response object.
Output: An unsigned char vector that contains the serialized response.
*/
std::vector<unsigned char> JsonResponsePacketSeriallizer::serializeSignupResponse(SignupResponse sr)
{
	std::vector<unsigned char> serializedResponse;

	std::string statusMsg("{status:" + std::to_string(sr.status) + "}");

	serializedResponse.push_back((unsigned char)(1));
	pushInt(serializedResponse, statusMsg.length());
	std::copy(statusMsg.begin(), statusMsg.end(), std::back_inserter(serializedResponse));
	return serializedResponse;
}

/*
This function serializes the error response.
Input: An error response object.
Output: An unsigned char vector that contains the serialized response.
*/
std::vector<unsigned char> JsonResponsePacketSeriallizer::serializeErrorResponse(ErrorResponse er)
{
	int i = 0;
	std::vector<unsigned char> serializedResponse;

	for (i = 0; i < er.message.length(); i++)
	{
		serializedResponse.push_back((unsigned char)(er.message[i]));
	}

	return serializedResponse;
}

void pushInt(std::vector<unsigned char>& pushInto, int num)
{
	pushInto.push_back((unsigned char)num >> 24);
	pushInto.push_back((unsigned char)(num >> 16) & 255);
	pushInto.push_back((unsigned char)(num >> 8) & 255);
	pushInto.push_back((unsigned char)(num & 255));
}

std::vector<unsigned char> JsonResponsePacketSeriallizer::serializeCreateRoomResponse(CreateRoomResponse crr)
{
	std::vector<unsigned char> serializedResponse;

	std::string statusMsg("{status:" + std::to_string(crr.status) + "}");
	serializedResponse.push_back((unsigned char)(1));
	pushInt(serializedResponse, statusMsg.length());
	std::copy(statusMsg.begin(), statusMsg.end(), std::back_inserter(serializedResponse));
	return serializedResponse;
}

std::vector<unsigned char> JsonResponsePacketSeriallizer::serializeJoinRoomResponse(JoinRoomResponse jrr)
{
	std::vector<unsigned char> serializedResponse;
	std::string playersInRoomNamesString = "playersInRoom:\"";
	std::string statusMsg("{status:" + std::to_string(jrr.status) + ",");

	for (int i = 0; i < jrr.usernamesOfRoom.length(); i++)
	{
		playersInRoomNamesString += jrr.usernamesOfRoom[i];
	}

	if (jrr.usernamesOfRoom.length() == 0)
	{
		playersInRoomNamesString = "playersInRoom:\"";
	}

	serializedResponse.push_back((unsigned char)(1));
	pushInt(serializedResponse, statusMsg.length() + playersInRoomNamesString.length() + 2);
	std::copy(statusMsg.begin(), statusMsg.end(), std::back_inserter(serializedResponse));

	for (int i = 0; i < playersInRoomNamesString.length(); i++)
	{
		serializedResponse.push_back(playersInRoomNamesString[i]);
	}

	serializedResponse.push_back('\"');
	serializedResponse.push_back('}'); // Closing the response message.

	return serializedResponse;
}

std::vector<unsigned char> JsonResponsePacketSeriallizer::serializeGetRoomsResponse(GetRoomsResponse grr)
{
	std::vector<unsigned char> serializedResponse;
	std::string roomNamesString = "Rooms:\"";
	std::string statusMsg("{status:" + std::to_string(grr.status) + ",");

	for (int i = 0; i < grr.roomNames.length(); i++)
	{
		roomNamesString += grr.roomNames[i];
	}

	if (grr.roomNames.length() == 0)
	{
		roomNamesString = "Rooms:\"";
	}

	serializedResponse.push_back((unsigned char)(1));
	pushInt(serializedResponse, statusMsg.length() + roomNamesString.length() + 2);
	std::copy(statusMsg.begin(), statusMsg.end(), std::back_inserter(serializedResponse));

	for (int i = 0; i < roomNamesString.length(); i++)
	{
		serializedResponse.push_back(roomNamesString[i]);
	}

	serializedResponse.push_back('\"');
	serializedResponse.push_back('}'); // Closing the response message.

	return serializedResponse;
}