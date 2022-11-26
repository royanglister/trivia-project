#include "SqliteDataBase.h"

int callback(void* data, int columnsCount, char** columnValves, char** columnNames);

void SqliteDataBase::SQLRequest(const char* sql)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sql, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK) { throw std::exception(errMessage); }
}

void SqliteDataBase::SQLRequest(const char* sql, Records& records)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sql, callback, &records, &errMessage);
	if (res != SQLITE_OK) { throw std::exception(errMessage); }
}

SqliteDataBase::SqliteDataBase()
{
	open();
}

void SqliteDataBase::open()
{
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	char* sql = nullptr, * errMessage = nullptr;

	if (res != SQLITE_OK)
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return;
	}
	if (doesFileExist == -1)
	{
		std::cout << "Creating database on " << dbFileName << std::endl;

		SQLRequest(	"CREATE TABLE Users ("		\
					"id INTEGER PRIMARY KEY AUTOINCREMENT,"\
					"username TEXT NOT NULL,"\
					"password TEXT NOT NULL,"\
					"mail TEXT NOT NULL);");
	}
	std::cout << dbFileName << " is opened" << std::endl;
}

void SqliteDataBase::close()
{
	sqlite3_close(db);
	db = nullptr;
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	Records records;
	std::string sql = "SELECT COUNT(*) FROM Users WHERE username = '" + username + "';";
	SQLRequest(sql.c_str(), records);
	return std::stoi(records.front().front());
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	Records records;
	std::string sql = "SELECT COUNT(*) FROM Users WHERE username = '" + username + "' AND password = '" + password + "';";
	SQLRequest(sql.c_str(), records);
	return std::stoi(records.front().front());
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string mail)
{
	std::string sql = "INSERT INTO Users (username, password, mail) Values ('" + username + "', '" + password + "', '" + mail + "');";
	SQLRequest(sql.c_str());
}

int callback(void* data, int columnsCount, char** columnValves, char** columnNames)
{
	Records* records = static_cast<Records*>(data);
	try { records->emplace_back(columnValves, columnValves + columnsCount); }	// try & catch?
	catch (...) {}
	return 0;
}