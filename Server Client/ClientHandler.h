#ifndef AP_SECONDMS_CLIENTHANDLER_H
#define AP_SECONDMS_CLIENTHANDLER_H

#include <string>
#include "TCP_client.h"

namespace server_side {
    class ClientHandler {

    public:
        virtual void handleClient(TCP_client client) = 0;

        virtual ClientHandler *Clone() = 0;

        virtual ~ClientHandler() = default;
    };
}

#endif
