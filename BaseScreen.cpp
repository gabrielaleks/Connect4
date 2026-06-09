#include "BaseScreen.h"

BaseScreen::BaseScreen(QWidget* parent) : QWidget(parent) {}

void BaseScreen::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), QColor(SCREEN_R, SCREEN_G, SCREEN_B));
}
