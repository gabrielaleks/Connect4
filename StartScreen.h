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
    QVBoxLayout* layout;
    QSvgWidget* logo;
    QPushButton* startButton;

signals:
    void startButtonClicked();
};

#endif // STARTSCREEN_H