#include <cstring>
#include "MySerialServer.h"

pthread_t MySerialServer::open(int port, server_side::ClientHandler *c) {
    createSocket(port);
    SetTimeout(NO_TIMEOUT);
    auto *params = new ThreadParams();
    params->_server = this;
    params->_clientHandler = c;
    pthread_t trid;
    pthread_create(&trid, nullptr, MySerialServer::Start, params);
    return trid;
}

void *MySerialServer::Start(void *args) {
    auto *params = (ThreadParams *) args;

    params->_server->listen(SOMAXCONN);
    server_side::TCP_client client = params->_server->Accept();
    params->_server->SetTimeout(DEF_TIMEOUT);

    while (!params->_server->ShouldStop()) {
        params->_clientHandler->handleClient(client);
        client = params->_server->Accept();
    }

    params->_server->CloseSock();
    delete params->_clientHandler;
    delete params;

    return nullptr;
}

void MySerialServer::close() {
    _shouldStop = true;
}


