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

Client::Client(std::string ip, int port):
	port(port)
{
	this->socket = new UDPSocket();
	Log::debug("Socket created");

	this->host = Network::hostToIp(ip);
	Log::verbose("Client created on " + ip +
	             " (" + this->host + ")" +
	             " : " + Log::intToString(port));
}
void Client::send(std::string msg)
{
	// ugly as fuark
	struct sockaddr_in server_addr;

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port   = htons(this->port);

	struct hostent* my_host;

	my_host = gethostbyname(this->host.c_str());
	if (my_host == NULL)
		throw std::string(strerror(errno));


	memcpy((void*) &server_addr.sin_addr,
	       my_host->h_addr_list[0],
	       my_host->h_length);

	int ret = sendto(this->socket->raw_socket,
	                 msg.c_str(),
	                 msg.length(),
	                 0, // flags
	                 (struct sockaddr*) &server_addr,
	                 sizeof(server_addr));

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
