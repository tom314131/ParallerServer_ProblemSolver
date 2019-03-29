#ifndef AP_SECONDMS_CUSTOMQUEUE_H
#define AP_SECONDMS_CUSTOMQUEUE_H

#include <iostream>
#include <set>
#include <unordered_map>

#include "State.h"

template<class T, class Comparator=PStateLess<T>>
class PStatePriQue {
    std::unordered_map<T,
            typename std::multiset<State<T> *>::iterator> _elements;

    std::multiset<State<T> *, Comparator> _sorted_elements;
public:
    PStatePriQue() = default;

    void Push(State<T> *state);

    void Remove(State<T> *state);

    void Update(State<T> *state);

    State<T> *GetState(T data) const;

    State<T> *PopMin();

    bool isExist(const State<T> *state) const;

    bool empty() const { return _sorted_elements.empty(); }

    int size() const;

    void print() const;

    void clear();
};

template<class T, class Comparator>
void PStatePriQue<T, Comparator>::Push(State<T> *state) {
    if (!isExist(state)) {
        T t = state->GetData();
        _elements[t] = _sorted_elements.insert(state);
    }
}

template<class T, class Comparator>
bool PStatePriQue<T, Comparator>::isExist(const State<T> *state) const {
    bool result = _elements.find(state->GetData()) != _elements.end();
    return result;
}

template<class T, class Comparator>
int PStatePriQue<T, Comparator>::size() const {
    return (int) _elements.size();
}

template<class T, class Comparator>
void PStatePriQue<T, Comparator>::Remove(State<T> *state) {
    _sorted_elements.erase(_elements[state->GetData()]);
    _elements.erase(state->GetData());
}

template<class T, class Comparator>
State<T> *PStatePriQue<T, Comparator>::PopMin() {
    State<T> *min = *_sorted_elements.begin();
    Remove(min);
    return min;
}

template<class T, class Comparator>
void PStatePriQue<T, Comparator>::Update(State<T> *state) {
    if (isExist(state)) {
        Remove(state);
        Push(state);
    }
}

template<class T, class Comparator>
State<T> *PStatePriQue<T, Comparator>::GetState(T data) const {
    return *(_elements.at(data));
}

template<class T, class Comparator>
void PStatePriQue<T, Comparator>::print() const {
    for (State<T> *t : _sorted_elements) {
        std::cout << *t << std::endl;
    }
    std::cout << std::endl;
}

template<class T, class Comparator>
void PStatePriQue<T, Comparator>::clear() {
    for (State<T> *state : _sorted_elements) {
        _elements.erase(state->GetData());
        delete state;
    }
    _sorted_elements.clear();
}


#endif
