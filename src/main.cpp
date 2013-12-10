/// `network-cat` main file
///
/// Start up the awesomeness!

#include <iostream>
#include <string>
#include <cstdlib>

#include "Arguments.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Log.hpp"

int main(int argc, char* argv[])
{
	try
	{
		Arguments::handle(argc, argv);
		Log::error(Log::intToString(Arguments::port));

		if (Arguments::debug)   Log::debugMode(true);
		if (Arguments::verbose) Log::verboseMode(true);
		Log::colors(false);

		if (Arguments::client)
		{
			Client client(Arguments::ip, Arguments::port);
			client.run();
		}
		else if (Arguments::server)
		{
			Server server(Arguments::port);
			server.run();
		}
		else
			throw std::string("Wtf");
	}
	catch (std::string s)
	{
		Log::error(s);
		exit(666);
	}
	return 0;
}

