#include "Client.hpp"
#include "Log.hpp"
#include "Network.hpp"

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

Client::Client(std::string server_hostname, int port):
	server_hostname(server_hostname),
	server_port(port),
	socket(NULL)
{
	this->socket = new UDPClient();
	Log::debug("Socket created");

	this->server_ip = Network::hostToIp(server_hostname);
	Log::verbose("Client created on " + this->server_hostname +
	             " (" + this->server_ip + ")" +
	             " : " + Log::intToString(port));
}
void Client::send(std::string msg)
{
	this->socket->send(msg, this->server_ip, this->server_port);
	Log::debug("Sent message");
}
