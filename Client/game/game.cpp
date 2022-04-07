//
// Created by Skyler Favors on 4/6/22.
//

#include <vector>

#include "game.h"

game::game() {
    // initialize board and fill with zeros
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            board[y][x] = 0;
        }
    }
}

bool game::PlaceMarker(int x, int y) {
    int p = 1;
    if (!yourTurn) {
        p = 2;
    }

    if (board[y][x] == 0 && x != -1 && y != -1) {
        board[y][x] = p;
        return true;
    }
    return false;
}

bool game::WinCheck() {
    int row = CompleteRow();
    if (row != -1) {
        isOver = true;
//        return row;
        return true;
    }

    int col = CompleteColumn();
    if (col != -1) {
        isOver = true;
//        return col;
        return true;
    }

    int diag = CompleteDiagonal();
    if (diag != -1) {
        isOver = true;
//        return diag;
        return true;
    }

    if (CheckTie()) {
        isOver = true;
//        return 0;
        return true;
    }

    return false;
}

int game::CompleteRow(){
    int track = 0;

    for (int y=0; y<3; y++) {
        for (int x=0; x<3; x++) {
            if (board[y][x] == 0) {
                continue;
            }
            else if (x != 3-1) {
                if (board[y][x] == board[y][x+1]) {
                    track++;
                }
            } else if (track == 3-1) {
                return board[y][x];
            }
        }
        track = 0;
    }
    return -1;
}

int game::CompleteColumn(){
    int track = 0;

    for (int x=0; x<3; x++) {
        for (int y=0; y<3; y++) {
            if (board[y][x] == 0) {
                continue;
            }
            else if (y != 3-1) {
                if (board[y][x] == board[y+1][x]) {
                    track++;
                }
            } else if (track == 3-1) {
                return board[y][x];
            }
        }
        track = 0;
    }
    return -1;
}

int game::CompleteDiagonal(){
    int principalPlayer = board[0][0];
    int secondaryPlayer = board[0][3-1];
    int trackPrincipal = 0;
    int trackSecondary = 0;

    for (int x=0; x<3; x++) {
        for (int y=0; y<3; y++) {
            if (board[y][x] == 0) {
                continue;
            }

            // Principal Diag
            if (y == x && board[y][x] == principalPlayer) {
                trackPrincipal++;
            }

            // Secondary Diag
            if ((y + x) == (3 - 1) && board[y][x] == secondaryPlayer) {
                trackSecondary++;
            }
        }
    }

    if (trackPrincipal == 3) {
        return principalPlayer;
    } else if (trackSecondary == 3) {
        return secondaryPlayer;
    }

    return -1;
}

bool game::CheckTie() {
    for (int x=0; x<3; x++) {
        for (int y=0; y<3; y++) {
            if (board[y][x] == 0) {
                return false;
            }
        }
    }
    return true;
}
