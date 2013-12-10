#ifndef CLIENT_H_DEFINED
#define CLIENT_H_DEFINED

#include <string>

/// Implements the client that will send data to a server.
class Client
{
public:
	/// Creates a client that will send to `ip`/`port`.
	Client(std::string ip, int port);

	/// Sends `msg` to a server specified when created.
	void send(std::string msg);

	std::string get();

	/// Runs an infinite loop, receiving input and sending
	/// it with `Client::send`.
	void run();

private:
	std::string hostToIp(std::string hostname);

	int          port;
	int          sckt;
	std::string  host;
};

#endif //CLIENT_H_DEFINED

