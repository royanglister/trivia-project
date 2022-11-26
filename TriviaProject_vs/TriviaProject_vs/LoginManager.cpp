#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database)
{
	m_database = database;
}

/*
This function gets the user's data and adds him to the DB.
Input: A username, a password and an email.
Output: None.
*/
void LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (m_database->doesUserExist(username))
	{
		throw ("Username is already taken");
	}

	else
	{
		m_database->addNewUser(username, password, email);
	}
}

/*
This function performs a login of an existing user.
Input: A username and a password.
Output: None.
*/
void LoginManager::login(std::string username, std::string password)
{
	if (!m_database->doesUserExist(username) || (m_database->doesUserExist(username) && !m_database->doesPasswordMatch(username, password)))
	{
		throw ("Username or password are incorrect");
	}

	else
	{
		LoggedUser user(username);
		m_loggedUsers.push_back(user);
	}
}

/*
This function performs a logout of an existing user.
Input: A username.
Output: None.
*/
void LoginManager::logout(std::string username)
{
	std::vector<LoggedUser>::iterator it;
	
	// Going through all the logged in users.
	for (it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it)
	{
		if (it->getUsername() == username) // Searching for the username.
		{
			m_loggedUsers.erase(it);
			break;
		}
	}
}