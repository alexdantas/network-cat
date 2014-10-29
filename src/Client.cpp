#include "Client.hpp"
#include "Log.hpp"
#include "Network.hpp"

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
