#ifndef AP_SECONDMS_EXTRA_H
#define AP_SECONDMS_EXTRA_H

std::string current = clientSock.GetLine();
std::string answer;
while (current != END_INDICATOR) {
std::cout << "client handler::GetLine() returned: " << current << "\n";
answer = GetAnswer(current);
std::cout << "client handler::GetAnswer() returned: " << answer << "\n";
clientSock.Send(answer);
current = clientSock.GetLine();
}


State<Cell> *SearchableMatrix::GetStateInOffSetOf(State<Cell> *base,
                                                  int xDir,
                                                  int yDir) {
    State<Cell> *result = nullptr;
    if (xDir < _rowLength && yDir < _colLength) {
        if (_matrix[xDir][yDir] != WALL_VAL) {
            result = new State<Cell>({xDir, yDir}, _matrix[xDir][yDir], base);
        }
    }
    return result;
}
#endif