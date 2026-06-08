#include "StartScreen.h"


StartScreen::StartScreen(QWidget* parent) : BaseScreen(parent) {
    layout = new QVBoxLayout(this);

    logo = new QSvgWidget(":/assets/logo.svg");
    QSize originalSize = logo->renderer()->defaultSize();
    logo->setFixedSize(originalSize * 0.8);

    QFont font("Verdana");
    startButton = new QPushButton("Start", this);
    startButton->setFixedSize(100, 50);
    font.setPixelSize(20);
    font.setBold(false);
    startButton->setFont(font);
    startButton->setStyleSheet("background-color: rgb(249, 234, 164); color: rgb(71, 0, 2);");

    layout->addStretch();
    layout->addWidget(logo, 0, Qt::AlignCenter);
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(
        startButton,
        &QPushButton::clicked,
        this,
        &StartScreen::startButtonClicked
    );
}