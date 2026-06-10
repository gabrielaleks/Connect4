#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include "BaseScreen.h"
#include "BoardWidget.h"
#include "NetworkClient.h"
#include "Color.h"

#define TOP_AREA_HEIGHT 30

class GameScreen : public BaseScreen {
    Q_OBJECT

private:
    void paintEvent(QPaintEvent* event) override;
    bool isWinner(int row, int column);
    int countConsecutive(
        int row,
        int col,
        int rowDir,
        int colDir,
        CellState playerState
    );

    BoardWidget* boardWidget;
    QVBoxLayout* layout;

    QString _topText;
    QColor _topColor;

    struct Player {
        int index;
        std::string name;
        Color color;
    };

    Player _player1;
    Player _player2;
    Player _activePlayer;
    CellState _gameState[ROW_COUNT][COLUMN_COUNT] = {{CellState::Empty}};
    bool _gameOver = false;
    int _piecesPlacedCounter = 0;
    QPushButton* _resetButton;
    QPushButton* _goBackToConfigButton;

    NetworkClient* _networkClient = nullptr;
    int _localPlayerIndex = 0;

public:
    explicit GameScreen(QWidget* parent = nullptr);

    void setPlayer1(std::string name, Color color);
    void setPlayer2(std::string name, Color color);
    Player getPlayer1();
    Player getPlayer2();
    void setActivePlayer(Player activePlayer);
    void updateTopText(QString text, std::optional<Color> color = std::nullopt);
    void reset();
    void setNetworkClient(NetworkClient* client, int localPlayerIndex);

private slots:
    void handleColumnSelection(int selectedColumn, bool fromNetwork = false);
    void handleRemoteMove(int column);
    void onResetButtonClicked();

signals:
    void configButtonClicked();
};

#endif // GAMESCREEN_H
