#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver<SearchableMatrix *, string>
                                         *solver,
                                         CacheManager<string, string> *manager)
        : _solver(solver), _manager(manager) {}

server_side::ClientHandler *MyTestClientHandler::Clone() {
    return new MyTestClientHandler(_solver->Clone(), _manager->Clone());
}


void MyTestClientHandler::handleClient(server_side::TCP_client clientSock) {

    // build matrix
    SearchableMatrix matrix = GetMatrixRequest(clientSock);

    // ask cache and solver
    string results = GetAnswer(&matrix);

    // return answer
    clientSock.Send(results);
}

SearchableMatrix MyTestClientHandler::GetMatrixRequest(server_side::TCP_client
                                                       client) {

    std::vector<int> matrix_data;
    int matrix_col;
    int matrix_row = 0;

    // get first line -> get number of columns
    std::string current = client.GetLine();
    StringSeparatorByComma(current, matrix_data);
    matrix_col = (int) matrix_data.size();
    ++matrix_row;

    current = client.GetLine();
    // get all numbers including rows and exit,entrance cells.
    while (current != END_INDICATOR) {
        StringSeparatorByComma(current, matrix_data);
        ++matrix_row;
        current = client.GetLine();
    }

    // Create matrix
    matrix_row -= 2; // last two rows were entrance and exit
    SearchableMatrix matrix = SearchableMatrix(matrix_row, matrix_col);

    // Set Exit and Entrance by the 4 last numbers received.
    int last_index = (int) matrix_data.size() - 1;
    matrix.SetExitState({matrix_data[last_index - 1], matrix_data[last_index]});
    matrix.SetInitialState({matrix_data[last_index - 3],
                            matrix_data[last_index - 2]});

    // remove the 4 last numbers received
    matrix_data.pop_back();
    matrix_data.pop_back();
    matrix_data.pop_back();
    matrix_data.pop_back();

    // set the rest as data
    matrix.SetData(matrix_data);

    return matrix;
}

std::string MyTestClientHandler::GetAnswer(SearchableMatrix *matrix) {
    std::string matrix_string = matrix->toString();
    std::string solution;
    if (_manager->IsSolutionExists(matrix_string)) {
        solution = _manager->GetSolution(matrix_string);
    } else {
        solution = _solver->solve(matrix);
        _manager->SaveSolution(matrix_string, solution);
    }
    return solution;
}

MyTestClientHandler::~MyTestClientHandler() {
    delete _solver;
    delete _manager;
}
