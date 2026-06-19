#define _CRT_SECURE_NO_WARNINGS
#include "ticTacToe.h"
#include "ultimateTicTacToe.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void clear() { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

// Problem 01: Regular game
void playRegular() {
    cout << "\n=== Regular Tic Tac Toe ===\n1.New 2.Load: ";
    int ch; cin >> ch; clear();
    ticTacToe g;
    if (ch == 1) { int n; cout << "Size (>=3): "; cin >> n; clear(); g = ticTacToe(n); }
    else g.load("BasicGame.txt");

    while (true) {
        cout << "\nPlayer " << g.player() << "\n" << g;
        cout << "Move (row col) or 's' save: "; string inp; getline(cin, inp);
        if (inp == "s") { g.save("BasicGame.txt"); cout << "Saved.\n"; break; }
        int r, c; if (sscanf_s(inp.c_str(), "%d %d", &r, &c) == 2 && g.isValid(r, c)) {
            g.play(r, c); char w = g.winner();
            if (w != ' ') { cout << g << (w == 'D' ? "\nDraw!\n" : "\nPlayer " + string(1, w) + " wins!\n"); break; }
        }
        else cout << "Invalid.\n";
    }
}

// Problem 02: Ultimate game
void playUltimate() {
    cout << "\n=== Ultimate Tic Tac Toe ===\n1.New 2.Load: ";
    int ch; cin >> ch; clear();
    ultimateTicTacToe g;
    if (ch == 2) g.load("UltimateGame.txt");

    while (!g.over()) {
        cout << "\nPlayer " << g.player();
        int nb = g.next(); if (nb == -1) cout << " [FREE MOVE]"; else cout << " [Play in board " << nb / 3 << "," << nb % 3 << "]";
        cout << "\n" << g;
        cout << "Move (br bc r c) or 's' save: "; string inp; getline(cin, inp);
        if (inp == "s") { g.save("UltimateGame.txt"); cout << "Saved.\n"; break; }
        int br, bc, r, c; if (sscanf_s(inp.c_str(), "%d %d %d %d", &br, &bc, &r, &c) == 4 && g.valid(br, bc, r, c)) {
            g.play(br, bc, r, c);
        }
        else cout << "Invalid.\n";
    }
    if (g.over()) { cout << "\n" << g; char w = g.winner(); cout << (w == 'D' ? "\nDraw!\n" : "\nPlayer " + string(1, w) + " wins!\n"); }
}

int main() {
    while (true) {
        cout << "\n=== MENU ===\n1.Regular 2.Ultimate 3.Exit\nChoice: ";
        int ch; cin >> ch; clear();
        if (ch == 1) playRegular();
        else if (ch == 2) playUltimate();
        else if (ch == 3) return 0;
        else cout << "Invalid.\n";
    }
}