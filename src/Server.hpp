#ifndef SERVER_H_DEFINED
#define SERVER_H_DEFINED

#include <string>
#include "Network.hpp"

/// Server that receives indefinite data from clients.
///
class Server
{
public:
	/// Creates a server on `port`, hell yeah.
	Server(int port);

	/// Gets a string from any remote client.
	/// It could have any size, but generally it would be
	/// less than 512 bytes.
	std::string receive();

private:
	int port; ///< Port on which the server operates.

	/// Communication end-point.
	/// Where the information will be received.
	UDPServer* socket;
};

#endif //SERVER_H_DEFINED
