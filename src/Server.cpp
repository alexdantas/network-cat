#include "Server.hpp"
#include "Log.hpp"

Server::Server(int port):
	port(port)
{
	this->socket = new UDPServer();
	Log::debug("Socket created");

	this->socket->setReusable();
	Log::debug("Socket set as reusable");

	this->socket->bindTo(port);
	Log::debug("Socket bound");

	Log::verbose("Server created at port " + Log::intToString(port));
}

std::string Server::receive()
{
	return this->socket->receive();
}
