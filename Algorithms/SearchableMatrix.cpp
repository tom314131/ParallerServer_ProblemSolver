#include "SearchableMatrix.h"
#include <math.h>

// Constructors and Destructor
void SearchableMatrix::AllocateMatrix() {

    _matrix = new int *[_rowLength];

    for (int i = 0; i < _rowLength; i++) {
        _matrix[i] = new int[_colLength];
    }
}

void SearchableMatrix::UpdateAllocation(int rows, int columns) {
    if (_colLength != columns) {
        for (int i = 0; i < _rowLength; ++i) { delete _matrix[i]; }
        _colLength = columns;
        if (_rowLength != rows) {
            delete _matrix;
            _rowLength = rows;
            AllocateMatrix();
        } else {
            for (int i = 0; i < _rowLength; ++i) {
                _matrix[i] = new int[_colLength];
            }
        }
    } else if (_rowLength != rows) {
        int **tmp = _matrix;
        int min = _rowLength > rows ? rows : _rowLength;
        _matrix = new int *[rows];
        for (int i = 0; i < min; i++) { _matrix[i] = tmp[i]; }
        for (int j = min; j < _rowLength; ++j) { delete tmp[j]; }
        delete tmp;
        _rowLength = rows;
    }
}

SearchableMatrix::SearchableMatrix(int rows, int columns) :
        _rowLength(rows),
        _colLength(columns),
        _matrix(nullptr),
        _exitStateIndicator(
                {}) {
    LoadValidMovements();
    if (rows < MINIMUM_SIZE || columns < MINIMUM_SIZE) {
        throw MyException(SIZE_ERR);
    }
    AllocateMatrix();
}

SearchableMatrix::SearchableMatrix(SearchableMatrix &&other) noexcept
        : _exitStateIndicator({}) {
    this->_rowLength = other._rowLength;
    this->_colLength = other._colLength;
    this->_matrix = other._matrix;
    other._matrix = nullptr;
    this->_entrance = other._entrance;
    this->_exitStateIndicator = other._exitStateIndicator;
    LoadValidMovements();
}

SearchableMatrix::SearchableMatrix(const SearchableMatrix &other)
        : SearchableMatrix(other._rowLength, other._colLength) {
    (*this) = other; // copy assignment
}

SearchableMatrix::~SearchableMatrix() {
    if (_matrix != nullptr) {
        for (int i = 0; i < _rowLength; ++i) {
            if (_matrix[i] != nullptr) {
                delete[] _matrix[i];
            }
        }
        delete[] _matrix;
    }
}

SearchableMatrix &SearchableMatrix::operator=(SearchableMatrix &&other)
noexcept {
    this->_rowLength = other._rowLength;
    this->_colLength = other._colLength;
    this->_matrix = other._matrix;
    other._matrix = nullptr;
    this->_entrance = other._entrance;
    this->_exitStateIndicator = other._exitStateIndicator;
    this->_validMovements = other._validMovements;
    return *this;
}

SearchableMatrix &SearchableMatrix::operator=(const SearchableMatrix &other) {
    this->_entrance = other._entrance;
    this->_exitStateIndicator = other._exitStateIndicator;
    this->_validMovements = other._validMovements;
    UpdateAllocation(other._rowLength, other._colLength);
    for (int i = 0; i < _rowLength; ++i) {
        for (int j = 0; j < _colLength; ++j) {
            this->_matrix[i][j] = other._matrix[i][j];
        }
    }
    return *this;
}

// Class Specific Functions

void SearchableMatrix::LoadValidMovements() {
    if (_validMovements.empty()) {
        _validMovements.push_back({1, 0});
        _validMovements.push_back({0, 1});
        _validMovements.push_back({-1, 0});
        _validMovements.push_back({0, -1});
    }
}

void SearchableMatrix::SetData(std::vector<int> &data) {

    int index = 0;
    for (int i = 0; i < _rowLength; i++) {
        for (int j = 0; j < _colLength; j++) {
            try {
                _matrix[i][j] = data[index];
            } catch (const std::out_of_range &exp) {
                throw MyException(INVAL_INFO);
            }
            ++index;
        }
    }
}

void SearchableMatrix::SetInitialState(Cell start) {
    if (!IsInMatrix(start.row, start.column)) {
        throw MyException(OUT_OF_BOUNDRY);
    }
    this->_entrance = start;
}

void SearchableMatrix::SetExitState(Cell end) {
    if (!IsInMatrix(end.row, end.column)) {
        throw MyException(OUT_OF_BOUNDRY);
    }
    this->_exitStateIndicator.SetData(end);
}

void print(SearchableMatrix *m) {
    for (int i = 0; i < m->_rowLength; ++i) {
        for (int j = 0; j < m->_rowLength; ++j) {
            std::cout << m->_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

inline bool SearchableMatrix::IsInMatrix(int x, int y) const {
    return (0 <= x && x < _rowLength) &&
           (0 <= y && y < _colLength);
}

// Searchable Override Functions
State<Cell> *SearchableMatrix::GetInitialState() {
    return new State<Cell>({_entrance},
                           _matrix[_entrance.row][_entrance.column]);
}

bool SearchableMatrix::isGoal(State<Cell> *state) {
    return (*state) == _exitStateIndicator;
}

std::vector<State<Cell> *> SearchableMatrix::GetReachable(State<Cell>
                                                          *state) {
    std::vector<State<Cell> *> result;
    for (Cell movement : _validMovements) {
        int newX = state->GetData().row + movement.row;
        int newY = state->GetData().column + movement.column;
        if (IsInMatrix(newX, newY)) {
            int val = _matrix[newX][newY];
            if (val != WALL_VAL) {
                result.push_back(new State<Cell>({newX, newY},
                                                 _matrix[newX][newY] +
                                                 state->GetCost(),
                                                 state));
            }
        }
    }

    return result;
}

State<Cell> *SearchableMatrix::GetDummy() {
    return new State<Cell>({-1, -1});
}

std::string SearchableMatrix::toString() {
    std::string matrixFormat = "SP" + this->_entrance.toString();
    matrixFormat = matrixFormat + "EP" + this->_exitStateIndicator.toString();
    matrixFormat = matrixFormat + "RL" + std::to_string(_rowLength);
    matrixFormat = matrixFormat + "CL" + std::to_string(_colLength);
    matrixFormat += "Matrix";
    for (int i = 0; i < _rowLength; i++) {
        for (int j = 0; j < _rowLength; j++) {
            matrixFormat += std::to_string(_matrix[i][j]);
        }
    }
    return matrixFormat;
}

int SearchableMatrix::GetHeuristic(State<Cell> *state) {

    double result;
    auto it = heuristics.find(state->GetData());
    if (it != heuristics.end()) {
        result = (*it).second;
    } else {
        Cell cell = state->GetData();
        Cell end = _exitStateIndicator.GetData();
        result = sqrt((cell.row - end.row) *
                      (cell.row - end.row) +
                      (cell.column - end.column) *
                      (cell.column - end.column));
        heuristics[cell] = result;
    }

    return result;
}

std::vector<std::pair<int, State<Cell> *>>
SearchableMatrix::GetReachableNHeuristic(State<Cell> *state) {

    std::vector<std::pair<int, State<Cell> *>> result;

    std::vector<State<Cell> *> neighbors = GetReachable(state);
    for (State<Cell> *neighbor : neighbors) {
        result.emplace_back(GetHeuristic(neighbor), neighbor);
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const SearchableMatrix &matrix) {
    for (int i = 0; i < matrix._rowLength; ++i) {
        for (int j = 0; j < matrix._colLength; ++j) {
            os << matrix._matrix[i][j] << ", ";
        }
        os << "\n";
    }
    os << " _entrance: " << matrix._entrance.row << ", "
       << matrix._entrance.column;
    os << " _exit: " << matrix._exitStateIndicator.GetData().row << ", "
       << matrix._exitStateIndicator.GetData().column;
    return os;
}


