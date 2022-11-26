#pragma once

#include "LoginManager.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSeriallizer.h"
#include <vector>

#define LOGIN_REQUEST_MESSAGE_CODE 2
#define SIGNUP_REQUEST_MESSAGE_CODE 3

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler	(LoginManager& loginManager, RequestHandlerFactory& handleFactory);
	virtual bool isRequestRelevant(RequestInfo rI);
	virtual RequestResult handleRequest(RequestInfo rI);

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handleFactory;

	RequestResult login(RequestInfo rI);
	RequestResult signup(RequestInfo rI);
};