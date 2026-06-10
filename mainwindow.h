#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "StartScreen.h"
#include "ConfigScreen.h"
#include "GameScreen.h"
#include "NetworkClient.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QStackedWidget* stack;

    StartScreen* startScreen;
    ConfigScreen* configScreen;
    GameScreen* gameScreen;
    QLabel* author;
    NetworkClient* _networkClient = nullptr;

private slots:
    void showConfigScreen();
    void showGameScreen(
        QString player1Name,
        Color player1Color,
        QString player2Name,
        Color player2Color
    );
    void showOnlineGameScreen(
        QString player1Name,
        Color player1Color,
        QString player2Name,
        Color player2Color,
        QString serverIp,
        int localPlayerIndex
    );
};

#endif // MAINWINDOW_H
