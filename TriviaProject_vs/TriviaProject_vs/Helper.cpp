#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;

// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);

	if (bytesNum == 1)
	{
		return (int)s[0];
	}

	return atoi(s);
}

// recieve data from socket according byteSize
// returns the data as string
string Helper::getStringPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	string res(s);
	return res;
}

// return string after padding zeros if necessary
string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

// recieve data from socket according byteSize.
std::vector<BYTE> Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	std::vector<BYTE> bufferVector;
	char* buffer = getPartFromSocket(sc, bytesNum, 0);
	std::string bufferInString = buffer;
	
	for (int i = 0; i < bufferInString.length(); i++)
	{
		bufferVector.push_back(bufferInString[i]);
	}

	return bufferVector;
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

// send data to socket
void Helper::sendData(SOCKET sc, std::vector<BYTE> message)
{
	std::string msg = "";

	for (byte ch : message)
	{
		msg += ch;
	}

	if (send(sc, msg.c_str(), message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}