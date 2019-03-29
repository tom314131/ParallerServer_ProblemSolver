#ifndef AP_SECONDMS_STATE_H
#define AP_SECONDMS_STATE_H

#include <iostream>

template<class T> // must have operator == !!!
class State {
    T _uniqueData;
    int _cost;
    State<T> *_cameFrom;

public:
    explicit State(T state,
                   int cost = 0,
                   State<T> *cameFrom = nullptr) : _uniqueData(state),
                                                   _cost(cost),
                                                   _cameFrom(cameFrom) {}

    bool operator==(const State<T> &right) const {
        return this->_uniqueData == right._uniqueData;
    }

    bool operator<(const State<T> &right) const {
        return this->_cost < right._cost;
    }

    int GetCost() const {
        return _cost;
    }

    void SetCost(int cost) {
        this->_cost = cost;
    }

    void SetData(T data) {
        this->_uniqueData = data;
    }

    T GetData() const {
        return _uniqueData;
    }

    State<T> *GetCameFrom() const {
        return _cameFrom;
    }

    void SetCameFrom(State<T> *_cameFrom) {
        State::_cameFrom = _cameFrom;
    }

    friend std::ostream &operator<<(std::ostream &os, const State &state) {
        os << "_uniqueData: " << state._uniqueData << " _cost: " << state._cost;
        return os;
    }

    std::string toString() {
        return _uniqueData.toString();
    }

};

template<typename T>    // compare for pointers to State<T>
struct PStateLess {
    bool operator()(State<T> *const &l, State<T> *const &r) const {
        return l->GetCost() < r->GetCost();
    }
};

template<typename T>    // compare for pointers to State<T>
struct PStateComp {
    bool operator()(State<T> *const &l, State<T> *const &r) const {
        return l->GetData() == r->GetData();
    }
};

template<typename T>
struct PStateHash {      // hash for pointer to State<T>
    size_t operator()(State<T> *const &state) const {
        return std::hash<T>()(state->GetData());
    }
};

namespace std {     // adding State<T> hash to std
    template<typename T>
    struct hash<State<T>> {
        size_t operator()(const State<T> &state) const {
            return hash<T>()(state.GetData());
        }
    };
}

#endif
