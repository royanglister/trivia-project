#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "SqliteDataBase.h"

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;

public:
	LoginManager(IDatabase* database);
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
};