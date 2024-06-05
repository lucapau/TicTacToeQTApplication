#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Player {
    QString name;
    char marker;
};

struct Board {
    char grid[3][3];
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClick(int row, int col);

private:
    Ui::MainWindow *ui;
    Board board;
    Player player1, player2;
    int currentPlayer;

    void initializeGame();
    void printBoard();
    const char* checkWin();
    void playerInput(int row, int col);
    void updateBoardDisplay();
};

#endif // MAINWINDOW_H
