#include "ConfigScreen.h"

ConfigScreen::ConfigScreen(QWidget* parent) : BaseScreen(parent) {
    layout = new QVBoxLayout(this);
    configLabel = new QLabel("Game configuration", this);
    configLabel->setAlignment(Qt::AlignCenter);
    QFont font("Verdana");
    font.setPixelSize(20);
    font.setBold(true);
    configLabel->setFont(font);
    configLabel->setStyleSheet("color: rgb(249, 234, 164);");

    font.setPixelSize(15);
    font.setBold(false);

    PlayerSection p1 = createPlayerSection("Player 1", Color::Red, font);
    player1Label = p1.label;
    player1HorizontalLayout = p1.horizontalLayout;
    player1NameField = p1.nameField;
    player1ColorDropdown = p1.colorDropdown;

    PlayerSection p2 = createPlayerSection("Player 2", Color::Yellow, font);
    player2Label = p2.label;
    player2HorizontalLayout = p2.horizontalLayout;
    player2NameField = p2.nameField;
    player2ColorDropdown = p2.colorDropdown;

    // Play button
    playButton = new QPushButton("Play", this);
    playButton->setFixedSize(80, 40);
    playButton->setEnabled(false);
    playButton->setStyleSheet("background-color: rgb(200, 190, 140); color: rgb(150, 80, 82);");

    connect(
        player1NameField,
        &QLineEdit::textChanged,
        this,
        &ConfigScreen::checkIfEmpty
    );

    connect(
        player2NameField,
        &QLineEdit::textChanged,
        this,
        &ConfigScreen::checkIfEmpty
    );

    player1PrevColorIndex = player1ColorDropdown->currentIndex();
    player2PrevColorIndex = player2ColorDropdown->currentIndex();
    setItemEnabled(player2ColorDropdown, player1PrevColorIndex, false);
    setItemEnabled(player1ColorDropdown, player2PrevColorIndex, false);

    connect(player1ColorDropdown, &QComboBox::currentIndexChanged, this, &ConfigScreen::makeChosenColorsReadOnly);
    connect(player2ColorDropdown, &QComboBox::currentIndexChanged, this, &ConfigScreen::makeChosenColorsReadOnly);

    // Layout config
    layout->addStretch(1);
    layout->addWidget(configLabel);
    layout->addStretch(1);
    layout->addWidget(player1Label);
    layout->addLayout(player1HorizontalLayout);
    layout->addWidget(player2Label);
    layout->addLayout(player2HorizontalLayout);
    layout->addWidget(playButton, 0, Qt::AlignCenter);
    layout->addStretch(2);

    connect(
        playButton,
        &QPushButton::clicked,
        this,
        &ConfigScreen::onPlayButtonClicked
    );

    player1NameField->setText("Player 1");
    player2NameField->setText("Player 2");
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
    emit playButtonClicked(
        player1NameField->text(),
        static_cast<Color>(player1ColorDropdown->currentData().toInt()),
        player2NameField->text(),
        static_cast<Color>(player2ColorDropdown->currentData().toInt())
    );
}

void ConfigScreen::checkIfEmpty() {
    if (
        player1NameField->text().trimmed() == "" ||
        player2NameField->text().trimmed() == ""
    ) {
        playButton->setEnabled(false);
        playButton->setStyleSheet("background-color: rgb(200, 190, 140); color: rgb(150, 80, 82);");
    } else {
        playButton->setEnabled(true);
        playButton->setStyleSheet("background-color: rgb(249, 234, 164); color: rgb(71, 0, 2);");
    }
}

void ConfigScreen::makeChosenColorsReadOnly() {
    QComboBox* changed = qobject_cast<QComboBox*>(sender());
    QComboBox* other;
    int* prevIndex;

    if (changed == player1ColorDropdown) {
        other = player2ColorDropdown;
        prevIndex = &player1PrevColorIndex;
    } else {
        other = player1ColorDropdown;
        prevIndex = &player2PrevColorIndex;
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