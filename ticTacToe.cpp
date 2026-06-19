#include "ticTacToe.h"
#include <fstream>

// Allocate NxN board
void alloc(char**& b, int n) {
    b = new char* [n];
    for (int i = 0; i < n; ++i) { b[i] = new char[n]; for (int j = 0; j < n; ++j) b[i][j] = ' '; }
}

// Free memory
void free(char**& b, int n) {
    if (!b) return;
    for (int i = 0; i < n; ++i) delete[] b[i];
    delete[] b; b = nullptr;
}

// Constructors
ticTacToe::ticTacToe() : N(3), moves(0), turn('X') { alloc(board, N); }
ticTacToe::ticTacToe(int n) : N(n >= 3 ? n : 3), moves(0), turn('X') { alloc(board, N); }
ticTacToe::ticTacToe(const ticTacToe& o) : N(o.N), moves(o.moves), turn(o.turn) {
    alloc(board, N);
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) board[i][j] = o.board[i][j];
}

// Destructor
ticTacToe::~ticTacToe() { free(board, N); }

// Assignment
ticTacToe& ticTacToe::operator=(const ticTacToe& o) {
    if (this == &o) return *this;
    free(board, N); N = o.N; moves = o.moves; turn = o.turn;
    alloc(board, N);
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) board[i][j] = o.board[i][j];
    return *this;
}

// Check if a line from (r,c) with direction (dr,dc) has N same symbols
bool ticTacToe::checkLine(int r, int c, int dr, int dc) const {
    char p = board[r][c]; if (p == ' ') return false;
    for (int k = 1; k < N; ++k) if (board[r + k * dr][c + k * dc] != p) return false;
    return true;
}

// Validate move
bool ticTacToe::isValid(int r, int c) const {
    return (r >= 0 && r < N && c >= 0 && c < N && board[r][c] == ' ');
}

// Make move
void ticTacToe::play(int r, int c) {
    if (!isValid(r, c)) return;
    board[r][c] = turn; ++moves;
    turn = (turn == 'X') ? 'O' : 'X';
}

// Check winner
char ticTacToe::winner() const {
    // Rows & cols
    for (int i = 0; i < N; ++i) {
        if (checkLine(i, 0, 0, 1)) return board[i][0];
        if (checkLine(0, i, 1, 0)) return board[0][i];
    }
    // Diagonals
    if (checkLine(0, 0, 1, 1)) return board[0][0];
    if (checkLine(0, N - 1, 1, -1)) return board[0][N - 1];
    // Draw or ongoing
    return (moves == N * N) ? 'D' : ' ';
}

// Print board
ostream& operator<<(ostream& os, const ticTacToe& g) {
    for (int i = 0; i < g.N; ++i) {
        os << " ";
        for (int j = 0; j < g.N; ++j) { os << " " << g.board[i][j] << " "; if (j < g.N - 1)os << "|"; }
        os << "\n";
        if (i < g.N - 1) { for (int k = 0; k < 4 * g.N - 1; ++k)os << "-"; os << "\n"; }
    }
    return os;
}

// Save game
void ticTacToe::save(const string& f) const {
    ofstream out(f); if (!out) return;
    out << N << " " << moves << " " << turn << "\n";
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) out << board[i][j] << " "; out << "\n";
}

// Load game
bool ticTacToe::load(const string& f) {
    ifstream in(f); if (!in) return false;
    int n, m; char t; if (!(in >> n >> m >> t) || n < 3) return false;
    free(board, N); N = n; moves = m; turn = t; alloc(board, N);
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) in >> board[i][j];
    return true;
}