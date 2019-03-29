#ifndef AP_SECONDMS_UTILS_H
#define AP_SECONDMS_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

void StringSeparatorByComma(string input, vector<int> &results);

bool UpdateCurrentFromLeftOvers(string &current_string, string &leftovers);

bool ManageStrings(const string &buffer, string &current_string,
                   string &leftovers);


#endif
