#include "GameScreen.h"
#include <QString>
#include <QMessageBox>

GameScreen::GameScreen(QWidget* parent) : BaseScreen(parent) {
    _layout = new QVBoxLayout(this);

    _boardWidget = new BoardWidget(this);
    _boardWidget->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    _resetButton = new QPushButton("Reset", this);
    _resetButton->setFixedSize(60, 30);
    _resetButton->setStyleSheet("background-color: rgb(200, 190, 140); color: rgb(150, 80, 82);");

    _goBackToConfigButton = new QPushButton("Go to config", this);
    _goBackToConfigButton->setFixedSize(100, 30);
    _goBackToConfigButton->setStyleSheet("background-color: rgb(200, 190, 140); color: rgb(150, 80, 82);");

    _layout->addSpacing(TOP_AREA_HEIGHT);
    _layout->addWidget(_boardWidget);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(_resetButton);
    buttonsLayout->addWidget(_goBackToConfigButton);
    buttonsLayout->addStretch();
    _layout->addLayout(buttonsLayout);

    connect(
        _boardWidget,
        &BoardWidget::columnSelected,
        this,
        [this](int col) { handleColumnSelection(col, false); }
    );

    connect(
        _resetButton,
        &QPushButton::clicked,
        this,
        &GameScreen::onResetButtonClicked
    );

    connect(
        _goBackToConfigButton,
        &QPushButton::clicked,
        this,
        &GameScreen::configButtonClicked
    );
}

void GameScreen::handleRemoteMove(int column) {
    handleColumnSelection(column, true);
}

void GameScreen::setNetworkClient(NetworkClient* client, int localPlayerIndex) {
    _networkClient = client;
    _localPlayerIndex = localPlayerIndex;
    if (_networkClient)
        connect(_networkClient, &NetworkClient::moveReceived, this, &GameScreen::handleRemoteMove);
}

void GameScreen::handleColumnSelection(int selectedColumn, bool fromNetwork) {
    if (_gameOver) return;

    if (_networkClient && !fromNetwork && _activePlayer.index != _localPlayerIndex)
        return;

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

    if (!fromNetwork && _networkClient)
        _networkClient->sendMove(selectedColumn);

    _piecesPlacedCounter++;

    bool isWinner = GameScreen::isWinner(selectedRow, selectedColumn);

    if (isWinner) {
        updateTopText(QString::fromStdString(_activePlayer.name) + " won the game!");
        _gameOver = true;
        _boardWidget->setGameOver(true);
    } else if (_piecesPlacedCounter == ROW_COUNT * COLUMN_COUNT) {
        updateTopText("It was a draw", Color::White);
        _gameOver = true;
        _boardWidget->setGameOver(true);
    } else {
        setActivePlayer(_activePlayer.index == 1 ? _player2 : _player1);
    }

    _boardWidget->setGameState(_gameState);
    _boardWidget->update();
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
    _boardWidget->setPlayer1Color(color);
}

void GameScreen::setPlayer2(
    std::string name,
    Color color
) {
    _player2.index = 2;
    _player2.name = name;
    _player2.color = color;
    _boardWidget->setPlayer2Color(color);
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
    _boardWidget->setActivePlayerIndex(activePlayer.index);
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

void GameScreen::onResetButtonClicked() {
    if (!_gameOver) {
        auto response = QMessageBox::question(
            this,
            "Reset game",
            "Are you sure you want to reset the game?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (response != QMessageBox::Yes) {
            return;
        }
    }

    reset();
    setActivePlayer(_player1);
}

void GameScreen::reset() {
    memset(_gameState, CellState::Empty, sizeof(_gameState));
    _gameOver = false;
    _piecesPlacedCounter = 0;
    _boardWidget->setGameOver(false);
    _boardWidget->setGameState(_gameState);
    _boardWidget->update();
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