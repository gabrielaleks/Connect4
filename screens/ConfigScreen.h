#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include "BaseScreen.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QStandardItemModel>
#include "Color.h"

class ConfigScreen : public BaseScreen {
    Q_OBJECT

public:
    explicit ConfigScreen(QWidget* parent = nullptr);

private:
    QVBoxLayout* layout;
    QLabel* configLabel;

    QHBoxLayout* player1HorizontalLayout;
    QLabel* player1Label;
    QLineEdit* player1NameField;
    QComboBox* player1ColorDropdown;

    QHBoxLayout* player2HorizontalLayout;
    QLabel* player2Label;
    QLineEdit* player2NameField;
    QComboBox* player2ColorDropdown;

    QPushButton* playButton;

    QCheckBox* _onlineModeCheckbox;
    QWidget*   _onlineOptionsWidget;
    QLineEdit* _serverIpField;
    QComboBox* _roleDropdown;

    int player1PrevColorIndex;
    int player2PrevColorIndex;

    struct PlayerSection {
        QLabel* label;
        QHBoxLayout* horizontalLayout;
        QLineEdit* nameField;
        QComboBox* colorDropdown;
    };

    PlayerSection createPlayerSection(const QString& labelText, Color defaultColor, const QFont& font);
    void setItemEnabled(QComboBox* combo, int index, bool enabled);

private slots:
    void checkIfEmpty();
    void makeChosenColorsReadOnly();
    void onPlayButtonClicked();
    void onOnlineModeToggled(bool checked);

signals:
    void playButtonClicked(
        QString player1Name,
        Color player1Color,
        QString player2Name,
        Color player2Color
    );
    void onlinePlayButtonClicked(
        QString player1Name,
        Color player1Color,
        QString player2Name,
        Color player2Color,
        QString serverIp,
        int localPlayerIndex
    );
};

#endif