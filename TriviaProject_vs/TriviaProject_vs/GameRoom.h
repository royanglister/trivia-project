#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"

class LoggedUser;

class GameRoom
{
public:
	typedef struct RoomData
	{
		unsigned int id;
		std::string name;
		unsigned int numOfPlayers;
		unsigned int numOfQuestionsInGame;
		unsigned int timePerQuestion; // In sec.
		unsigned int isActive;
	}RoomData;

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData();

	GameRoom();
	GameRoom(RoomData metadata, LoggedUser user);

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
