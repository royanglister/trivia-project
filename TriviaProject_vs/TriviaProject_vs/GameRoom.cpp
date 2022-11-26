#include "GameRoom.h"

/*
This function creates a Room.
Input: The room's metadata and the room's creator.
Output: None.
*/
GameRoom::GameRoom(RoomData metadata, LoggedUser user)
{
	m_metadata = metadata;
	addUser(user);
}

GameRoom::GameRoom()
{
}

/*
This function adds a user to the game room.
Input: A user to add.
Output: None.
*/
void GameRoom::addUser(LoggedUser user)
{
	if (user.getIsInRoom())
	{
		throw ("Error. User is already in a room");
	}

	user.setIsInRoom(true);
	m_users.push_back(user);
}

/*
This function removes a user from the game room.
Input: A user to remove.
Output: None.
*/
void GameRoom::removeUser(LoggedUser user)
{
	std::vector<LoggedUser>::iterator it;

	for (it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (user.getUsername() == it->getUsername())
		{
			user.setIsInRoom(false);
			m_users.erase(it);
		}
	}
}

/*
This function returns a vector that contains all the usernames in the game room.
Input: None.
Output: The vector with all the usernames in the game room.
*/
std::vector<std::string> GameRoom::getAllUsers()
{
	std::vector<std::string> usernames;
	std::vector<LoggedUser>::iterator it;

	// Creating a vector of usernames.
	for (it = m_users.begin(); it != m_users.end(); ++it)
	{
		usernames.push_back(it->getUsername());
	}

	return usernames;
}

/*
This function returns the room's data.
Input: None.
Output: The room's data.
*/
GameRoom::RoomData GameRoom::getRoomData()
{
	return m_metadata;
}
