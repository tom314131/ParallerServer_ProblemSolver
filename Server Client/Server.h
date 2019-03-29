#ifndef AP_SECONDMS_SERVER_H
#define AP_SECONDMS_SERVER_H

#include "ClientHandler.h"

namespace server_side {

    class Server {

    public:

        // create socket and
        virtual pthread_t open(int port, ClientHandler *c) = 0;

        // close the server
        virtual void close() = 0;

    };


}

#endif
