#include <iostream>
using namespace std;

int board[10];
int turn;

void initBoard()
{
    for (int i = 1; i <= 9; i++) board[i] = 2;
    turn = 1;
}

void printBoard()
{
    cout << "\n";
    for (int i = 1; i <= 9; i++)
    {
        char c = (board[i] == 3) ? 'X' : (board[i] == 5) ? 'O' : (char)('0' + i);
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

void placeMove(int n)
{
    board[n] = (turn % 2 == 1) ? 3 : 5;
    turn++;
}

int pickSafeSquare()
{
    if (board[5] == 2) return 5;
    int edges[] = {2, 4, 6, 8};
    for (int sq : edges)
        if (board[sq] == 2) return sq;
    return 0;
}

int findWinningMove(int p)
{
    int lines[8][3] = {
        {1,2,3},{4,5,6},{7,8,9},
        {1,4,7},{2,5,8},{3,6,9},
        {1,5,9},{3,5,7}
    };
    int winProduct = p * p * 2;
    for (auto& line : lines)
    {
        int product = board[line[0]] * board[line[1]] * board[line[2]];
        if (product == winProduct)
            for (int sq : line)
                if (board[sq] == 2) return sq;
    }
    return 0;
}

bool checkWin(int p)
{
    int lines[8][3] = {
        {1,2,3},{4,5,6},{7,8,9},
        {1,4,7},{2,5,8},{3,6,9},
        {1,5,9},{3,5,7}
    };
    for (auto& line : lines)
        if (board[line[0]] == p && board[line[1]] == p && board[line[2]] == p)
            return true;
    return false;
}

bool isBoardFull()
{
    for (int i = 1; i <= 9; i++)
        if (board[i] == 2) return false;
    return true;
}

void computerMove()
{
    int sq = 0;

    if (turn == 1)
    {
        sq = 1;
    }
    else if (turn == 2)
    {
        sq = (board[5] == 2) ? 5 : 1;
    }
    else if (turn == 3)
    {
        sq = (board[9] == 2) ? 9 : 3;
    }
    else if (turn == 4)
    {
        int win = findWinningMove(3);
        sq = (win != 0) ? win : pickSafeSquare();
    }
    else if (turn == 5)
    {
        int wx = findWinningMove(3);
        int wo = findWinningMove(5);
        if      (wx != 0)       sq = wx;
        else if (wo != 0)       sq = wo;
        else if (board[7] == 2) sq = 7;
        else                    sq = 3;
    }
    else if (turn == 6)
    {
        int wo = findWinningMove(5);
        int wx = findWinningMove(3);
        if      (wo != 0) sq = wo;
        else if (wx != 0) sq = wx;
        else              sq = pickSafeSquare();
    }
    else
    {
        int wx = findWinningMove(3);
        int wo = findWinningMove(5);
        if      (wx != 0) sq = wx;
        else if (wo != 0) sq = wo;
        else
            for (int i = 1; i <= 9; i++)
                if (board[i] == 2) { sq = i; break; }
    }

    if (sq == 0)
        for (int i = 1; i <= 9; i++)
            if (board[i] == 2) { sq = i; break; }

    cout << "Computer (O) plays at square " << sq << "\n";
    placeMove(sq);
}

int main()
{
    cout << "=== Non-AI Tic Tac Toe (Program 2) ===\n";
    cout << "You are X (odd turns), Computer is O (even turns).\n";
    cout << "Squares numbered 1-9:\n";
    cout << " 1 | 2 | 3\n---+---+---\n 4 | 5 | 6\n---+---+---\n 7 | 8 | 9\n\n";

    initBoard();

    while (!isBoardFull())
    {
        printBoard();

        if (turn % 2 == 1)
        {
            int pos;
            cout << "Your turn (X). Enter square (1-9): ";
            cin >> pos;
            if (pos < 1 || pos > 9 || board[pos] != 2)
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            placeMove(pos);
        }
        else
        {
            computerMove();
        }

        if (checkWin(3)) { printBoard(); cout << "X wins!\n";            return 0; }
        if (checkWin(5)) { printBoard(); cout << "O (Computer) wins!\n"; return 0; }
    }

    printBoard();
    cout << "It's a draw!\n";
    return 0;
}