#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handleFactory):
	m_loginManager(loginManager), m_handleFactory(handleFactory)
{
}

IRequestHandler::RequestResult LoginRequestHandler::login(RequestInfo rI)
{
	IRequestHandler::RequestResult rR;
	JsonResponsePacketSeriallizer::LoginResponse lR;
	JsonRequestPacketDeserializer::LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(rI.buffer);

	try 
	{
		m_loginManager.login(request.username, request.password);
		LoggedUser user(request.username);
		lR.status = 1;

		rR.newHandler = m_handleFactory.createMenuRequestHandler(user);
	}

	catch (...)
	{
		lR.status = 0;
		rR.newHandler = this;
	}

	rR.response = JsonResponsePacketSeriallizer::serializeLoginResponse(lR);

	return rR;
}

IRequestHandler::RequestResult LoginRequestHandler::signup(RequestInfo rI)
{
	IRequestHandler::RequestResult rR;
	JsonResponsePacketSeriallizer::SignupResponse sR;
	JsonRequestPacketDeserializer::SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(rI.buffer);

	try
	{
		m_loginManager.signup(request.username, request.password, request.mail);
		sR.status = 1;
	}

	catch (...)
	{
		sR.status = 0;
	}

	rR.newHandler = this;
	rR.response = JsonResponsePacketSeriallizer::serializeSignupResponse(sR);

	return rR;
}

IRequestHandler::RequestResult LoginRequestHandler::handleRequest(RequestInfo rI)
{
	IRequestHandler::RequestResult rR;
	JsonResponsePacketSeriallizer::ErrorResponse eR;

	if (!isRequestRelevant(rI))
	{
		rR.newHandler = this;
		eR.message = "Error. Irrelevant request";
		rR.response = JsonResponsePacketSeriallizer::serializeErrorResponse(eR);
		return rR;
	}

	if (rI.id == LOGIN_REQUEST_MESSAGE_CODE)
	{
		rR = login(rI);
	}

	else
	{
		rR = signup(rI);
	}

	return rR;
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo rI)
{
	return (rI.id == LOGIN_REQUEST_MESSAGE_CODE|| rI.id == SIGNUP_REQUEST_MESSAGE_CODE);
}