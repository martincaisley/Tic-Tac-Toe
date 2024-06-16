#include <stdio.h>
#include <limits.h>

#define SIZE 3

// Prototypes
bool checkForWin(char board[SIZE][SIZE], char player);
bool checkForDraw(char board[SIZE][SIZE]);
void printGrid(char board[SIZE][SIZE]);
bool makeMove(int move, char player, char board[SIZE][SIZE]);
int minimax(char board[SIZE][SIZE],int depth, bool isMaximizing);
int availableMoves(char board[SIZE][SIZE]);

void printGrid(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
}

bool makeMove(int move, char player, char board[SIZE][SIZE]) {
    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;

    if (board[row][col] == 'x' || board[row][col] == 'o') {
        return false; // Spot is already taken
    }

    board[row][col] = player;
    return true;
}

bool checkForDraw(char board[SIZE][SIZE]) {
    for (int i = 0 ; i < SIZE ; i++) {
        for (int j = 0 ; j < SIZE ; j++) {
            if (board[i][j] != 'x' && board[i][j] != 'o') {
                return false;
            }
        }
    }
    return true;
}

bool checkForWin(char board[SIZE][SIZE], char player) {
    // Orthogonal.
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Diagonal
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

int availableMoves(char board[SIZE][SIZE]) {
    int bestScore = INT_MIN;
    int bestMove = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'x' && board[i][j] != 'o') {
                char temp = board[i][j];
                board[i][j] = 'o';
                int score = minimax(board, 3, false);
                board[i][j] = temp;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = (i * SIZE) + (j + 1);
                }
            }
        }
    }
    return bestMove;
}

int minimax(char board[SIZE][SIZE], int depth, bool isMaximizing) {
    if (checkForWin(board, 'o')) return 10 - depth;
    if (checkForWin(board, 'x')) return depth - 10;
    if (checkForDraw(board)) return 0;

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 'x' && board[i][j] != 'o') {
                    char temp = board[i][j];
                    board[i][j] = 'o';
                    int score = minimax(board, depth + 1, false);
                    board[i][j] = temp;
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 'x' && board[i][j] != 'o') {
                    char temp = board[i][j];
                    board[i][j] = 'x';
                    int score = minimax(board, depth + 1, true);
                    board[i][j] = temp;
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}


int main(void) {
    bool gameWon = false;
    bool gameDrawn = false;
    char currentPlayer = 'x';
    char move;
    int moveNumber;

    char board[SIZE][SIZE] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
    };

    printGrid(board);

    while (!gameWon && !gameDrawn) {
        if(currentPlayer == 'x') {
            printf("Player %c, enter your move using the numbers on the grid:\n\n", currentPlayer);
            scanf(" %c", &move); // space before %c to consume any leftover whitespace.
            moveNumber = move - '0';
        }
        else {
            moveNumber = availableMoves(board);
            printf("Opponent chose move: %d\n", moveNumber);
        }

        if (moveNumber < 1 || moveNumber > 9) {
            printf("Invalid Move Number: %c, Please try again\n", move);
            continue; // Skip to the next iteration of the loop to get a valid move
        }

        if (!makeMove(moveNumber, currentPlayer, board)) {
            printf("Spot already taken, please try again.\n");
            continue; // Skip to the next iteration of the loop to get a valid move
        }

        printGrid(board);
        gameWon = checkForWin(board, currentPlayer);
        gameDrawn = checkForDraw(board);

        if (gameWon) {
            printf("Player %c has won!\n", currentPlayer);
        } else if (gameDrawn) {
            printf("Game ended in a draw\n");
        } else {
            currentPlayer = (currentPlayer == 'x') ? 'o' : 'x';
        }
    }

    return 0;
}
