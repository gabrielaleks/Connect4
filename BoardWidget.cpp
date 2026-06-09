#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent) {
    setMouseTracking(true);
}

void BoardWidget::setGameState(
    CellState gameState[ROW_COUNT][COLUMN_COUNT]
) {
    std::memcpy(_gameState, gameState, sizeof(_gameState));
}

void BoardWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (_hoveredColumn > -1) {
        int clickedX = event->pos().x();
        int selectedColumn = (clickedX - getGridMetrics().startX) / getGridMetrics().cellSize;

        emit columnSelected(selectedColumn);
    }
}

void BoardWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    auto gridSize = getGridMetrics().gridSize;
    auto cellSize = getGridMetrics().cellSize;
    auto startX = getGridMetrics().startX;
    auto startY = getGridMetrics().startY;

    for (size_t i = 0; i < ROW_COUNT; i++) {
        for (size_t j = 0; j < COLUMN_COUNT; j++) {
            painter.setPen(QPen(Qt::black, 2));

            if (_gameState[i][j] == CellState::Empty) {
                painter.setBrush(EMPTY_CELL_COLOR);
            }

            if (_gameState[i][j] == CellState::Player1) {
                painter.setBrush(colorValues.at(_player1Color));
            }

            if (_gameState[i][j] == CellState::Player2) {
                painter.setBrush(colorValues.at(_player2Color));
            }

            painter.drawEllipse(
                (cellSize * j) + MARGIN_SIZE + startX,
                (cellSize * i) + MARGIN_SIZE + startY,
                cellSize - MARGIN_SIZE * 2,
                cellSize - MARGIN_SIZE * 2
            );
        }
    }

    if (_hoveredColumn > -1 && !_isGameOver) {
        int columnCenter =  (getGridMetrics().cellSize * (_hoveredColumn + 1)) + (MARGIN_SIZE * 4);

        int arrowY = getGridMetrics().startY - 4 * MARGIN_SIZE;
        int arrowSize = 15;

        QPointF tip(columnCenter, arrowY + arrowSize);
        QPointF topLeft(columnCenter - arrowSize, arrowY);
        QPointF topRight(columnCenter + arrowSize, arrowY);

        painter.setBrush(
            colorValues.at(_activePlayerIndex == 1 ? _player1Color : _player2Color)
        );
        painter.drawPolygon(QPolygonF() << topLeft << topRight << tip);
    }
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event) {
    auto mouseXPosition = event->pos().x();
    int newColumn = (mouseXPosition - getGridMetrics().startX) / getGridMetrics().cellSize;

    if (
        mouseXPosition < getGridMetrics().startX + MARGIN_SIZE ||
        mouseXPosition > getGridMetrics().endX - MARGIN_SIZE
        ) {
        newColumn = -1;
    }


    if (newColumn != _hoveredColumn) {
        _hoveredColumn = newColumn;
        update();
    }
}

BoardWidget::GridMetrics BoardWidget::getGridMetrics() const {
    GridMetrics gridMetrics;

    gridMetrics.gridSize = width() * 0.80;
    gridMetrics.cellSize = gridMetrics.gridSize / COLUMN_COUNT;
    gridMetrics.startX = (width() - gridMetrics.gridSize) / 2;
    gridMetrics.endX = width() - gridMetrics.startX;
    gridMetrics.startY = (height() - gridMetrics.cellSize * ROW_COUNT) / 2;

    return gridMetrics;
}

void BoardWidget::setActivePlayerIndex(int index) {
    _activePlayerIndex = index;
}

void BoardWidget::setPlayer1Color(Color color) {
    _player1Color = color;
}

void BoardWidget::setPlayer2Color(Color color) {
    _player2Color = color;
}

void BoardWidget::setGameOver(bool isGameOver) {
    _isGameOver = isGameOver;
}