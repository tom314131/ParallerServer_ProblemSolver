#ifndef AP_SECONDMS_SEARCHER_H
#define AP_SECONDMS_SEARCHER_H

#include "Searchable.h"

template<typename T>
class Searcher {

public:
    virtual std::vector<State<T> *> Search(Searchable<T> *s) = 0;

    virtual Searcher *Clone() = 0;

    virtual ~Searcher() = default;
};

#endif
