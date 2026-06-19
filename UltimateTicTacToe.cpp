#include "ultimateTicTacToe.h"
#include <fstream>

ultimateTicTacToe::ultimateTicTacToe() : forced(-1), turn('X'), done(false) {
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) big[i][j] = ' ';
}

ultimateTicTacToe::ultimateTicTacToe(const ultimateTicTacToe& o)
    : forced(o.forced), turn(o.turn), done(o.done) {
    for (int i = 0; i < 9; ++i) small[i] = o.small[i];
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) big[i][j] = o.big[i][j];
}

// Check big board winner
char ultimateTicTacToe::bigWinner() const {
    for (int i = 0; i < 3; ++i) {
        if (big[i][0] != ' ' && big[i][0] == big[i][1] && big[i][1] == big[i][2]) return big[i][0];
        if (big[0][i] != ' ' && big[0][i] == big[1][i] && big[1][i] == big[2][i]) return big[0][i];
    }
    if (big[0][0] != ' ' && big[0][0] == big[1][1] && big[1][1] == big[2][2]) return big[0][0];
    if (big[0][2] != ' ' && big[0][2] == big[1][1] && big[1][1] == big[2][0]) return big[0][2];
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) if (big[i][j] == ' ') return ' ';
    return 'D';
}

// Validate move
bool ultimateTicTacToe::valid(int br, int bc, int r, int c) const {
    if (br < 0 || br>2 || bc < 0 || bc>2 || r < 0 || r>2 || c < 0 || c>2) return false;
    int i = idx(br, bc);
    if (!active(i)) return false;
    if (forced != -1 && forced != i) return false;
    return small[i].isValid(r, c);
}

// Make move
void ultimateTicTacToe::play(int br, int bc, int r, int c) {
    if (!valid(br, bc, r, c)) return;
    int i = idx(br, bc);
    small[i].play(r, c);
    char res = small[i].winner();
    if (res == 'X' || res == 'O') big[br][bc] = res;
    else if (res == 'D') big[br][bc] = 'T';
    forced = idx(r, c);
    if (!active(forced)) forced = -1;  // Free move if target is full/won
    turn = (turn == 'X') ? 'O' : 'X';
    if (winner() != ' ') done = true;
}

// Print all 9 boards
ostream& operator<<(ostream& os, const ultimateTicTacToe& g) {
    string sep = "+-------+-------+-------+------+\n"; os << sep;
    for (int br = 0; br < 3; ++br) {
        for (int line = 0; line < 3; ++line) {
            os << "|";
            for (int bc = 0; bc < 3; ++bc) {
                int i = g.idx(br, bc);
                for (int sc = 0; sc < 3; ++sc) os << " " << g.small[i].get(line, sc) << " ";
                os << "|";
            } os << "\n";
        } os << sep;
    } return os;
}

// Save game
void ultimateTicTacToe::save(const string& f) const {
    ofstream out(f); if (!out) return;
    out << forced << " " << turn << " " << done << "\n";
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) out << big[i][j] << " "; out << "\n";
    for (int k = 0; k < 9; ++k) for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) out << small[k].get(i, j) << " "; out << "\n";
}

// Load game
bool ultimateTicTacToe::load(const string& f) {
    ifstream in(f); if (!in) return false;
    int fr, ov; char pl; if (!(in >> fr >> pl >> ov)) return false;
    *this = ultimateTicTacToe(); forced = fr; turn = pl; done = (ov != 0);
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) in >> big[i][j];
    for (int k = 0; k < 9; ++k) for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) { char v; in >> v; small[k].set(i, j, v); }
    return true;
}