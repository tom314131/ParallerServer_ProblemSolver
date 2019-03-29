#ifndef AP_SECONDMS_TCP_CLIENT_H
#define AP_SECONDMS_TCP_CLIENT_H

#include <strings.h>

#include "TCP_client.h"
#include "../Etc/Utils.h"
#include "TCP_socket.h"

#define DEF_SIZE 256

#define ERR_READ "failure on reading from socket"
#define ERR_READ_TIMEOUT "reading timeout has reached"
#define ERR_SEND "failure on writing to socket"

namespace server_side {

    class TCP_client {

    protected:
        char buffer[DEF_SIZE];
        string current_string;
        string leftovers;

        TCP_socket sock;

    public:

        TCP_client() {};

        TCP_client(TCP_socket sock) : sock(sock) {}

        std::string GetLine();

        void Send(std::string message);

        void settimeout(int sec, int usec = 0);

        void close() { sock.close(); }
    };
}
#endif