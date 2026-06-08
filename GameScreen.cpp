#include "GameScreen.h"

GameScreen::GameScreen(QWidget* parent) : BaseScreen(parent) {
}

void GameScreen::paintEvent(QPaintEvent* event) {
    BaseScreen::paintEvent(event);
    QPainter painter(this);

    int margin = MARGIN_SIZE;
    float gridSize = width() * 0.80;
    float cellSize = gridSize / COLUMN_COUNT;
    float startX = (width() - gridSize) / 2;
    float startY = (height() - cellSize * ROW_COUNT) / 2;

    painter.setBrush(Qt::white);
    for (size_t i = 0; i < ROW_COUNT; i++) {
        for (size_t j = 0; j < COLUMN_COUNT; j++) {
            painter.drawEllipse(
                (cellSize * j) + margin + startX,
                (cellSize * i) + margin + startY,
                cellSize - margin * 2,
                cellSize - margin * 2
            );
        }
    }
}

void GameScreen::setPlayer1Name(std::string player1Name) {
    _player1Name = player1Name;
    // qDebug() << "player1 name: " << _player1Name;
}

void GameScreen::setPlayer1Color(Color player1Color) {
    _player1Color = player1Color;
    // qDebug() << "player1 color: " << colors.at(_player1Color);
}

void GameScreen::setPlayer2Name(std::string player2Name) {
    _player2Name = player2Name;
    // qDebug() << "player2 name: " << _player2Name;
}

void GameScreen::setPlayer2Color(Color player2Color) {
    _player2Color = player2Color;
    // qDebug() << "player2 color: " << colors.at(_player2Color);
}
