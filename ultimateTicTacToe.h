#ifndef ULTIMATE_H
#define ULTIMATE_H
#include "ticTacToe.h"
#include <iostream>
using namespace std;

class ultimateTicTacToe {
private:
    ticTacToe small[9];   // 3x3 array of small boards
    char big[3][3];       // Status: 'X','O','T'(tie),' '(active)
    int forced;           // -1=free, 0-8=forced board index
    char turn;
    bool done;

    int idx(int br, int bc) const { return br * 3 + bc; }
    bool active(int i) const { return big[i / 3][i % 3] == ' '; }
    char bigWinner() const;

public:
    ultimateTicTacToe();
    ultimateTicTacToe(const ultimateTicTacToe& o);
    ~ultimateTicTacToe() {}  // small[] auto-cleanup

    friend ostream& operator<<(ostream& os, const ultimateTicTacToe& g);
    bool valid(int br, int bc, int r, int c) const;
    void play(int br, int bc, int r, int c);
    char winner() const { return bigWinner(); }
    void save(const string& f) const;
    bool load(const string& f);

    int next() const { return forced; }
    char player() const { return turn; }
    bool over() const { return done; }
};
#endif