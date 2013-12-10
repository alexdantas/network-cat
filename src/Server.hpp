#ifndef SERVER_H_DEFINED
#define SERVER_H_DEFINED

#include <string>

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
	int sckt; ///< Raw socket.
};

#endif //SERVER_H_DEFINED

