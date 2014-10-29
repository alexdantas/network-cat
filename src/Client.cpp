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
	this->socket = new UDPSocket();
	Log::debug("Socket created");

	this->server_ip = Network::hostToIp(server_hostname);
	Log::verbose("Client created on " + this->server_hostname +
	             " (" + this->server_ip + ")" +
	             " : " + Log::intToString(port));
}
void Client::send(std::string msg)
{
	// Socket address to the server.
	// This is the raw connection we actually make to the server.
	// We send raw data through this.
	struct sockaddr_in server_address;
	memset(&server_address, '\0', sizeof(server_address));

	// It's an IP connection on a specific port
	server_address.sin_family = AF_INET;
	server_address.sin_port   = htons(this->server_port);

	// To send stuff to the server we need to know about it.
	// This is the information we get from the server
	// (IP address, along with other useless stuff)
	struct hostent* server_host_entity;

	// Retrieving it...
	server_host_entity = gethostbyname(this->server_ip.c_str());
	if (server_host_entity == NULL)
		throw std::string(strerror(errno));

	// Storing the server information on that connection thingy
	memcpy((void*) &server_address.sin_addr,
	       server_host_entity->h_addr_list[0],
	       server_host_entity->h_length);

	// Finally actually sending information to the server!
	int ret = sendto(this->socket->raw_socket,
	                 msg.c_str(),
	                 msg.length(),
	                 0, // flags
	                 (struct sockaddr*) &server_address,
	                 sizeof(server_address));

	if (ret < 0)
		throw std::string(strerror(errno));

	Log::debug("Sent message");
}
void Client::run()
{
	Log::verbose("Connected!");

    while (true)
    {
	    std::string input;

	    if (!(std::getline(std::cin, input)))
		    break;

	    send(input);
    }
}
