#pragma once
#include <string>

class LoggedUser
{
private:
	std::string m_username;
	bool isInRoom = false;

public:
	LoggedUser(std::string username);
	std::string getUsername();

	bool getIsInRoom(); // Getter.
	void setIsInRoom (bool newStatus); // Setter.
};

