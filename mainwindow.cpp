#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    _centralWidget = new QWidget();

    _layout = new QVBoxLayout(_centralWidget);

    _stack = new QStackedWidget();

    _author = new QLabel("Developed by Gabriel Aleksandravicius", this);
    _author->setAlignment(Qt::AlignCenter);
    QFont font("Verdana");
    font.setPixelSize(10);
    font.setBold(false);
    _author->setFont(font);

    _startScreen = new StartScreen();
    _configScreen = new ConfigScreen();
    _gameScreen = new GameScreen();

    _stack->addWidget(_startScreen);
    _stack->addWidget(_configScreen);
    _stack->addWidget(_gameScreen);

    _stack->setCurrentWidget(_startScreen);

    _layout->addWidget(_stack);
    _layout->addWidget(_author);

    setCentralWidget(_centralWidget);

    resize(SCREEN_SIZE, SCREEN_SIZE);
    setWindowTitle("Connect4");

    connect(
        _startScreen,
        &StartScreen::startButtonClicked,
        this,
        &MainWindow::showConfigScreen);

    connect(
        _configScreen,
        &ConfigScreen::playButtonClicked,
        this,
        &MainWindow::showGameScreen);

    connect(
        _configScreen,
        &ConfigScreen::onlinePlayButtonClicked,
        this,
        &MainWindow::showOnlineGameScreen);

    connect(
        _gameScreen,
        &GameScreen::configButtonClicked,
        this,
        &MainWindow::showConfigScreen);
}

MainWindow::~MainWindow() = default;

void MainWindow::showConfigScreen() {
    delete _networkClient;
    _networkClient = nullptr;
    _gameScreen->setNetworkClient(nullptr, 0);
    _stack->setCurrentWidget(_configScreen);
}

void MainWindow::showGameScreen(
    QString player1Name,
    Color player1Color,
    QString player2Name,
    Color player2Color) {
    _gameScreen->setNetworkClient(nullptr, 0);
    _gameScreen->reset();
    _gameScreen->setPlayer1(player1Name.toStdString(), player1Color);
    _gameScreen->setPlayer2(player2Name.toStdString(), player2Color);
    _gameScreen->setActivePlayer(_gameScreen->getPlayer1());

    _stack->setCurrentWidget(_gameScreen);
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

    _gameScreen->reset();
    _gameScreen->setPlayer1(player1Name.toStdString(), player1Color);
    _gameScreen->setPlayer2(player2Name.toStdString(), player2Color);
    _gameScreen->setNetworkClient(_networkClient, localPlayerIndex);
    _gameScreen->setActivePlayer(_gameScreen->getPlayer1());

    _stack->setCurrentWidget(_gameScreen);
}