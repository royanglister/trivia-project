#pragma once
#include <vector>
#include <ctime>

class IRequestHandler
{
public:
	typedef struct RequestInfo
	{
		int id;
		std::time_t receivalTime = std::time(0);
		std::vector<unsigned char> buffer;
	}RequestInfo;
	
	typedef struct RequestResult
	{
		std::vector<unsigned char> response;
		IRequestHandler* newHandler;
	}RequestResult;

	virtual bool isRequestRelevant(RequestInfo rI) = 0;
	virtual RequestResult handleRequest(RequestInfo rI) = 0;
};

