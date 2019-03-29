#ifndef AP_SECONDMS_TCP_SERVER_H
#define AP_SECONDMS_TCP_SERVER_H

#include <arpa/inet.h>

#include "TCP_socket.h"
#include "../Etc/MyException.h"
#include "TCP_client.h"
#include "Server.h"

#define ERR_BIND "failure on bind"
#define ERR_LISTEN "failure on listen"
#define ERR_ACCEPT "failure on accept"
#define DEF_TIMEOUT 1
#define NO_TIMEOUT 0

namespace server_side {

    class TCP_server : public Server {

    protected:
        TCP_socket _sock;
        bool _shouldStop;
        bool _ready;

    public:
        TCP_server() : _sock(), _ready(false), _shouldStop(false) {};

        // Base Class function
        void createSocket(int port);

        void listen(int max_lis);

        void SetTimeout(int sec, int usec = 0) { _sock.settimeout(sec, usec); }

        void CloseSock() { _sock.close(); }

        TCP_client Accept();

        bool ShouldStop() { return _shouldStop; }

        // Interface function
        pthread_t open(int port, ClientHandler *c) override = 0;

        void close() override = 0;
    };
}

#endif
