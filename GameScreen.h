#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QLabel>
#include <QPushButton>
#include "BaseScreen.h"
#include "Color.h"

#define MARGIN_SIZE 5
#define ROW_COUNT 6
#define COLUMN_COUNT 7

class GameScreen : public BaseScreen {
    Q_OBJECT

public:
    explicit GameScreen(QWidget* parent = nullptr);

    void setPlayer1Name(std::string player1Name);
    void setPlayer1Color(Color player1Color);
    void setPlayer2Name(std::string player2Name);
    void setPlayer2Color(Color player2Color);

private:
    void paintEvent(QPaintEvent* event) override;

    std::string _player1Name;
    Color _player1Color;
    std::string _player2Name;
    Color _player2Color;

signals:
    void configButtonClicked();
};

#endif // GAMESCREEN_H
