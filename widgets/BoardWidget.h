#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "Color.h"
#include "BoardConfig.h"

#define MARGIN_SIZE 5

class BoardWidget : public QWidget {
    Q_OBJECT

struct GridMetrics {
    float gridSize;
    float cellSize;
    float startX;
    float endX;
    float startY;
};

public:
    explicit BoardWidget(QWidget* parent = nullptr);
    GridMetrics getGridMetrics() const;
    void setActivePlayerIndex(int index);
    void setPlayer1Color(Color color);
    void setPlayer2Color(Color color);
    void setGameState(CellState gameState[ROW_COUNT][COLUMN_COUNT]);
    void setGameOver(bool isGameOver);

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    bool _isGameOver = false;
    int _hoveredColumn = -1;
    int _activePlayerIndex = 0;
    Color _player1Color;
    Color _player2Color;
    CellState _gameState[ROW_COUNT][COLUMN_COUNT] = {{CellState::Empty}};

signals:
    void columnSelected(int selectedColumn);
};

#endif // BOARDWIDGET_H
