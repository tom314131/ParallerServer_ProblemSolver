#ifndef AP_SECONDMS_STATEUNORDEREDSET_H
#define AP_SECONDMS_STATEUNORDEREDSET_H

#include <iostream>
#include <unordered_set>

#include "State.h"

template<typename T>
class PStateUnorderedSet {
    std::unordered_set<State<T> *, PStateHash<T>, PStateComp<T>> _set;
public:
    PStateUnorderedSet() = default;

    void Insert(State<T> *state);

    void Remove(State<T> *state);

    State<T> *GetState(State<T> *state) const;

    bool isExist(State<T> *state) const;

    bool empty() const { return _set.empty(); }

    int size() const;

    void clear();

};

template<typename T>
void PStateUnorderedSet<T>::Insert(State<T> *state) {
    if (!isExist(state)) {
        _set.insert(state);
    }
}

template<typename T>
bool PStateUnorderedSet<T>::isExist(State<T> *state) const {
    return _set.find(state) != _set.end();
}

template<typename T>
void PStateUnorderedSet<T>::Remove(State<T> *state) {
    _set.erase(state);
}

template<typename T>
int PStateUnorderedSet<T>::size() const {
    return _set.size();
}

template<typename T>
void PStateUnorderedSet<T>::clear() {
    for (State<T> *state : _set) {
        delete state;
    }
    _set.clear();
}

template<typename T>
State<T> *PStateUnorderedSet<T>::GetState(State<T> *state) const {
    return (*_set.find(state));
}


#endif
