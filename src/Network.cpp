
#include "Network.hpp"

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

void UDPServer::setReusable()
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

void UDPServer::bindTo(int port)
{
    // Which settings to apply to our socket
    struct sockaddr_in address;
    memset(&address, '\0', sizeof(address));

    // Make it an IP socket bound to any address on this port
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port        = htons(port);

    // Bind socket to previous settings
    int ret = bind(this->raw_socket,
                   (struct sockaddr*) &address,
                   sizeof(address));

    if (ret < 0)
        throw std::string(strerror(errno));
}

std::string Network::hostToIp(std::string& hostname)
{
    // Need to explicitly duplicate the string
    // because "gethostbyname" actually modifies
    // the C string (char*).
    std::string hostname_dup = hostname.substr();

    struct hostent* my_host;
    struct in_addr* my_host_address;

    my_host = gethostbyname(hostname_dup.c_str());
    if (my_host == NULL)
        return "";

    my_host_address = (struct in_addr*)my_host->h_addr_list[0];

    return std::string(inet_ntoa(*my_host_address));
}

std::vector<std::pair<std::string, std::string> > Network::getInterfaces()
{

    std::vector<std::pair<std::string, std::string> > interfaces;

    struct ifaddrs* raw_interfaces = NULL;
    struct ifaddrs* curr           = NULL;

    // Gets the raw interfaces as a linked list
    getifaddrs(&raw_interfaces);

    for (curr = raw_interfaces;
         curr != NULL;
         curr = curr->ifa_next)
    {
        // Is it a valid IPv4 Address?
        if (curr->ifa_addr->sa_family == AF_INET)
        {
            // Pointer to raw IP address
            void* tmp = &((struct sockaddr_in*)curr->ifa_addr)->sin_addr;

            // Convert it to a string dotted IP address (eg. 192.168.21.2)
            char buffer[20];
            inet_ntop(AF_INET, tmp, buffer, 20);

            std::string name(curr->ifa_name);
            std::string ip(buffer);

            std::pair<std::string, std::string> interface(name, ip);
            interfaces.push_back(interface);
        }
    }

    if (raw_interfaces != NULL)
        freeifaddrs(raw_interfaces);

    return interfaces;
}
