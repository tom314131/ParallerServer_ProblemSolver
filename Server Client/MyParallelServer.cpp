#include "MyParallelServer.h"
#include <pthread.h>

pthread_t MyParallelServer::open(int port, server_side::ClientHandler *c) {
    createSocket(port);
    SetTimeout(NO_TIMEOUT);

    auto *params = new ThreadParams();
    params->_server = this;
    params->_clientHandler = c;
    pthread_t trid;
    pthread_create(&trid, nullptr, MyParallelServer::Start, params);
    return trid;
}

void *MyParallelServer::Start(void *args) {
    auto *params = (ThreadParams *) args;
    CliThreadParams *cliParams;

    params->_server->listen(SOMAXCONN);

    server_side::TCP_client client = params->_server->Accept();
    params->_server->SetTimeout(DEF_TIMEOUT);

    while (!params->_server->ShouldStop()) {

        cliParams = new CliThreadParams();
        cliParams->clientSock = client;
        cliParams->handler = params->_clientHandler->Clone();
        cliParams->server = params->_server;
        params->_server->AddClient(cliParams);

        client = params->_server->Accept();
    }

    params->_server->CloseAll();
    delete params;

    return nullptr;
}

void MyParallelServer::AddClient(CliThreadParams *cliParams) {
    pthread_t newClient;
    pthread_create(&newClient, nullptr, MyParallelServer::DoClient, cliParams);

    UpdateThreadVector(newClient);
}

void MyParallelServer::UpdateThreadVector(pthread_t pthread, int operation) {
    lock.lock();
    if (operation == ADD) {
        _clientThreads.push_back(pthread);
    } else if (operation == DELETE) {
        std::vector<pthread_t>::iterator it;
        for (it = _clientThreads.begin(); it != _clientThreads.end(); ++it) {
            if (*it == pthread) {
                _clientThreads.erase(it);
                break;
            }
        }
    }
    lock.unlock();
}

void *MyParallelServer::DoClient(void *args) {
    auto *cliParams = (CliThreadParams *) args;
    cliParams->handler->handleClient(cliParams->clientSock);

    MyParallelServer *server = cliParams->server;
    delete cliParams->handler;
    delete cliParams;

    return nullptr;
}

void MyParallelServer::CloseAll() {
    for (pthread_t thread : _clientThreads) {
        pthread_join(thread, nullptr);
    }
}

void MyParallelServer::close() {
    _shouldStop = true;
}