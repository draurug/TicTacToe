#include "Scene.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

Scene::Scene(QWidget *parent) : QWidget(parent)
{
   // setFixedSize(300, 350);

    // Initialize game m_grid
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_grid[i][j] = 0; // 0 - empty, 1 - X, 2 - O
        }
    }

    currentPlayer = 1; // Player X starts
    gameActive = true;
    scoreX = 0;
    scoreO = 0;

}

void Scene::positionChanged(QVector<int> vector)
{
    for( int i = 0; i < 3; i++)
    {
        for( int j= 0; j < 3; j++)
        {
            m_grid[i][j] = vector[i*3 + j];
        }
    }
    emit update();
}


void Scene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);

    // Draw m_grid lines
    for (int i = 1; i < 3; ++i) {
        painter.drawLine(0, i * height() / 3, width(), i * height() / 3);
        painter.drawLine(i * width() / 3, 0, i * width() / 3, height());
    }

    // Draw crosses and circles
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (m_grid[i][j] == 1) {
                drawCross(painter, j * width() / 3, i * height() / 3, width() / 3);
            } else if (m_grid[i][j] == 2) {
                drawCircle(painter, j * width() / 3, i * height() / 3, width() / 3);
            }
        }
    }
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    if (!gameActive) return;

    int cellSize = width() / 3;
    int row = event->y() / cellSize;
    int col = event->x() / cellSize;

    if (row >= 0 && row < 3 && col >= 0 && col < 3)
    {
        emit onClick(row, col, 1);

        // if (m_grid[row][col] == 0)
            // {
        //     m_grid[row][col] = currentPlayer;
        //     update();

        //     if (checkWin(currentPlayer)) {
        //         endGame(currentPlayer);
        //     } else if (checkDraw()) {
        //         endGame(0); // Draw
        //     }
        //     currentPlayer = (currentPlayer == 1) ? 2 : 1;
        //  }
    }
}

void Scene::drawCross(QPainter &painter, int x, int y, int size)
{
    painter.drawLine(x + 10, y + 10, x + size - 10, y + size - 10);
    painter.drawLine(x + size - 10, y + 10, x + 10, y + size - 10);
}

void Scene::drawCircle(QPainter &painter, int x, int y, int size)
{
    painter.drawEllipse(x + 10, y + 10, size - 20, size - 20);
}

bool Scene::checkWin(int player)
{
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (m_grid[i][0] == player && m_grid[i][1] == player && m_grid[i][2] == player)
            return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (m_grid[0][i] == player && m_grid[1][i] == player && m_grid[2][i] == player)
            return true;
    }
    // Check diagonals
    if (m_grid[0][0] == player && m_grid[1][1] == player && m_grid[2][2] == player)
        return true;
    if (m_grid[0][2] == player && m_grid[1][1] == player && m_grid[2][0] == player)
        return true;

    return false;
}

bool Scene::checkDraw()
{
    // Check for draw
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (m_grid[i][j] == 0)
                return false;
        }
    }

    return true;
}

void Scene::endGame(int winner)
{
    gameActive = false;

    QString message;
    if (winner == 1) {
        message = "Player X wins!";
        scoreX++;
    } else if (winner == 2) {
        message = "Player O wins!";
        scoreO++;
    } else {
        message = "It's a draw!";
    }

    scoreLabel->setText("Score - X: " + QString::number(scoreX) + "  O: " + QString::number(scoreO));

    QMessageBox::information(this, "Game Result", message);
}

void Scene::resetGame()
{
    gameActive = true;
    currentPlayer = 1;

    // Reset game m_grid
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_grid[i][j] = 0;
        }
    }

    update();
}

void Scene::resetScore()
{
    scoreX = 0;
    scoreO = 0;

    scoreLabel->setText("Score - X: 0  O: 0");
    resetGame();
}

void Scene::resetGameClicked()
{
    resetGame();
}

void Scene::resetScoreClicked()
{
    resetScore();
}

void Scene::quitClicked()
{
    QApplication::quit();
}
