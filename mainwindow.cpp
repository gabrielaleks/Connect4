#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget();

    layout = new QVBoxLayout(centralWidget);

    stack = new QStackedWidget();

    author = new QLabel("Developed by Gabriel Aleksandravicius", this);
    author->setAlignment(Qt::AlignCenter);
    QFont font("Verdana");
    font.setPixelSize(10);
    font.setBold(false);
    author->setFont(font);

    startScreen = new StartScreen();
    configScreen = new ConfigScreen();
    gameScreen = new GameScreen();

    stack->addWidget(startScreen);
    stack->addWidget(configScreen);
    stack->addWidget(gameScreen);


    stack->setCurrentWidget(startScreen);

    layout->addWidget(stack);
    layout->addWidget(author);

    setCentralWidget(centralWidget);

    resize(SCREEN_SIZE, SCREEN_SIZE);
    setFixedSize(size());
    setWindowTitle("Connect4");

    connect(
        startScreen,
        &StartScreen::startButtonClicked,
        this,
        &MainWindow::showConfigScreen
    );

    connect(
        configScreen,
        &ConfigScreen::playButtonClicked,
        this,
        &MainWindow::showGameScreen
    );
}

MainWindow::~MainWindow() = default;

void MainWindow::showConfigScreen() {
    stack->setCurrentWidget(configScreen);
}

void MainWindow::showGameScreen(
    QString player1Name,
    Color player1Color,
    QString player2Name,
    Color player2Color
) {
    gameScreen->setPlayer1(player1Name.toStdString(), player1Color);
    gameScreen->setPlayer2(player2Name.toStdString(), player2Color);
    gameScreen->setActivePlayer(gameScreen->getPlayer1());

    stack->setCurrentWidget(gameScreen);
}


/** Requirements
 * - Players annouce themselves at the start of the game
 * - Each player gets a color
 * - Players alternate their turns
 * - The state of the game must be displayed by the UI
 * - The program must determine the winner
 * - The game must also be playable online
 *
 * Extras:
 * - Button to restart game (with confirmation)
 * - Timer
 * - The game can be saved and replayed later
*/