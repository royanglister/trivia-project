#pragma once
#include "GameRoom.h"
#include <map>

class RoomManager
{
public:
	void createRoom(LoggedUser user, GameRoom::RoomData roomData);
	void deleteRoom(int Id);
	//unsigned int getRoomState(int Id); // Not compatiable with this version.
	std::vector<GameRoom::RoomData> getRoomsData();
	GameRoom& getRoom(std::string roomName);

private:
	std::map<unsigned int, GameRoom> m_rooms; // The unsigned int is for the room's ID number.
	int m_roomIdGenerator = 1;
};
