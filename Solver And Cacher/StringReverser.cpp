#include "StringReverser.h"

string StringReverser::solve(string problem) {
    string solution = problem;
    reverse(solution.begin(), solution.end());
    return solution;
}

Solver<string, string> *StringReverser::Clone() {
    return new StringReverser();
}

