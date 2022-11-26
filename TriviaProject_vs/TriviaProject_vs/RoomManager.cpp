#include "RoomManager.h"

/*
This function creates a game room.
Input: An admin and the room's data.
Output: None.
*/
void RoomManager::createRoom(LoggedUser user, GameRoom::RoomData roomData)
{
	roomData.id = m_roomIdGenerator;
	m_roomIdGenerator++;

	m_rooms[roomData.id] = GameRoom(roomData, user);
}

/*
This function deletes a game room.
Input: A room's ID.
Output: None.
*/
void RoomManager::deleteRoom(int Id)
{
	m_rooms.erase(Id);
}

/*
This function returns the data of all rooms.
Input: None.
Output: A vector with all the data.
*/
std::vector<GameRoom::RoomData> RoomManager::getRoomsData()
{
	std::vector<GameRoom::RoomData> roomsData;

	for (std::pair<unsigned int, GameRoom> room : m_rooms)
	{
		roomsData.push_back(room.second.getRoomData());
	}

	return roomsData;
}

GameRoom& RoomManager::getRoom(std::string roomName)
{
	GameRoom room;
	std::map<unsigned int, GameRoom>::iterator it;

	for (it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if (it->second.getRoomData().name == roomName)
		{
			return it->second;
			break;
		}
	}

	return room;
}