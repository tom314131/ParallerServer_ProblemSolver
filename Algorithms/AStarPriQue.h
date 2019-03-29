#ifndef AP_SECONDMS_ASTARPRIQUE_H
#define AP_SECONDMS_ASTARPRIQUE_H

#include <iostream>
#include <set>
#include <unordered_map>

#include "State.h"

template<class T>
struct AStarState {
    int totalValue;
    int heuristic;
    State<T> *state;

    bool operator<(const AStarState &r) const {
        return this->totalValue < r.totalValue;
    }

    friend std::ostream &operator<<(std::ostream &os, const AStarState &state) {
        os << "totalValue: " << state.totalValue << " heuristic: "
           << state.heuristic << " state: " << (*state.state);
        return os;
    }
};

template<class T>
class AStarPriQue {
    std::unordered_map<T,
            typename std::multiset<AStarState<T>>::iterator> _elements;
    std::multiset<AStarState<T>> _sorted_elements;
public:
    AStarPriQue() = default;

    void Push(AStarState<T> aState);

    void Remove(State<T> *state);

    void Update(State<T> *state);

    State<T> *GetState(State<T> *state) const;

    State<T> *PopMin();

    bool isExist(const State<T> *state) const;

    bool empty() const { return _sorted_elements.empty(); }

    int size() const;

    void print() const;

    void clear();
};


template<class T>
void AStarPriQue<T>::Push(AStarState<T> aState) {
    if (!isExist(aState.state)) {
        T t = aState.state->GetData();
        _elements[t] = _sorted_elements.insert(aState);
    }
}

template<class T>
bool AStarPriQue<T>::isExist(const State<T> *state) const {
    bool result = _elements.find(state->GetData()) != _elements.end();
    return result;
}

template<class T>
int AStarPriQue<T>::size() const {
    return (int) _elements.size();
}

template<class T>
void AStarPriQue<T>::Remove(State<T> *state) {
    _sorted_elements.erase(_elements[state->GetData()]);
    _elements.erase(state->GetData());
}

template<class T>
State<T> *AStarPriQue<T>::PopMin() {
    State<T> *min = (*_sorted_elements.begin()).state;
    Remove(min);
    return min;
}

template<class T>
void AStarPriQue<T>::Update(State<T> *state) {
    if (isExist(state)) {
        AStarState<T> newState;
        newState.state = state;
        newState.heuristic = (*_elements[state->GetData()]).heuristic;
        newState.totalValue = newState.heuristic + state->GetCost();
        Remove(state);
        Push(newState);
    }
}

template<class T>
void AStarPriQue<T>::print() const {
    for (AStarState<T> aState : _sorted_elements) {
        std::cout << aState << std::endl;
    }
    std::cout << std::endl;
}

template<class T>
void AStarPriQue<T>::clear() {
    for (AStarState<T> aState : _sorted_elements) {
        delete aState.state;
    }
    _elements.clear();
    _sorted_elements.clear();
}

template<class T>
State<T> *AStarPriQue<T>::GetState(State<T> *state) const {
    return (*_elements.at(state->GetData())).state;
}

#endif
