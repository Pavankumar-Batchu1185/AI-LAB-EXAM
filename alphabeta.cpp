#include <iostream>
#include <climits>
using namespace std;

void printBoard(char board[3][3])
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool movesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return true;
    return false;
}

char getWinner(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return ' ';
}

int evaluate(char board[3][3])
{
    char w = getWinner(board);
    if (w == 'X') return  10;
    if (w == 'O') return -10;
    return 0;
}

int alphaBeta(char board[3][3], int depth, bool isMaximizing, int alpha, int beta)
{
    int score = evaluate(board);
    if (score ==  10) return score - depth;
    if (score == -10) return score + depth;
    if (!movesLeft(board)) return 0;

    if (isMaximizing)
    {
        int best = INT_MIN;
        bool pruned = false;
        for (int i = 0; i < 3 && !pruned; i++)
        {
            for (int j = 0; j < 3 && !pruned; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int val = alphaBeta(board, depth + 1, false, alpha, beta);
                    board[i][j] = ' ';
                    best  = max(best, val);
                    alpha = max(alpha, best);
                    if (beta <= alpha) pruned = true;
                }
            }
        }
        return best;
    }
    else
    {
        int best = INT_MAX;
        bool pruned = false;
        for (int i = 0; i < 3 && !pruned; i++)
        {
            for (int j = 0; j < 3 && !pruned; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int val = alphaBeta(board, depth + 1, true, alpha, beta);
                    board[i][j] = ' ';
                    best = min(best, val);
                    beta = min(beta, best);
                    if (beta <= alpha) pruned = true;
                }
            }
        }
        return best;
    }
}

pair<int,int> findBestMove(char board[3][3])
{
    int bestVal = INT_MIN;
    pair<int,int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                int moveVal = alphaBeta(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = ' ';
                if (moveVal > bestVal)
                {
                    bestVal = moveVal;
                    bestMove = {i, j};
                }
            }
        }
    }

    cout << "[Alpha-Beta] Best move H-value: " << bestVal << "\n";
    return bestMove;
}

int main()
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    cout << "=== AI Tic Tac Toe (Program 3 - Alpha-Beta Pruning) ===\n";
    cout << "AI is X (maximizes H), You are O (minimizes H).\n";
    cout << "H = P(X wins) - P(O wins).\n";
    cout << "Alpha-Beta pruning eliminates branches AI/Human would never choose.\n\n";

    cout << "Who goes first? (h = Human / a = AI): ";
    char choice;
    cin >> choice;
    char currentPlayer = (choice == 'a' || choice == 'A') ? 'X' : 'O';

    while (getWinner(board) == ' ' && movesLeft(board))
    {
        printBoard(board);

        if (currentPlayer == 'O')
        {
            int r, c;
            cout << "Your turn (O). Enter row and col (0-2): ";
            cin >> r >> c;
            if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != ' ')
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            board[r][c] = 'O';
            currentPlayer = 'X';
        }
        else
        {
            cout << "AI (X) thinking using Alpha-Beta Pruning...\n";
            auto [r, c] = findBestMove(board);
            board[r][c] = 'X';
            cout << "AI plays at row " << r << ", col " << c << "\n";
            currentPlayer = 'O';
        }
    }

    printBoard(board);
    char result = getWinner(board);
    if      (result == 'X') cout << "AI (X) wins!\n";
    else if (result == 'O') cout << "Human (O) wins!\n";
    else                    cout << "Draw!\n";

    return 0;
}