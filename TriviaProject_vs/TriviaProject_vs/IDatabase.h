#pragma once

#include <iostream>

class IDatabase
{
public:
	virtual void open() = 0;
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string mail) = 0;
};

