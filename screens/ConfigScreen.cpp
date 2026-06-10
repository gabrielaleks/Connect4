#include "ConfigScreen.h"

ConfigScreen::ConfigScreen(QWidget* parent) : BaseScreen(parent) {
    _layout = new QVBoxLayout(this);
    _configLabel = new QLabel("Game configuration", this);
    _configLabel->setAlignment(Qt::AlignCenter);
    QFont font("Verdana");
    font.setPixelSize(20);
    font.setBold(true);
    _configLabel->setFont(font);
    _configLabel->setStyleSheet("color: rgb(249, 234, 164);");

    font.setPixelSize(15);
    font.setBold(false);

    PlayerSection p1 = createPlayerSection("Player 1", Color::Red, font);
    _player1Label = p1.label;
    _player1HorizontalLayout = p1.horizontalLayout;
    _player1NameField = p1.nameField;
    _player1ColorDropdown = p1.colorDropdown;

    PlayerSection p2 = createPlayerSection("Player 2", Color::Yellow, font);
    _player2Label = p2.label;
    _player2HorizontalLayout = p2.horizontalLayout;
    _player2NameField = p2.nameField;
    _player2ColorDropdown = p2.colorDropdown;

    // Online mode
    _onlineModeCheckbox = new QCheckBox("Online mode", this);
    _onlineModeCheckbox->setStyleSheet("color: rgb(249, 234, 164);");

    _onlineOptionsWidget = new QWidget(this);
    QHBoxLayout* onlineLayout = new QHBoxLayout(_onlineOptionsWidget);
    onlineLayout->setContentsMargins(0, 0, 0, 0);

    _serverIpField = new QLineEdit;
    _serverIpField->setPlaceholderText("Server IP...");
    _serverIpField->setText("127.0.0.1");
    _serverIpField->setFixedWidth(150);
    _serverIpField->setTextMargins(5, 0, 0, 0);

    _roleDropdown = new QComboBox(this);
    _roleDropdown->addItem("Player 1", 1);
    _roleDropdown->addItem("Player 2", 2);
    _roleDropdown->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    onlineLayout->addStretch();
    onlineLayout->addWidget(_serverIpField);
    onlineLayout->addWidget(_roleDropdown);
    onlineLayout->addStretch();
    _onlineOptionsWidget->setVisible(false);

    connect(_onlineModeCheckbox, &QCheckBox::toggled, this, &ConfigScreen::onOnlineModeToggled);
    connect(_serverIpField, &QLineEdit::textChanged, this, &ConfigScreen::checkIfEmpty);

    // Play button
    _playButton = new QPushButton("Play", this);
    _playButton->setFixedSize(80, 40);
    _playButton->setEnabled(false);
    _playButton->setStyleSheet("background-color: rgb(200, 190, 140); color: rgb(150, 80, 82);");

    connect(
        _player1NameField,
        &QLineEdit::textChanged,
        this,
        &ConfigScreen::checkIfEmpty
    );

    connect(
        _player2NameField,
        &QLineEdit::textChanged,
        this,
        &ConfigScreen::checkIfEmpty
    );

    _player1PrevColorIndex = _player1ColorDropdown->currentIndex();
    _player2PrevColorIndex = _player2ColorDropdown->currentIndex();
    setItemEnabled(_player2ColorDropdown, _player1PrevColorIndex, false);
    setItemEnabled(_player1ColorDropdown, _player2PrevColorIndex, false);

    connect(_player1ColorDropdown, &QComboBox::currentIndexChanged, this, &ConfigScreen::makeChosenColorsReadOnly);
    connect(_player2ColorDropdown, &QComboBox::currentIndexChanged, this, &ConfigScreen::makeChosenColorsReadOnly);

    // Layout config
    _layout->addStretch(1);
    _layout->addWidget(_configLabel);
    _layout->addStretch(1);
    _layout->addWidget(_player1Label);
    _layout->addLayout(_player1HorizontalLayout);
    _layout->addWidget(_player2Label);
    _layout->addLayout(_player2HorizontalLayout);
    _layout->addWidget(_onlineModeCheckbox, 0, Qt::AlignCenter);
    _layout->addWidget(_onlineOptionsWidget);
    _layout->addWidget(_playButton, 0, Qt::AlignCenter);
    _layout->addStretch(2);

    connect(
        _playButton,
        &QPushButton::clicked,
        this,
        &ConfigScreen::onPlayButtonClicked
    );

    _player1NameField->setText("Player 1");
    _player2NameField->setText("Player 2");
}

ConfigScreen::PlayerSection ConfigScreen::createPlayerSection(const QString& labelText, Color defaultColor, const QFont& font) {
    PlayerSection section;

    section.label = new QLabel(labelText, this);
    section.label->setAlignment(Qt::AlignCenter);
    section.label->setFont(font);
    section.label->setStyleSheet("color: rgb(249, 234, 164);");

    section.horizontalLayout = new QHBoxLayout();
    section.horizontalLayout->addStretch();
    section.horizontalLayout->setSpacing(10);

    section.nameField = new QLineEdit;
    section.nameField->setPlaceholderText("Name...");
    section.nameField->setFixedWidth(200);
    section.nameField->setTextMargins(5, 0, 0, 0);

    section.colorDropdown = new QComboBox(this);
    for (const auto& [color, name] : colors) {
        section.colorDropdown->addItem(name, static_cast<int>(color));
    }
    section.colorDropdown->setCurrentText(colors.at(defaultColor));
    section.colorDropdown->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    section.horizontalLayout->addWidget(section.nameField);
    section.horizontalLayout->addWidget(section.colorDropdown);
    section.horizontalLayout->addStretch();

    return section;
}

void ConfigScreen::onPlayButtonClicked() {
    if (_onlineModeCheckbox->isChecked()) {
        emit onlinePlayButtonClicked(
            _player1NameField->text(),
            static_cast<Color>(_player1ColorDropdown->currentData().toInt()),
            _player2NameField->text(),
            static_cast<Color>(_player2ColorDropdown->currentData().toInt()),
            _serverIpField->text(),
            _roleDropdown->currentData().toInt()
        );
    } else {
        emit playButtonClicked(
            _player1NameField->text(),
            static_cast<Color>(_player1ColorDropdown->currentData().toInt()),
            _player2NameField->text(),
            static_cast<Color>(_player2ColorDropdown->currentData().toInt())
        );
    }
}

void ConfigScreen::checkIfEmpty() {
    bool namesReady = !_player1NameField->text().trimmed().isEmpty()
                   && !_player2NameField->text().trimmed().isEmpty();
    bool onlineReady = !_onlineModeCheckbox->isChecked()
                    || !_serverIpField->text().trimmed().isEmpty();

    if (namesReady && onlineReady) {
        _playButton->setEnabled(true);
        _playButton->setStyleSheet("background-color: rgb(249, 234, 164); color: rgb(71, 0, 2);");
    } else {
        _playButton->setEnabled(false);
        _playButton->setStyleSheet("background-color: rgb(200, 190, 140); color: rgb(150, 80, 82);");
    }
}

void ConfigScreen::onOnlineModeToggled(bool checked) {
    _onlineOptionsWidget->setVisible(checked);
    checkIfEmpty();
}

void ConfigScreen::makeChosenColorsReadOnly() {
    QComboBox* changed = qobject_cast<QComboBox*>(sender());
    QComboBox* other;
    int* prevIndex;

    if (changed == _player1ColorDropdown) {
        other = _player2ColorDropdown;
        prevIndex = &_player1PrevColorIndex;
    } else {
        other = _player1ColorDropdown;
        prevIndex = &_player2PrevColorIndex;
    }

    int newIndex = changed->currentIndex();
    setItemEnabled(other, *prevIndex, true);
    setItemEnabled(other, newIndex, false);
    *prevIndex = newIndex;
}

void ConfigScreen::setItemEnabled(QComboBox* combo, int index, bool enabled) {
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(combo->model());
    QStandardItem* item = model->item(index);

    Qt::ItemFlags flags = item->flags();
    if (enabled)
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else
        flags &= ~(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setFlags(flags);
}