#ifndef CLIENT_H_DEFINED
#define CLIENT_H_DEFINED

#include <string>
#include "Network.hpp"

/// Implements the client that will send data to a server.
class Client
{
public:
	/// Creates a client with a socket to #server_hostname and #port.
	///
	/// It will translate #server_hostname to an ip and
	/// send messages to "server_ip:port".
	/// For instance, "localhost" will get translated to "127.0.0.1"..
	Client(std::string server_hostname, int port);

	/// Sends `msg` to a server specified when created.
	void send(std::string msg);

	std::string get();

	/// Runs an infinite loop, receiving input and sending
	/// it with `Client::send`.
	void run();

private:
	/// Original server hostname sent to the Client constructor.
	/// It could be an IP address, if user provided one.
	std::string server_hostname;

	/// Translated IP address from #server_hostname.
	/// For example, "localhost" to "127.0.0.1".
	std::string server_ip;

	/// Port to connect to the server.
	int server_port;

	UDPClient* socket;
};

#endif //CLIENT_H_DEFINED
