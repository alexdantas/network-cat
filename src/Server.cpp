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
	this->socket = new UDPSocket();
	Log::debug("Socket created");

	this->socket->setReusable();
	Log::debug("Socket set as reusable");

	this->socket->bindTo(port);
	Log::debug("Socket bound");

	Log::verbose("Server created at port " + Log::intToString(port));
}
std::string Server::receive()
{
	// will hold address of received message
	struct sockaddr_in received_addr;
	memset(&received_addr, '\0', sizeof(received_addr));
	socklen_t addr_length = sizeof(received_addr);

	char buffer[SERVER_BUFFER_SIZE];
	memset(&buffer, '\0', SERVER_BUFFER_SIZE);

	int bytes_received = recvfrom(this->socket->raw_socket,
								buffer,
								SERVER_BUFFER_SIZE,
								0, // flags
								(struct sockaddr*) &received_addr,
								&addr_length);
	if (bytes_received < 0)
		throw std::string(strerror(errno));

	return std::string(buffer);
}
void Server::run()
{
	// Hell yeah main loop
	while (true)
	{
		std::string received = this->receive();
		Log::verbose("Received " +
		             Log::intToString(received.length()) +
		             " bytes");

		Log::log(received);
	}
}
