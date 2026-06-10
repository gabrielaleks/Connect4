#include "StartScreen.h"


StartScreen::StartScreen(QWidget* parent) : BaseScreen(parent) {
    _layout = new QVBoxLayout(this);

    _logo = new QSvgWidget(":/assets/logo.svg");
    QSize originalSize = _logo->renderer()->defaultSize();
    _logo->setFixedSize(originalSize * 0.8);

    QFont font("Verdana");
    _startButton = new QPushButton("Start", this);
    _startButton->setFixedSize(100, 50);
    font.setPixelSize(20);
    font.setBold(false);
    _startButton->setFont(font);
    _startButton->setStyleSheet("background-color: rgb(249, 234, 164); color: rgb(71, 0, 2);");

    _layout->addStretch();
    _layout->addWidget(_logo, 0, Qt::AlignCenter);
    _layout->addWidget(_startButton, 0, Qt::AlignCenter);
    _layout->addStretch();

    connect(
        _startButton,
        &QPushButton::clicked,
        this,
        &StartScreen::startButtonClicked
    );
}