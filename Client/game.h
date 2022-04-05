//
// Created by Skyler Favors on 4/4/22.
//

#ifndef TICTACTOECLIENT_GAME_H
#define TICTACTOECLIENT_GAME_H

#include <cstring>
#include <random>
#include <cmath>


// clean constructors


class game {
private:
    int difficulty = 0;
    int playerNum = 0;
    int size = 3;

    int CompleteRow();
    int CompleteColumn();
    int CompleteDiagonal();
    bool CheckTie();

public:
//    int** board;
    std::vector<std::vector<int>> board;
    bool yourTurn = false;
    bool isOver = false;
    int winner = -1;

    bool PlaceMarker(int x, int y, int player);
    int WinCheck();

    // for local multiplayer
    explicit game() {
        board = (std::vector<std::vector<int>>(size, std::vector<int>(size)));
        // initialize board and fill with zeros
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                board[y][x] = 0;
            }
        }
    }

    // singlePlayer
    explicit game(int difficulty, int size) : difficulty(difficulty), board(std::vector<std::vector<int>>(size, std::vector<int>(size))), size(size) {
        // initialize board and fill with zeros
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                board[y][x] = 0;
            }
        }
        // randomize starting player, only used for single player
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        int val = (int) round(dist(mt));

        if (val == 1) {
            yourTurn = true;
        }
    }


    int Bot() {
        switch (difficulty) {
            case 1:
                return EasyBot();
            case 2:
                return MediumBot();

            case 3:
                return HardBot();

            default:
                return -1;
        }
    }

private:
    int EasyBot() {
        // randomly choose coords
        std::random_device rd;
        std::mt19937 mt(rd());

        int x = -1;
        int y = -1;

        while (true) {
            std::uniform_real_distribution<double> dist(0.0, (float)size-1);
            double temp = dist(mt);
            x = (int) round(dist(mt));
            y = (int) round(dist(mt));

            if (PlaceMarker(x, y, 2)) {
                break;
            }
        }
        if (x != -1 && y != -1) {
            return y * size + x;
        }
        return -1;
    }

    int MediumBot() {
        return -1;
    }

    int HardBot() {
        return -1;
    }
};

#endif //TICTACTOECLIENT_GAME_H
