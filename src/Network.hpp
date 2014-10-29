#ifndef NETWORK_H_DEFINED
#define NETWORK_H_DEFINED

#include <string>

/// A single UDP socket, abstracted away.
///
struct UDPSocket
{
    UDPSocket();

    /// Sets this socket connection as reusable.
    /// This is useful for the server, avoids having to wait for the
    /// connection to fully end before starting a new one.
    void setReusable();

    /// Binds socket to #port.
    /// Makes socket listen to incoming connections over #port.
    ///
    /// @note If it's under 40,000 something you might need
    ///       administrator rights.
    void bindTo(int port);

    /// Raw socket, used by the UNIX socket API.
    int raw_socket;
};

/// Reusable functions for networking.
namespace Network
{
    /// Returns the IP address for #hostname.
    /// Acts as the DNS, returning a string representation of the
    /// IP of #hostname.
    std::string hostToIp(std::string& hostname);
}

#endif //NETWORK_H_DEFINED
