//
// Created by Skyler Favors on 4/6/22.
//

#ifndef TICTACTOECLIENT_GAME_H
#define TICTACTOECLIENT_GAME_H


class game {
private:
    int CompleteRow();
    int CompleteColumn();
    int CompleteDiagonal();
    bool CheckTie();

public:
    std::vector<std::vector<int>> board = std::vector<std::vector<int>>(3, std::vector<int>(3));
    bool yourTurn = false;
    bool isOver = false;

    game();
    bool PlaceMarker(int x, int y);
    bool WinCheck();
    void ResetBoard();
};


#endif //TICTACTOECLIENT_GAME_H
