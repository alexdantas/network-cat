
#include "Network.hpp"
#include <string>

// include HELL for SOCKETS
#include <errno.h>
#include <stdint.h>     // absolute int types
#include <string.h>     // memset()
#include <fcntl.h>      // fcntl()
#include <stdlib.h>
#include <sys/socket.h> // socket() bind() inet_ntoa
#include <sys/types.h>  // inet_ntoa
#include <netinet/in.h> // inet_ntoa
#include <arpa/inet.h>  // inet_ntoa
#include <netdb.h>      // gethostbyname()
#include <sys/types.h>
#include <ifaddrs.h>

UDPSocket::UDPSocket():
    raw_socket(0)
{
    // Actually creates the IP/UDP socket
    int ret = socket(AF_INET, SOCK_DGRAM, 0);
    if (ret < 0)
        throw std::string(strerror(errno)); // show last error

    this->raw_socket = ret;
}

void UDPSocket::setReusable()
{
    // "setsockopt()" needs a pointer
    // to an integer with value 1
    int yes = 1;

    int ret = setsockopt(this->raw_socket,
                         SOL_SOCKET,
                         SO_REUSEADDR,
                         &yes,
                         sizeof(yes));

    if (ret < 0)
        throw std::string(strerror(errno)); // show Last error
}
