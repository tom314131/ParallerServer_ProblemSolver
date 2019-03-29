#ifndef AP_SECONDMS_SEARCHABLEMATRIX_H
#define AP_SECONDMS_SEARCHABLEMATRIX_H

#include <list>
#include <unordered_map>
#include <ostream>

#include "../Etc/MyException.h"
#include "Searchable.h"
#include "Cell.h"

#define MINIMUM_SIZE 2
#define WALL_VAL -1
#define SIZE_ERR "Cannot create a matrix in the given size!"
#define INVAL_INFO "Invalid given values!"
#define OUT_OF_BOUNDRY "The given location is out of boundry!"


/***
 * Represents a searchable matrix.
 * must be instantiated with valid size number.
 * before use be sure to set entrance and exit with Locations!
 */
class SearchableMatrix : virtual public Searchable<Cell> {

protected:
    int **_matrix;
    int _rowLength;
    int _colLength;
    Cell _entrance;
    State<Cell> _exitStateIndicator;
    std::list<Cell> _validMovements;
    std::unordered_map<Cell, int> heuristics;

public:
    friend std::ostream &
    operator<<(std::ostream &os, const SearchableMatrix &matrix);

protected:
    SearchableMatrix() = default;   // Cannot be used externally

    void AllocateMatrix();

    void LoadValidMovements();

    void UpdateAllocation(int rows, int columns);

    friend void print(SearchableMatrix *m);

public:
    // Ctors and Dtor
    explicit SearchableMatrix(int rows, int columns);

    SearchableMatrix(const SearchableMatrix &other); // copy constructor

    SearchableMatrix(SearchableMatrix &&other) noexcept; // move constructor

    SearchableMatrix &operator=(const SearchableMatrix &other); //cpy assignment

    SearchableMatrix &operator=(SearchableMatrix &&other) noexcept; //mv assign

    virtual ~SearchableMatrix();


    // Class Specific Functions
    void SetData(std::vector<int> &data);

    void SetInitialState(Cell start);

    void SetExitState(Cell end);

    bool IsInMatrix(int x, int y) const;


    // Searchable Override Functions
    State<Cell> *GetInitialState() override;

    bool isGoal(State<Cell> *state) override;

    std::vector<State<Cell> *> GetReachable(State<Cell> *state) override;

    State<Cell> *GetDummy() override;

    std::string toString();

    std::vector<std::pair<int, State<Cell> *>>
    GetReachableNHeuristic(State<Cell> *state) override;

    int GetHeuristic(State<Cell> *state) override;

};

#endif
