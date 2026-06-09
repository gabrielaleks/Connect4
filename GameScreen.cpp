#include "GameScreen.h"
#include <QString>

GameScreen::GameScreen(QWidget* parent) : BaseScreen(parent) {
    layout = new QVBoxLayout(this);

    boardWidget = new BoardWidget(this);
    boardWidget->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    layout->addSpacing(TOP_AREA_HEIGHT);
    layout->addWidget(boardWidget);

    connect(
        boardWidget,
        &BoardWidget::columnSelected,
        this,
        &GameScreen::handleColumnSelection
    );
}

void GameScreen::handleColumnSelection(int selectedColumn) {
    if (_gameOver) return;

    int selectedRow = -1;

    for (int i = ROW_COUNT - 1; i >= 0; i--) {
        if (_gameState[i][selectedColumn] == CellState::Empty) {
            _gameState[i][selectedColumn] = _activePlayer.index == 1
                ? CellState::Player1
                : CellState::Player2;
            selectedRow = i;
            break;
        }
    }

    if (selectedRow == -1) {
        return;
    }

    _piecesPlacedCounter++;

    bool isWinner = GameScreen::isWinner(selectedRow, selectedColumn);

    if (isWinner) {
        updateTopText(QString::fromStdString(_activePlayer.name) + " won the game!");
        _gameOver = true;
        boardWidget->setGameOver(true);
    } else if (_piecesPlacedCounter == ROW_COUNT * COLUMN_COUNT) {
        updateTopText("It was a draw", Color::White);
        _gameOver = true;
        boardWidget->setGameOver(true);
    } else {
        setActivePlayer(_activePlayer.index == 1 ? _player2 : _player1);
    }

    boardWidget->setGameState(_gameState);
    boardWidget->update();
}

bool GameScreen::isWinner(int row, int column) {
    auto playerState = _activePlayer.index == 1 ? CellState::Player1 : CellState::Player2;

    int horizontal = countConsecutive(row, column, 0, -1, playerState) + countConsecutive(row, column, 0, 1, playerState);
    int vertical = countConsecutive(row, column, 1, 0, playerState);
    int diagonalRight = countConsecutive(row, column, -1, -1, playerState) + countConsecutive(row, column, 1, 1, playerState);
    int diagonalLeft = countConsecutive(row, column, 1, -1, playerState) + countConsecutive(row, column, -1, 1, playerState);

    bool won = (1 + horizontal >= 4) ||
               (1 + vertical >= 4)   ||
               (1 + diagonalRight >= 4) ||
               (1 + diagonalLeft >= 4);

    return won;
}

int GameScreen::countConsecutive(
    int row,
    int col,
    int rowDir,
    int colDir,
    CellState playerState
) {
    int count = 0;
    int r = row + rowDir;
    int c = col + colDir;

    while (r >= 0 && r < ROW_COUNT && c >= 0 && c < COLUMN_COUNT) {
        if (_gameState[r][c] == playerState) {
            count++;
            r += rowDir;
            c += colDir;
        } else {
            break;
        }
    }

    return count;
}

void GameScreen::setPlayer1(
    std::string name,
    Color color
) {
    _player1.index = 1;
    _player1.name = name;
    _player1.color = color;
    boardWidget->setPlayer1Color(color);
}

void GameScreen::setPlayer2(
    std::string name,
    Color color
) {
    _player2.index = 2;
    _player2.name = name;
    _player2.color = color;
    boardWidget->setPlayer2Color(color);
}

GameScreen::Player GameScreen::getPlayer1() {
    return _player1;
}

GameScreen::Player GameScreen::getPlayer2() {
    return _player2;
}

void GameScreen::setActivePlayer(GameScreen::Player activePlayer) {
    _activePlayer = activePlayer;
    GameScreen::updateTopText(QString::fromStdString(_activePlayer.name) + "'s turn");
    boardWidget->setActivePlayerIndex(activePlayer.index);
}

void GameScreen::updateTopText(QString text, std::optional<Color> color) {
    _topText = text;

    if (color.has_value()) {
        _topColor = colorValues.at(color.value());
    } else {
        _topColor = colorValues.at(_activePlayer.color);
    }

    update();
}

void GameScreen::paintEvent(QPaintEvent* event) {
    BaseScreen::paintEvent(event);

    if (_topText.isEmpty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font("Verdana");
    font.setPixelSize(24);
    font.setBold(true);

    QPainterPath path;
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(_topText);
    int x = (width() - textWidth) / 2;
    int y = TOP_AREA_HEIGHT / 2 + fm.ascent() / 2;
    path.addText(x, y, font, _topText);

    painter.setPen(QPen(Qt::black, 3));
    painter.strokePath(path, painter.pen());
    painter.setPen(Qt::NoPen);
    painter.fillPath(path, _topColor);
}