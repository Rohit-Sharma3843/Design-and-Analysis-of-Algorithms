#include <iostream>
using namespace std;

const int N = 8;
int board[N][N];

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

bool isSafe(int row, int col) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                if (j == col) return false;
                if (i - j == row - col) return false;
                if (i + j == row + col) return false;
            }
        }
    }
    return true;
}

bool solve(int row, int firstRow) {
    if (row == N) return true;

    if (row == firstRow)
        return solve(row + 1, firstRow);

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            if (solve(row + 1, firstRow)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int r, c;
    do {
        cout << "Enter row and column of first queen (0 to 7): ";
        cin >> r >> c;
    } while (r < 0 || r > 7 || c < 0 || c > 7);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    board[r][c] = 1;

    if (solve(0, r)) {
        int result[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                result[i][j] = board[i][j];
                board[i][j] = 0;
            }

        int step = 1;
        board[r][c] = 1;
        cout << "\nStep 1: First queen placed at row " << r << ", column " << c << endl;
        printBoard();

        for (int i = 0; i < N; i++) {
            if (i == r) continue;
            for (int j = 0; j < N; j++) {
                if (result[i][j] == 1) {
                    board[i][j] = 1;
                    step++;
                    cout << "\nStep " << step << ": Queen placed at row " << i << ", column " << j << endl;
                    printBoard();
                }
            }
        }
        cout << "\nAll 8 queens are placed.\n";
    } else {
        cout << "No solution possible with the first queen at this position.\n";
    }
    return 0;
}
