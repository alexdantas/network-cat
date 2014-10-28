#include "Client.hpp"
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

Client::Client(std::string ip, int port):
	port(port)
{
	// Create IP/UDP socket
	int ret = socket(AF_INET, SOCK_DGRAM, 0);
	if (ret < 0)
		throw std::string(strerror(errno)); // show last error

	this->sckt = ret;
	Log::debug("Socket created");

	this->host = hostToIp(ip);
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

	int ret = sendto(this->sckt,
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

std::string Client::hostToIp(std::string hostname)
{
	struct hostent* my_host;
	struct in_addr* my_host_address;

	my_host = gethostbyname(hostname.c_str());
	if (my_host == NULL)
		return "";

	my_host_address = (struct in_addr*)my_host->h_addr_list[0];

	return std::string(inet_ntoa(*my_host_address));
}
