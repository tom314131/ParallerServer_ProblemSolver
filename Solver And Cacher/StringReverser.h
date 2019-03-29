#ifndef AP_SECONDMS_STRINGREVERSER_H
#define AP_SECONDMS_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    StringReverser() = default;

    string solve(string problem) override;

    Solver<string, string> *Clone() override;

    ~StringReverser() override = default;

};

#endif
