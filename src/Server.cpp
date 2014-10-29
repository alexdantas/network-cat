#include "Server.hpp"
#include "Log.hpp"

// include HELL for SOCKETS
#include <errno.h>
#include <stdint.h>     // absolute int types
#include <string.h>     // memset()
#include <fcntl.h>      // fcntl()
#include <stdlib.h>
#include <sys/socket.h> // socket() bind() inet_ntoa
#include <sys/types.h>  // inet_ntoa
#include <netinet/in.h> // inet_ntoa
#include <arpa/inet.h>  // inet_ntoa
#include <netdb.h>      // gethostbyname()
#include <sys/types.h>
#include <ifaddrs.h>

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
