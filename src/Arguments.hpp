#ifndef ARGUMENTS_H_DEFINED
#define ARGUMENTS_H_DEFINED

#include <string>

#define DEFAULT_PORT 27015

/// Handles commandline arguments and holds global settings.
///
/// @note Aborts execution with `throw` in case of help.
class Arguments
{
public:

	static void handle(int argc, char* argv[]);

	static bool client;
	static bool server;
	static std::string ip;
	static int port;
	static bool color;       ///< Print messages with colors?
    static bool debug;
    static bool verbose;
};

#endif //ARGUMENTS_H_DEFINED
