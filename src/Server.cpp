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

	// Show our IP address to the user
	// WARNING: ugly as hell
	Log::verbose("Tell clients your IP");
	Log::verbose("Interface name/IP address");

	struct ifaddrs* raw_interfaces = NULL;
	struct ifaddrs* curr    = NULL;

	getifaddrs(&raw_interfaces);

	for (curr = raw_interfaces;
	     curr != NULL;
	     curr = curr->ifa_next)
	{
		// Is it a valid IPv4 Address?
		if (curr->ifa_addr->sa_family == AF_INET)
		{
			// Pointer to raw address
			void* tmp = &((struct sockaddr_in*)curr->ifa_addr)->sin_addr;

			char buffer[20];
			inet_ntop(AF_INET, tmp, buffer, 20);

			Log::verbose(std::string(curr->ifa_name) +
			             std::string("/") +
			             std::string(buffer));
		}
	}

	if (raw_interfaces != NULL)
		freeifaddrs(raw_interfaces);

	Log::verbose("Server created at port " +
	             Log::intToString(port));
}
void Server::run()
{
	// Hell yeah main loop
	while (true)
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

		std::string received(buffer);

		Log::verbose("Received " +
		             Log::intToString(received.length()) +
		             " bytes");

		Log::log(received);
	}
}
