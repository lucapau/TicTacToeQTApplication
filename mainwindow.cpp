#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeGame();

    // Connect buttons to slots
    connect(ui->pushButton00, &QPushButton::clicked, [this](){ onButtonClick(0, 0); });
    connect(ui->pushButton01, &QPushButton::clicked, [this](){ onButtonClick(0, 1); });
    connect(ui->pushButton02, &QPushButton::clicked, [this](){ onButtonClick(0, 2); });
    connect(ui->pushButton10, &QPushButton::clicked, [this](){ onButtonClick(1, 0); });
    connect(ui->pushButton11, &QPushButton::clicked, [this](){ onButtonClick(1, 1); });
    connect(ui->pushButton12, &QPushButton::clicked, [this](){ onButtonClick(1, 2); });
    connect(ui->pushButton20, &QPushButton::clicked, [this](){ onButtonClick(2, 0); });
    connect(ui->pushButton21, &QPushButton::clicked, [this](){ onButtonClick(2, 1); });
    connect(ui->pushButton22, &QPushButton::clicked, [this](){ onButtonClick(2, 2); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeGame()
{
    player1.name = "Player 1";
    player1.marker = 'X';
    player2.name = "Player 2";
    player2.marker = 'O';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board.grid[i][j] = '#';
        }
    }
    currentPlayer = 1;
    updateBoardDisplay();
}

void MainWindow::onButtonClick(int row, int col)
{
    playerInput(row, col);
    const char* result = checkWin();
    if (strcmp(result, "win") == 0) {
        QMessageBox::information(this, "Game Over", QString("%1 wins!").arg((currentPlayer == 1) ? player1.name : player2.name));
        initializeGame();
    } else if (strcmp(result, "draw") == 0) {
        QMessageBox::information(this, "Game Over", "The game is a draw!");
        initializeGame();
    } else {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        updateBoardDisplay();
    }
}

const char* MainWindow::checkWin()
{
    // Check rows for win
    for (int i = 0; i < 3; i++) {
        if (board.grid[i][0] != '#' &&
            board.grid[i][0] == board.grid[i][1] &&
            board.grid[i][0] == board.grid[i][2]) {
            return "win";
        }
    }

    // Check columns for win
    for (int j = 0; j < 3; j++) {
        if (board.grid[0][j] != '#' &&
            board.grid[0][j] == board.grid[1][j] &&
            board.grid[0][j] == board.grid[2][j]) {
            return "win";
        }
    }

    // Check main diagonal for win
    if (board.grid[0][0] != '#' &&
        board.grid[0][0] == board.grid[1][1] &&
        board.grid[0][0] == board.grid[2][2]) {
        return "win";
    }

    // Check anti-diagonal for win
    if (board.grid[0][2] != '#' &&
        board.grid[0][2] == board.grid[1][1] &&
        board.grid[0][2] == board.grid[2][0]) {
        return "win";
    }

    // Check for draw
    bool isDraw = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board.grid[i][j] == '#') {
                isDraw = false; // Board is not full, game continues
                break;
            }
        }
    }
    if (isDraw) {
        return "draw"; // Draw
    }

    return " "; // No winner yet
}

void MainWindow::playerInput(int row, int col)
{
    if (board.grid[row][col] != '#') {
        QMessageBox::warning(this, "Invalid Move", "That box is already occupied. Please select another one.");
        return;
    }

    board.grid[row][col] = (currentPlayer == 1) ? player1.marker : player2.marker;
}

void MainWindow::updateBoardDisplay()
{
    ui->pushButton00->setText(board.grid[0][0] == '#' ? "" : QString(board.grid[0][0]));
    ui->pushButton01->setText(board.grid[0][1] == '#' ? "" : QString(board.grid[0][1]));
    ui->pushButton02->setText(board.grid[0][2] == '#' ? "" : QString(board.grid[0][2]));
    ui->pushButton10->setText(board.grid[1][0] == '#' ? "" : QString(board.grid[1][0]));
    ui->pushButton11->setText(board.grid[1][1] == '#' ? "" : QString(board.grid[1][1]));
    ui->pushButton12->setText(board.grid[1][2] == '#' ? "" : QString(board.grid[1][2]));
    ui->pushButton20->setText(board.grid[2][0] == '#' ? "" : QString(board.grid[2][0]));
    ui->pushButton21->setText(board.grid[2][1] == '#' ? "" : QString(board.grid[2][1]));
    ui->pushButton22->setText(board.grid[2][2] == '#' ? "" : QString(board.grid[2][2]));
}
