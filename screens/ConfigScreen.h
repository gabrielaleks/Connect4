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
    QVBoxLayout* _layout;
    QLabel* _configLabel;

    QHBoxLayout* _player1HorizontalLayout;
    QLabel* _player1Label;
    QLineEdit* _player1NameField;
    QComboBox* _player1ColorDropdown;

    QHBoxLayout* _player2HorizontalLayout;
    QLabel* _player2Label;
    QLineEdit* _player2NameField;
    QComboBox* _player2ColorDropdown;

    QPushButton* _playButton;

    QCheckBox* _onlineModeCheckbox;
    QWidget*   _onlineOptionsWidget;
    QLineEdit* _serverIpField;
    QComboBox* _roleDropdown;

    int _player1PrevColorIndex;
    int _player2PrevColorIndex;

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