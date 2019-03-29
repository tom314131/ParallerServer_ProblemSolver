#include "MatrixSolver.h"

MatrixSolver::MatrixSolver(Searcher<Cell> *searcher) {
    this->searcher = searcher;
}

string MatrixSolver::solve(SearchableMatrix *problem) {
    vector<State<Cell> *> result = searcher->Search(problem);
    if (result.size() == 1) {
        delete result[0];
        return UNREADCHABLE;
    }
    State<Cell> father = *result[1];
    State<Cell> current = *result[0];
    string moves;
    for (int i = 1; i < result.size() - 1;) {
        if (father.GetData().row < current.GetData().row &&
            father.GetData().column == current.GetData().column) {
            moves += DOWN;
        } else if (father.GetData().row > current.GetData().row &&
                   father.GetData().column == current.GetData().column) {
            moves += UP;
        } else if (father.GetData().column < current.GetData().column &&
                   father.GetData().row == current.GetData().row) {
            moves += RIGHT;
        } else if (father.GetData().column > current.GetData().column &&
                   father.GetData().row == current.GetData().row) {
            moves += LEFT;
        }
        moves += ",";
        current = father;
        if (i < result.size() - 1) {
            father = *result[++i];
        } else { break; }
    }
    moves = moves.substr(0, moves.length() - 1);
    for (int i = 0; i < result.size(); i++) {
        delete result[i];
    }
    return moves;
}

MatrixSolver::~MatrixSolver() {
    delete searcher;
}

Solver<SearchableMatrix *, string> *MatrixSolver::Clone() {
    return new MatrixSolver(searcher->Clone());
}

