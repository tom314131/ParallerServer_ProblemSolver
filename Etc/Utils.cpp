#include "Utils.h"

/**
 * receives a string of ints separated by ',' and vector of int.
 * separate string numbers and inserts them into vector.
 */
void StringSeparatorByComma(string input, vector<int> &results) {

    string currentValue;
    int index = 0;

    while (index < input.length()) {
        if (input[index] == ',') {
            if (!currentValue.empty()) {
                results.push_back(stoi(currentValue));
                currentValue.clear();
            }
        } else {
            currentValue += input[index];
        }
        index++;
    }

    if (!currentValue.empty()) {
        results.push_back(stoi(currentValue));
    }
}

/***
 * receives a string and a leftover string.
 * loads leftovers substring into current until reaches the end of leftover
 * or '\n'.
 * updates the leftover sub string the leftovers.
 * if encountered '\n', return true, else false.
 */
bool UpdateCurrentFromLeftOvers(string &current_string, string &leftovers) {
    bool hasNewLine = false;

    if (!leftovers.empty()) {
        int index = 0;
        while (index < leftovers.length()) {
            if (leftovers[index] != '\n') {
                current_string += leftovers[index];
            } else {
                hasNewLine = true;
                break;
            }
            index++;
        }
        if (index == leftovers.length()) {
            leftovers.clear();
        } else {
            leftovers = leftovers.substr(index + 1,
                                         leftovers.length() - index - 1);
        }
    }

    return hasNewLine;
}

/***
 * receives a buffer, current string and leftovers.
 * load leftovers into current string by its logic above.
 * if still hasn't encountered '\n\, then load buffer substring to current
 * until reaches the end or '\n'.
 * if encountered '\n' and buffer has more chars, loads them to leftover.
 * if encountered '\n' anywhere, returns true, else returns false.
 */
bool ManageStrings(const string &buffer, string &current_string,
                   string &leftovers) {
    int index = 0;
    bool hasNewLine = UpdateCurrentFromLeftOvers(current_string, leftovers);

    while (index < buffer.length()) {
        if (buffer[index] == '\n') {
            if (hasNewLine) {
                leftovers += buffer[index];
            } else {
                hasNewLine = true;
            }
        } else if (hasNewLine) {
            leftovers += buffer[index];
        } else {
            current_string += buffer[index];
        }
        index++;
    }

    return hasNewLine;
}

