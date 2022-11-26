#pragma once

#include "sqlite3.h"
#include "IDatabase.h"
#include <io.h>
#include <vector>
#include <string>
#include <list>
#include <map>

typedef std::list<std::list<std::string>> Records;

class SqliteDataBase : public IDatabase
{
private:
	sqlite3* db;
	std::string dbFileName = "MyDB.sqlite";

	void SQLRequest(const char* sql);
	void SQLRequest(const char* sql, Records& records);

public:
	SqliteDataBase();
	virtual ~SqliteDataBase() = default;

	virtual void open();
	void close();

	bool doesUserExist(std::string username);
	bool doesPasswordMatch(std::string username, std::string password);
	void addNewUser(std::string username, std::string password, std::string mail);
};

