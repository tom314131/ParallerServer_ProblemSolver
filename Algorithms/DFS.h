#ifndef AP_SECONDMS_DFS_H
#define AP_SECONDMS_DFS_H

#include <unordered_set>
#include <queue>

#include "Searcher.h"

template<typename T>
class DFS : public Searcher<T> {

    std::unordered_set<State<T> *, PStateHash<T>, PStateComp<T>> _grays;
    std::unordered_set<State<T> *, PStateHash<T>, PStateComp<T>> _blacks;
    State<T> *_goal;

    bool IsWhite(State<T> *state);

    std::vector<State<T> *> GetResults(Searchable<T> *s);

    bool Visit(State<T> *state, Searchable<T> *s);

public:
    DFS() : _goal(nullptr) {};

    std::vector<State<T> *> Search(Searchable<T> *s) override;

    Searcher<T> *Clone() override;
};

template<typename T>
bool DFS<T>::IsWhite(State<T> *state) {
    bool isGray = _grays.find(state) != _grays.end();
    bool isBlack = _blacks.find(state) != _blacks.end();
    return !(isBlack || isGray);
}

template<typename T>
std::vector<State<T> *> DFS<T>::GetResults(Searchable<T> *s) {

    int developedNodes = 0;
    std::vector<State<T> *> results;

    State<T> *iterator = _goal;
    while (iterator != nullptr) {
        results.push_back(iterator);
        _blacks.erase(iterator);
        iterator = iterator->GetCameFrom();
        ++developedNodes;
    }

    developedNodes += _blacks.size();

    if (!_blacks.empty()) {
        for (State<T> *state : _blacks) {
            delete state;
        }
        _blacks.clear();
    }

    State<T> *devIndicatorState = s->GetDummy();
    devIndicatorState->SetCost(developedNodes);
    results.push_back(devIndicatorState);

    _goal = nullptr;

    return results;
}

template<typename T>
bool DFS<T>::Visit(State<T> *state, Searchable<T> *s) {

    bool foundAnswer = false;

    if (s->isGoal(state)) {
        _goal = state;
        return true;
    }

    _grays.insert(state);       // change color to gray

    std::vector<State<T> *> neighbors = s->GetReachable(state);

    for (State<T> *neighbor : neighbors) {
        if (!foundAnswer && IsWhite(neighbor)) {
            if (Visit(neighbor, s)) {
                foundAnswer = true;
            }

        } else {
            delete neighbor;
        }
    }

    _grays.erase(state);        // change color to black
    _blacks.insert(state);

    return foundAnswer;
}

template<typename T>
std::vector<State<T> *> DFS<T>::Search(Searchable<T> *s) {
    State<T> *startState = s->GetInitialState();

    Visit(startState, s);

    return GetResults(s);
}

template<typename T>
Searcher<T> *DFS<T>::Clone() {
    return new DFS();
}


#endif
