#ifndef AP_SECONDMS_BestFS_H
#define AP_SECONDMS_BestFS_H

#include "Searcher.h"
#include "PStatePriQue.h"
#include "PStateUnorderedSet.h"

#include <unordered_set>

template<class T>
class BestFS : public Searcher<T> {

    int SetAnswerAndReset(std::vector<State<T> *> &result,
                          PStatePriQue<T> &open,
                          PStateUnorderedSet<T> &close,
                          State<T> *goal);

public:
    std::vector<State<T> *> Search(Searchable<T> *s) override;

    Searcher<T> *Clone() override;
};

template<class T>
int BestFS<T>::SetAnswerAndReset(std::vector<State<T> *> &result,
                                 PStatePriQue<T> &open,
                                 PStateUnorderedSet<T> &close,
                                 State<T> *goal) {
    int developedNodes = 0;

    State<T> *iterator = goal;
    while (iterator != nullptr) {
        result.push_back(iterator);
        if (open.isExist(iterator)) { open.Remove(iterator); }
        if (close.isExist(iterator)) { close.Remove(iterator); }
        iterator = iterator->GetCameFrom();
        ++developedNodes;
    }

    developedNodes += open.size() + close.size();
    // delete left memory
    open.clear();
    close.clear();

    return developedNodes;
}

template<class T>
std::vector<State<T> *> BestFS<T>::Search(Searchable<T> *s) {
    std::vector<State<T> *> result;
    PStatePriQue<T> open;
    PStateUnorderedSet<T> close;

    State<T> *goal;

    open.Push(s->GetInitialState());

    while (!open.empty()) {
        State<T> *current = open.PopMin();
        close.Insert(current);
        if (s->isGoal(current)) {
            goal = current;
            break;
        }
        std::vector<State<T> *> neighbors = s->GetReachable(current);
        for (State<T> *neighbor : neighbors) {
            if (!close.isExist(neighbor) && !open.isExist(neighbor)) {
                open.Push(neighbor);
                neighbor = nullptr;
            } else if (open.isExist(neighbor)) {
                State<T> *oldNeighbor = open.GetState(neighbor->GetData());
                if (oldNeighbor->GetCost() > neighbor->GetCost()) {
                    open.Update(neighbor);
                    neighbor = nullptr;
                }
            } else { // State must be in close.
                State<T> *oldNeighbor = close.GetState(neighbor);
                if (oldNeighbor->GetCost() > neighbor->GetCost()) {
                    close.Remove(neighbor);  // removes old neighbor - same data
                    open.Push(neighbor);
                    neighbor = nullptr;
                }
            }
            if (neighbor != nullptr) {
                delete neighbor;
            }
        }
    }

    int devNodes = SetAnswerAndReset(result, open, close, goal);
    State<T> *devNodesIndicator = s->GetDummy();
    devNodesIndicator->SetCost(devNodes);
    result.push_back(devNodesIndicator);

    return result;
}

template<class T>
Searcher<T> *BestFS<T>::Clone() {
    return new BestFS();
}


#endif
