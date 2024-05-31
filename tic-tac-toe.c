#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    char marker;
} Player;

typedef struct {
    char grid[3][3];
} Board;

void printBoard(Board *board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board->grid[i][j]);
        }
        printf("\n");
    }
}

const char* checkWin(Board *board) {
    // Check rows for win
    for (int i = 0; i < 3; i++) {
        if (board->grid[i][0] != '#' &&
            board->grid[i][0] == board->grid[i][1] &&
            board->grid[i][0] == board->grid[i][2]) {
            return "win";
        }
    }

    // Check columns for win
    for (int j = 0; j < 3; j++) {
        if (board->grid[0][j] != '#' &&
            board->grid[0][j] == board->grid[1][j] &&
            board->grid[0][j] == board->grid[2][j]) {
            return "win";
        }
    }

    // Check main diagonal for win
    if (board->grid[0][0] != '#' &&
        board->grid[0][0] == board->grid[1][1] &&
        board->grid[0][0] == board->grid[2][2]) {
        return "win";
    }

    // Check anti-diagonal for win
    if (board->grid[0][2] != '#' &&
        board->grid[0][2] == board->grid[1][1] &&
        board->grid[0][2] == board->grid[2][0]) {
        return "win";
    }

    // Check for draw
    int isDraw = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->grid[i][j] == '#') {
                isDraw = 0; // Board is not full, game continues
                break;
            }
        }
    }
    if (isDraw) {
        return "draw"; // Draw
    }

    return " "; // No winner yet
}

void playerInput(Board *board, Player *player) {
    int input;
    printf("%s, select a box to input (0-8): ", player->name);
    scanf("%d", &input);

    if (input < 0 || input > 8) {
        printf("Invalid input. Please enter a number between 0 and 8.\n");
        playerInput(board, player); 
        return;
    }

    // Convert the input to grid coordinates
    int row = input / 3;
    int col = input % 3;

    if (board->grid[row][col] != '#') {
        printf("That box is already occupied. Please select another one.\n");
        playerInput(board, player); 
        return;
    }

    // Update the game board with the player's marker
    board->grid[row][col] = player->marker;
}

int main() {
    Player player1, player2;
    Board board = { '#', '#', '#', '#', '#', '#', '#', '#', '#' };
    // Initialize players
    strcpy(player1.name, "Player 1");
    player1.marker = 'X';
    strcpy(player2.name, "Player 2");
    player2.marker = 'O';

    // Main game loop
    int currentPlayer = 1;
    int totalMoves = 0;
    while (1) {
        printBoard(&board);

        Player *currentPlayerPtr = (currentPlayer == 1) ? &player1 : &player2;

        playerInput(&board, currentPlayerPtr);
        totalMoves++;

        // Check for win/draw conditions
        const char* result = checkWin(&board);
        if (strcmp(result, "win") == 0) {
            printBoard(&board);
            printf("Congratulations %s wins!\n", currentPlayerPtr->name);
            break;
        }
        else if (strcmp(result, "draw") == 0) {
            printBoard(&board);
            printf("The game is a draw!\n");
            break;
        }

        // Switch players for the next turn
        currentPlayer = (currentPlayer == 1) ? 2 : 1;

        
    }

    return 0;
}
