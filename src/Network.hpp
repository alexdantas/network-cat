#ifndef NETWORK_H_DEFINED
#define NETWORK_H_DEFINED

#include <string>
#include <vector>

/// A single UDP socket, abstracted away.
///
struct UDPSocket
{
    /// Creates (and initializes) an empty socket.
    UDPSocket();

    /// Raw socket, used by the UNIX socket API.
    int raw_socket;
};

/// UDP Socket specific for listening to and receive data (strings).
struct UDPServer: UDPSocket
{
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
};

/// UDP Socket specific for sending data (strings).
struct UDPClient: UDPSocket
{
    /// Sends #message to #ip through #port.
    /// There needs to be a server listening on remote #ip and
    /// to that #port, otherwise the message will be lost.
    void send(std::string message, std::string ip, int port);
};

/// Reusable functions for networking.
namespace Network
{
    /// Returns the IP address for #hostname.
    /// Acts as the DNS, returning a string representation of the
    /// IP of #hostname.
    std::string hostToIp(std::string& hostname);

    /// Returns all networking interfaces of the current machine.
    ///
    /// Looks daunting, but it's merely a vector of interfaces,
    /// like <interface name, interface ip address>.
    ///
    /// For example, on Linux, it could be <"eth0", "192.168.0.6">
    /// Windows usually have a big-ass hex string.
    ///
    std::vector<std::pair<std::string, std::string> > getInterfaces();
}

#endif //NETWORK_H_DEFINED
