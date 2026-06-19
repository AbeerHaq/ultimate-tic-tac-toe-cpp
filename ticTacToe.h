#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <iostream>
using namespace std;

class ticTacToe {
private:
    char** board;      // Dynamic 2D array
    int N;             // Board size
    int moves;         // Count of moves made
    char turn;         // Current player 'X' or 'O'

    // Helper: check if a line has N same symbols
    bool checkLine(int r, int c, int dr, int dc) const;

public:
    // Constructors & Destructor (Rule of 3)
    ticTacToe();                    // Default: 3x3
    explicit ticTacToe(int n);      // Param: NxN
    ticTacToe(const ticTacToe& o);  // Copy
    ~ticTacToe();                   // Cleanup

    // Assignment operator
    ticTacToe& operator=(const ticTacToe& o);

    // Game logic
    bool isValid(int r, int c) const;
    void play(int r, int c);
    char winner() const;            // 'X', 'O', 'D'(draw), ' '(ongoing)

    // I/O
    friend ostream& operator<<(ostream& os, const ticTacToe& g);
    void save(const string& f) const;
    bool load(const string& f);

    // Helpers for Ultimate mode
    char get(int r, int c) const { return (r >= 0 && r < N && c >= 0 && c < N) ? board[r][c] : ' '; }
    void set(int r, int c, char v) { if (r >= 0 && r < N && c >= 0 && c < N) board[r][c] = v; }

    // Accessors
    int size() const { return N; }
    char player() const { return turn; }
};
#endif

