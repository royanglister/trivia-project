#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username)
{
	m_username = username;
}

std::string LoggedUser::getUsername()
{
	return m_username;
}

bool LoggedUser::getIsInRoom()
{
	return isInRoom;
}

void LoggedUser::setIsInRoom(bool newStatus)
{
	isInRoom = newStatus;
}