#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QVBoxLayout>
#include <QtSvgWidgets/QSvgWidget>
#include <QtSvg/QSvgRenderer>
#include <QPushButton>
#include "BaseScreen.h"

class StartScreen : public BaseScreen {
    Q_OBJECT

public:
    explicit StartScreen(QWidget* parent = nullptr);

private:
    QVBoxLayout* _layout;
    QSvgWidget* _logo;
    QPushButton* _startButton;

signals:
    void startButtonClicked();
};

#endif // STARTSCREEN_H