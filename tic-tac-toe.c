#include <stdio.h>

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
        playerInput(board, player); // Ask for input again
        return;
    }

    // Update the game board with the player's marker
    board->grid[row][col] = player->marker;
}


void playerMoves(char matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = i * 3 + j;
        }
    }
}

int main() {
    Player player1, player2;
    Board board = { '#', '#', '#', '#', '#', '#', '#', '#', '#' };
    printBoard(&board);
    
  
    
    return 0;
}
