#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QVector>

class Scene : public QWidget
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = nullptr);

signals:
    void onClick(int x, int y, int value);

public slots:
    void positionChanged(QVector<int>);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int m_grid[3][3]; // Game m_grid
    int currentPlayer; // Current player (1 - X, 2 - O)
    bool gameActive; // Flag indicating if game is active
    int scoreX; // Score for player X
    int scoreO; // Score for player O

    QLabel *scoreLabel; // Label to display score
    QPushButton *resetGameButton; // Button to reset game
    QPushButton *resetScoreButton; // Button to reset score
    QPushButton *quitButton; // Button to quit game

    void drawCross(QPainter &painter, int x, int y, int size);
    void drawCircle(QPainter &painter, int x, int y, int size);
    bool checkWin(int player);
    bool checkDraw();
    void endGame(int winner);
    void resetGame();
    void resetScore();

private slots:
    void resetGameClicked();
    void resetScoreClicked();
    void quitClicked();
};
