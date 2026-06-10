#ifndef BASESCREEN_H
#define BASESCREEN_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#define SCREEN_SIZE 500
#define SCREEN_R 95
#define SCREEN_G 133
#define SCREEN_B 255

class BaseScreen : public QWidget {
    Q_OBJECT

public:
    explicit BaseScreen(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // BASESCREEN_H
