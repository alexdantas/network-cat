#ifndef NETWORK_H_DEFINED
#define NETWORK_H_DEFINED

// Has several reusable networking functions and data structures

struct UDPSocket
{
    UDPSocket();

    /// Sets this socket connection as reusable.
    /// This is useful for the server, avoids having to wait for the
    /// connection to fully end before starting a new one.
    void setReusable();

    /// Raw socket, used by the UNIX socket API.
    int raw_socket;
};

#endif //NETWORK_H_DEFINED
