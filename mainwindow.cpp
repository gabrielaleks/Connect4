#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
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
    setWindowTitle("Connect4");

    connect(
        startScreen,
        &StartScreen::startButtonClicked,
        this,
        &MainWindow::showConfigScreen);

    connect(
        configScreen,
        &ConfigScreen::playButtonClicked,
        this,
        &MainWindow::showGameScreen);

    connect(
        configScreen,
        &ConfigScreen::onlinePlayButtonClicked,
        this,
        &MainWindow::showOnlineGameScreen);

    connect(
        gameScreen,
        &GameScreen::configButtonClicked,
        this,
        &MainWindow::showConfigScreen);
}

MainWindow::~MainWindow() = default;

void MainWindow::showConfigScreen() {
    delete _networkClient;
    _networkClient = nullptr;
    gameScreen->setNetworkClient(nullptr, 0);
    stack->setCurrentWidget(configScreen);
}

void MainWindow::showGameScreen(
    QString player1Name,
    Color player1Color,
    QString player2Name,
    Color player2Color) {
    gameScreen->setNetworkClient(nullptr, 0);
    gameScreen->reset();
    gameScreen->setPlayer1(player1Name.toStdString(), player1Color);
    gameScreen->setPlayer2(player2Name.toStdString(), player2Color);
    gameScreen->setActivePlayer(gameScreen->getPlayer1());

    stack->setCurrentWidget(gameScreen);
}

void MainWindow::showOnlineGameScreen(
    QString player1Name,
    Color player1Color,
    QString player2Name,
    Color player2Color,
    QString serverIp,
    int localPlayerIndex) {
    delete _networkClient;
    _networkClient = new NetworkClient(serverIp, 12345, localPlayerIndex, this);

    connect(_networkClient, &NetworkClient::errorOccurred, this, [this](const QString& msg) {
        QMessageBox::warning(this, "Network error", msg);
    });

    gameScreen->reset();
    gameScreen->setPlayer1(player1Name.toStdString(), player1Color);
    gameScreen->setPlayer2(player2Name.toStdString(), player2Color);
    gameScreen->setNetworkClient(_networkClient, localPlayerIndex);
    gameScreen->setActivePlayer(gameScreen->getPlayer1());

    stack->setCurrentWidget(gameScreen);
}