#ifndef AP_SECONDMS_MATRIXSOLVER_H
#define AP_SECONDMS_MATRIXSOLVER_H

#include "Solver.h"
#include "../Algorithms/SearchableMatrix.h"
#include "../Algorithms/Searcher.h"
#include "../Algorithms/State.h"
#include "../Algorithms/Cell.h"
#include <vector>
#include "../Algorithms/BFS.h"

#define UP "Up"
#define DOWN "Down"
#define RIGHT "Right"
#define LEFT "Left"
#define UNREADCHABLE "-1"

using namespace std;

class MatrixSolver : public Solver<SearchableMatrix *, string> {
private:
    Searcher<Cell> *searcher;
public:
    MatrixSolver(Searcher<Cell> *searcher);

    ~MatrixSolver() override;

    string solve(SearchableMatrix *problem) override;

    Solver<SearchableMatrix *, string> *Clone() override;


};


#endif
