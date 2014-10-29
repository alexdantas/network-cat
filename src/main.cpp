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
#include "Network.hpp"

int main(int argc, char* argv[])
{
	try
	{
		Arguments::handle(argc, argv);

		if (Arguments::color)   Log::colors(true);
		if (Arguments::debug)   Log::debugMode(true);
		if (Arguments::verbose) Log::verboseMode(true);

		if (Arguments::client)
		{
			Client client(Arguments::ip, Arguments::port);

			while (true)
			{
				std::string input;

				if (!(std::getline(std::cin, input)))
					break;

				client.send(input);
			}
		}
		else if (Arguments::server)
		{
			Server server(Arguments::port);

			// Show our interfaces and IP addresses to the user
			// (Ugly as hell...!)
			Log::verbose("Interface name - IP address");
			std::vector<std::pair<std::string, std::string> > interfaces = Network::getInterfaces();
			for(std::vector<std::pair<std::string, std::string> >::iterator it = interfaces.begin();
				it != interfaces.end();
				it++)
				Log::verbose((*it).first + " - " + (*it).second);

			// Hell yeah main loop
			while (true)
			{
				std::string received = server.receive();
				Log::verbose("Received " +
							Log::intToString(received.length()) +
							" bytes");

				Log::log(received);
			}
		}
		else
			throw std::string("Unexpected behavior: Neither Client or Server");
	}
	catch (std::string s)
	{
		Log::error(s);
		exit(666);
	}
	return 0;
}
