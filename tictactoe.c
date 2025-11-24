#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 3

// Function prototypes
void initBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
int makeMove(char board[SIZE][SIZE], int position, char player);
int checkWin(char board[SIZE][SIZE]);
int checkDraw(char board[SIZE][SIZE]);
void clearScreen();

int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int position;
    int gameOver = 0;
    char playAgain;

    printf("=================================\n");
    printf("   TIC-TAC-TOE GAME\n");
    printf("=================================\n\n");

    do {
        initBoard(board);
        gameOver = 0;
        currentPlayer = 'X';

        while (!gameOver) 
        {
            clearScreen();
            printBoard(board);
            
            printf("\nPlayer %c's turn\n", currentPlayer);
            printf("Enter position (1-9): ");
            
            if (scanf("%d", &position) != 1) 
            {
                // Clear invalid input
                while (getchar() != '\n');
                printf("Invalid input! Please enter a number.\n");
                printf("Press Enter to continue...");
                getchar();
                continue;
            }

            if (makeMove(board, position, currentPlayer)) 
            {
                // Check for win
                if (checkWin(board)) 
                {
                    clearScreen();
                    printBoard(board);
                    printf("\n Player %c wins! \n", currentPlayer);
                    gameOver = 1;
                }
                // Check for draw
                else if (checkDraw(board)) 
                {
                    clearScreen();
                    printBoard(board);
                    printf("\n It's a draw! \n");
                    gameOver = 1;
                }
                else {
                    // Switch player
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            } else {
                printf("Invalid move! Try again.\n");
                printf("Press Enter to continue...");
                while (getchar() != '\n');
                getchar();
            }
        }

        printf("\nPlay again? (y/n): ");
        scanf(" %c", &playAgain);
        
    } while (tolower(playAgain) == 'y');

    printf("\nThanks for playing!\n");
    return 0;
}

// Initialize the board with numbers 1-9
void initBoard(char board[SIZE][SIZE]) 
{
    int count = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) 
        {
            board[i][j] = '0' + count;
            count++;
        }
    }
}

// Print the current board state
void printBoard(char board[SIZE][SIZE]) 
{
    printf("\n");
    for (int i = 0; i < SIZE; i++) 
    {
        printf("     ");
        for (int j = 0; j < SIZE; j++) 
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) 
        {
            printf("     -----------\n");
        }
    }
    printf("\n");
}

// Make a move on the board
int makeMove(char board[SIZE][SIZE], int position, char player) 
{
    if (position < 1 || position > 9) 
    {
        return 0;
    }

    int row = (position - 1) / SIZE;
    int col = (position - 1) % SIZE;

    // Check if position is already taken
    if (board[row][col] == 'X' || board[row][col] == 'O') 
    {
        return 0;
    }

    board[row][col] = player;
    return 1;
}

// Check if there's a winner
int checkWin(char board[SIZE][SIZE]) 
{
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) 
        {
            return 1;
        }
    }

    // Check columns
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) 
        {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
    {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
    {
        return 1;
    }

    return 0;
}

// Check if the game is a draw
int checkDraw(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (board[i][j] != 'X' && board[i][j] != 'O') 
            {
                return 0;
            }
        }
    }
    return 1;
}

// Clear the screen (cross-platform)
void clearScreen() 
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}