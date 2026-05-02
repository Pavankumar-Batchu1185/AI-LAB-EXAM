#include <iostream>
#include <vector>
using namespace std;

int magic[10] = {0, 8, 1, 6, 3, 5, 7, 4, 9, 2};
int board[10];
vector<int> humanVals;
vector<int> compVals;
int turn;

void initBoard()
{
    for (int i = 1; i <= 9; i++) board[i] = 0;
    humanVals.clear();
    compVals.clear();
    turn = 1;
}

void printBoard()
{
    cout << "\n";
    for (int i = 1; i <= 9; i++)
    {
        char c = (board[i] == 1) ? 'X' : (board[i] == 2) ? 'O' : (char)('0' + i);
        cout << " " << c;
        if (i % 3 == 0)
        {
            cout << "\n";
            if (i < 9) cout << "---+---+---\n";
        }
        else
        {
            cout << " |";
        }
    }
    cout << "\n";
}

bool hasWon(vector<int>& vals)
{
    int n = vals.size();
    if (n < 3) return false;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (vals[i] + vals[j] + vals[k] == 15)
                    return true;
    return false;
}

int findWinningMove(vector<int>& vals)
{
    int n = vals.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int needed = 15 - vals[i] - vals[j];
            if (needed < 1 || needed > 9) continue;
            for (int sq = 1; sq <= 9; sq++)
            {
                if (magic[sq] == needed && board[sq] == 0)
                    return sq;
            }
        }
    }
    return 0;
}

int pickSafeSquare()
{
    if (board[5] == 0) return 5;
    int edges[] = {2, 4, 6, 8};
    for (int sq : edges)
        if (board[sq] == 0) return sq;
    return 0;
}

bool isBoardFull()
{
    for (int i = 1; i <= 9; i++)
        if (board[i] == 0) return false;
    return true;
}

void placeMove(int sq, int player)
{
    board[sq] = player;
    if (player == 1) humanVals.push_back(magic[sq]);
    else             compVals.push_back(magic[sq]);
    turn++;
}

void humanMove()
{
    int sq;
    while (true)
    {
        cout << "Your turn (X). Enter square (1-9): ";
        cin >> sq;
        if (sq >= 1 && sq <= 9 && board[sq] == 0) break;
        cout << "Invalid! Try again.\n";
    }
    placeMove(sq, 1);
}

void computerMove()
{
    int sq = 0;

    if (turn == 2)
    {
        sq = (board[5] == 0) ? 5 : 1;
    }
    else if (turn == 3)
    {
        sq = (board[9] == 0) ? 9 : 3;
    }
    else
    {
        int win   = findWinningMove(compVals);
        int block = findWinningMove(humanVals);

        if (win != 0)        sq = win;
        else if (block != 0) sq = block;
        else                 sq = pickSafeSquare();
    }

    if (sq == 0)
        for (int i = 1; i <= 9; i++)
            if (board[i] == 0) { sq = i; break; }

    cout << "Computer (O) plays at square " << sq << "\n";
    placeMove(sq, 2);
}

int main()
{
    cout << "=== Tic Tac Toe (Magic Square Strategy) ===\n";
    cout << "You are X (odd turns). Computer is O (even turns).\n";
    cout << "Squares are numbered 1-9:\n";
    cout << " 1 | 2 | 3\n---+---+---\n 4 | 5 | 6\n---+---+---\n 7 | 8 | 9\n\n";

    initBoard();

    while (!isBoardFull())
    {
        printBoard();

        if (turn % 2 == 1) humanMove();
        else               computerMove();

        if (hasWon(humanVals)) { printBoard(); cout << "You win!\n";       return 0; }
        if (hasWon(compVals))  { printBoard(); cout << "Computer wins!\n"; return 0; }
    }

    printBoard();
    cout << "It's a draw!\n";
    return 0;
}