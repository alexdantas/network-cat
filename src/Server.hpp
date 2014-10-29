#ifndef SERVER_H_DEFINED
#define SERVER_H_DEFINED

#include <string>
#include "Network.hpp"

/// Maximum size (in bytes) that we get at once from a remote
/// client.
#define SERVER_BUFFER_SIZE 666

/// Server that receives indefinite data from clients.
///
class Server
{
public:
	/// Creates a server on `port`, hell yeah.
	Server(int port);

	/// Receives a string from any remote client.
	std::string get();

	/// Runs an infinite loop, receiving messages from hosts.
	void run();

private:
	int port; ///< Port on which the server operates.

	/// Communication end-point.
	/// Where the information will be received.
	UDPSocket* socket;
};

#endif //SERVER_H_DEFINED
