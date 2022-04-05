//
// Created by Skyler Favors on 4/4/22.
//

#include "game.h"


bool game::PlaceMarker(int x, int y, int player) {
    if (board[y][x] == 0 && x != -1 && y != -1) {
        board[y][x] = player;
        return true;
    }
    return false;
}

int game::WinCheck() {
    int row = CompleteRow();
    if (row != -1) {
        isOver = true;
        winner = row;
        return row;
    }

    int col = CompleteColumn();
    if (col != -1) {
        isOver = true;
        winner = col;
        return col;
    }

    int diag = CompleteDiagonal();
    if (diag != -1) {
        isOver = true;
        winner = diag;
        return diag;
    }

    if (CheckTie()) {
        isOver = true;
        winner = 0;
        return 0;
    }

    return false;
}

int game::CompleteRow(){
    int track = 0;

    for (int y=0; y<size; y++) {
        for (int x=0; x<size; x++) {
            if (board[y][x] == 0) {
                continue;
            }
            else if (x != size-1) {
                if (board[y][x] == board[y][x+1]) {
                    track++;
                }
            } else if (track == size-1) {
                return board[y][x];
            }
        }
        track = 0;
    }
    return -1;
}

int game::CompleteColumn(){
    int track = 0;

    for (int x=0; x<size; x++) {
        for (int y=0; y<size; y++) {
            if (board[y][x] == 0) {
                continue;
            }
            else if (y != size-1) {
                if (board[y][x] == board[y+1][x]) {
                    track++;
                }
            } else if (track == size-1) {
                return board[y][x];
            }
        }
        track = 0;
    }
    return -1;
}

int game::CompleteDiagonal(){
    int principalPlayer = board[0][0];
    int secondaryPlayer = board[0][size-1];
    int trackPrincipal = 0;
    int trackSecondary = 0;

    for (int x=0; x<size; x++) {
        for (int y=0; y<size; y++) {
            if (board[y][x] == 0) {
                continue;
            }

            // Principal Diag
            if (y == x && board[y][x] == principalPlayer) {
                trackPrincipal++;
            }

            // Secondary Diag
            if ((y + x) == (size - 1) && board[y][x] == secondaryPlayer) {
                trackSecondary++;
            }
        }
    }

    if (trackPrincipal == size) {
        return principalPlayer;
    } else if (trackSecondary == size) {
        return secondaryPlayer;
    }

    return -1;
}

bool game::CheckTie() {
    for (int x=0; x<size; x++) {
        for (int y=0; y<size; y++) {
            if (board[y][x] == 0) {
                return false;
            }
        }
    }
    return true;
}
