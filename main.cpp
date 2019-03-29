#include "Server Client/MyParallelServer.h"
#include "Server Client/MyTestClientHandler.h"
#include "Solver And Cacher/MatrixSolver.h"
#include "Solver And Cacher/FileCacheManager.h"
#include "Algorithms/Astar.h"

#define ERR_NO_PORT "Program must receive port number."
#define ERR_INVALID_ARG "Invalid argument, not a number."

int main(int argc, char **argv) {

    if (argc == 1) { throw MyException(ERR_NO_PORT); }

    int port;

    try {
        port = stoi(argv[1]);
    } catch (const std::invalid_argument &exp) {
        throw MyException(ERR_INVALID_ARG);
    }

    MyParallelServer server;

    auto *astar = new Astar<Cell>();
    auto *solver = new MatrixSolver(astar);
    auto *manager = new FileCacheManager();
    auto *handler = new MyTestClientHandler(solver, manager);

    pthread_t trid = server.open(port, handler);

    pthread_join(trid, nullptr);

    delete handler; // deletes its solver and manager
}

