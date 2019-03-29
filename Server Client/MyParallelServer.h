#ifndef AP_SECONDMS_MYPARALLELSERVER_H
#define AP_SECONDMS_MYPARALLELSERVER_H

#include <mutex>
#include "TCP_server.h"
#include "TCP_client.h"

#define ADD 1
#define DELETE 0

class MyParallelServer;

struct CliThreadParams {
    server_side::TCP_client clientSock;
    server_side::ClientHandler *handler;
    MyParallelServer *server;
};

struct ThreadParams {
    MyParallelServer *_server;
    server_side::ClientHandler *_clientHandler;
};


class MyParallelServer : public server_side::TCP_server {

    std::vector<pthread_t> _clientThreads;
    mutex lock;

    void CloseAll();

    void AddClient(CliThreadParams *cliParams);

public:
    MyParallelServer() = default;

    static void *Start(void *args);

    static void *DoClient(void *args);

    pthread_t open(int port, server_side::ClientHandler *c) override;

    void close() override;

    void UpdateThreadVector(pthread_t pthread, int operation = ADD);
};


#endif
