#include "BaseScreen.h"

BaseScreen::BaseScreen(QWidget* parent) : QWidget(parent) {}

void BaseScreen::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), QColor(95, 133, 255));
}
