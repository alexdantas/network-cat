#include <cstdlib>
#include "Arguments.hpp"

// Default values for class variables
bool         Arguments::client  = false;
bool         Arguments::server  = false;
std::string  Arguments::ip      = "";
int          Arguments::port    = DEFAULT_PORT;
bool         Arguments::color   = false;
bool         Arguments::debug   = false;
bool         Arguments::verbose = false;

void Arguments::handle(int argc, char* argv[])
{
	std::string usage("Show help:\n"
	                  "    $ network-cat -h, --help\n"
	                  "\n"
	                  "Client:\n"
	                  "    $ network-cat host-ip [port]\n"
	                  "\n"
	                  "Server:\n"
	                  "    $ network-cat -L [port]\n"
	                  "\n"
	                  "Flags:\n"
	                  "--colors, --debug, --verbose\n");

	if (argc < 2)
		throw std::string("Not enough arguments\n\n") + usage;

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == std::string("--help") ||
		    std::string(argv[i]) == std::string("-h"))
			throw usage;

		if (std::string(argv[i]) == std::string("--colors"))
			Arguments::color = true;

		if (std::string(argv[i]) == std::string("--debug"))
			Arguments::debug = true;

		if (std::string(argv[i]) == std::string("--verbose"))
			Arguments::verbose = true;
	}

	if (std::string(argv[1]) == std::string("-L"))
	{
		Arguments::server = true;

		// User-specified port
		if (argc > 2)
		{
			int port = atoi(argv[2]);
			if (port > 0)
				Arguments::port = port;
		}
	}
	else
	{
		Arguments::client = true;
		Arguments::ip = std::string(argv[1]);

		// User specified port
		if (argc > 2)
		{
			int port = atoi(argv[2]);
			if (port > 0)
				Arguments::port = port;
		}
	}

}
