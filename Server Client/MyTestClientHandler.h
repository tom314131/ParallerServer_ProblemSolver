#ifndef AP_SECONDMS_MYCLIENT_H
#define AP_SECONDMS_MYCLIENT_H

#include "ClientHandler.h"
#include "../Algorithms/SearchableMatrix.h"
#include "../Solver And Cacher/Solver.h"
#include "../Solver And Cacher/CacheManager.h"

#define END_INDICATOR "end"

class MyTestClientHandler : public server_side::ClientHandler {

    Solver<SearchableMatrix *, std::string> *_solver;
    CacheManager<std::string, std::string> *_manager;

    SearchableMatrix GetMatrixRequest(server_side::TCP_client client);

    std::string GetAnswer(SearchableMatrix *matrix);

public:
    MyTestClientHandler(Solver<SearchableMatrix *, string> *solver,
                        CacheManager<string, string> *manager);

    void handleClient(server_side::TCP_client clientSock) override;

    ClientHandler *Clone() override;

    ~MyTestClientHandler() override;
};


#endif
