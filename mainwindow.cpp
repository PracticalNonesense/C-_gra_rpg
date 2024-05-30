#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->newGame->setVisible(false);
    connect(ui->trash, &QPushButton::clicked, this, &MainWindow::clearLog);


    connect(ui->history, &QPushButton::clicked, this, &MainWindow::showLocationHistory);
     connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::onQuitButtonClicked);

    locationHistories["Pyroklas Castle"] = "Pyroklas Castle is a magnificent castle in the center of Pyroklas Kingdom, usually it's a peaceful city where merchants and andveturers can rest and trade equipment. Recently though the castle is falling victim to the dragons attack...";
    locationHistories["Volcanic Mountains"] = "The Volcanic Mountains, legendary place where The Ember Lord, source of all evil resides. Surrounding area consists mostly of molten lava and heavy smoke with strong scent of sulfur";
    locationHistories["Amber Lair"] = "The Amber Lair, large cave with strong fire energy hidden within it. It is said, that in this very cave The Ember Lord fell into his slumber for thousand years, although he wasn't seen here in hundresds of years at least. ";
    locationHistories["Fire Pits"] = "The Fire Pits, outskirts of the Volcanic Mountains, not many things happen here accept for accasional appearence of flame slugs and small dragons.";
    locationHistories["Hot Caves"] = "The Hot Caves are known for their scorching heat and deadly inhabitants such as fire slimes and scorching spiders. It's best to keep distance from this place, temperatures may even reach 212F";
    locationHistories["Boiling Waters"] = "The Boiling Waters are a dangerous and hot region filled with geysers. It's not recomended to enter the water. Only creatures able to live here are the mighty Lizardmen";
    locationHistories["Treasure Coast"] = "The Treasure Coast is known for its hidden treasures and perilous waters. Legends say before the times of dragon dangerous pirates pillaged surrounding villages and took all the treasures to the cove";

    logMessage("Welcome to the Kingdom of Pyroklas adventurer! You are about to embark on an epic journey through various parts of this world. Prepare yourself for an adventure filled with dragons. Your objective is defeating dragons in order to gain more expereince and kill the source of this chaos: The Amber Lorn. It is said The Amber Lord resides in the Volcanic Mountains, before you approach him you should be well prepared or he'll dispose of you quickly. Legend says the last hero who had a chance to kill The Ember Lord had 300 mysterious points and 5 particular items in his inventory before entering The Volcanic Mountains, it might be a clue. Good luck, brave warrior!");

    game.setMainWindow(this);
    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI() {
    ui->locationLabel->setText("Location: " + QString::fromStdString(game.getCurrentLocation()));
    ui->healthLabel->setText("HP: " + QString::number(game.getPlayerHealth()));
    ui->xpLabel->setText("XP: " + QString::number(game.getPlayerXP()));
}

void MainWindow::logMessage(const QString &message) {
    ui->TextEdit->append(message);
}

void MainWindow::changeBackground(const QString &filePath) {
    QGraphicsScene *scene = new QGraphicsScene;
    QPixmap pixmap(filePath);
    scene->addPixmap(pixmap);
    ui->tlo->setScene(scene);
}

void MainWindow::updateLocationLabel(const QString &location) {
    ui->locationLabel->setText("Location: " + location);  // Ustawienie tekstu QLabel
}
void MainWindow::clearLog() {
    ui->TextEdit->clear();  // Wyczyść okno logów
}
void MainWindow::showLocationHistory() {
    QString currentLocation = ui->locationLabel->text().remove("Location: ");
    if (locationHistories.find(currentLocation) != locationHistories.end()) {
        logMessage(locationHistories[currentLocation]);
    } else {
        logMessage("No history available for this location.");
    }
}
void MainWindow::on_moveButton_clicked() {
    bool ok;
    QStringList items;
    std::vector<std::string> locations = game.getLocations(); // Pobieramy listę lokacji
    for (const auto &loc : locations) {
        items << QString::fromStdString(loc);
    }
    QString item = QInputDialog::getItem(this, "Move to", "Select location:", items, 0, false, &ok);
    if (ok && !item.isEmpty()) {
        std::string newLocation = item.toStdString();
        try {
            game.moveLocation(newLocation);
            int currentXP = game.getPlayerXP(); // Pobierz aktualną wartość doświadczenia gracza
            currentXP += 10; // Dodaj 10 XP
            game.setPlayerXP(currentXP); // Ustaw nową wartość doświadczenia gracza
            updateUI();
        } catch (const std::runtime_error &e) {
            logMessage("Error: " + QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::on_checkInventoryButton_clicked() {
    QString inventory;
    for (const auto &item : game.getInventory()) {
        inventory += QString::fromStdString(item.first) + ": " + QString::number(item.second) + "\n";
    }
    logMessage("You have in your inventory:\n" + inventory);
}

void MainWindow::on_saveGameButton_clicked() {
    QString executablePath = QCoreApplication::applicationDirPath(); // Ścieżka do katalogu, w którym znajduje się plik wykonywalny gry
    QString savesPath = executablePath + "/saves"; // Ścieżka do katalogu saves w folderze z grą

    // Upewniamy się, że katalog saves istnieje
    QDir savesDir(savesPath);
    if (!savesDir.exists()) {
        if (!savesDir.mkpath(savesPath)) {
            logMessage("Error creating saves directory.");
            return;
        }
    }

    // Ścieżka do pliku zapisu w katalogu saves
    QString fileName = savesPath + "/game.save";

    // Zapisujemy grę pod tą ścieżką
    if (game.saveGame(fileName.toStdString())) {
        logMessage("Game successfully saved to " + fileName);
    } else {
        logMessage("Error saving game to " + fileName);
    }
}

void MainWindow::on_loadGameButton_clicked() {
    QString executablePath = QCoreApplication::applicationDirPath(); // Ścieżka do katalogu, w którym znajduje się plik wykonywalny gry
    QString savesPath = executablePath + "/saves"; // Ścieżka do katalogu saves w folderze z grą

    QString fileName = QFileDialog::getOpenFileName(this, "Load Game", savesPath, "Save Files (*.save)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.exists()) {
            QMessageBox::critical(this, "Error", "The selected file does not exist.");
            return;
        }

        game.loadGame(fileName.toStdString());
        updateUI();
        logMessage("Game loaded from " + fileName);
    }
}

void MainWindow::onQuitButtonClicked()
{
    qApp->quit(); // qApp to globalny wskaźnik do aplikacji Qt
}
void MainWindow::displayGameOver() {
    clearLog();

    // Wyświetl komunikat końcowy
    logMessage("You tried your best, you used everything you could but it just wasn't enough. Your whole body is heavily wounded, with each passing second you see a puddle of blood under your feet getting bigger and bigger. You don't have any strength left in your body, everything feels cold. As the last spark of life in your eyes fades away so does the only chance for saving the kingdom. There's no one on par with The Amber Lord left, he leads the fire creatures onto Pyroklas Castle and takes it without much opposition. The whole kingdom is doomed to fire and flames. GAME OVER.");

    // Ukryj inne elementy interfejsu

    for (QPushButton* button : findChildren<QPushButton*>()) {
        if (button != ui->quitButton && button != ui->newGame) {
            button->setEnabled(false);
            button->hide();
        }
    }

    for (QGraphicsView* tlo : findChildren<QGraphicsView*>()) {
        tlo->hide();
    }

    for (QPlainTextEdit* cele : findChildren<QPlainTextEdit*>()) {
        cele->hide();
    }

    for (QLabel* etyk : findChildren<QLabel*>()) {
        etyk->hide();
    }

    // Ustaw styl tła na obraz końcowy
    setStyleSheet("QMainWindow { background-image: url(:/images/gameover.jpg); background-repeat: no-repeat;}");

    ui->newGame->setVisible(true);
    ui->newGame->setEnabled(true);
}

void MainWindow::displayGameOver1() {
    clearLog();

    // Wyświetl komunikat końcowy
    logMessage("Sometimes you want to rush thing and be done with them. Well this is one way to do it, but this time it won't work. Normally reading instructions is optional but not in this world, you either ingnored them or just haven't read it but that only works against you. It is never possible to win against powerful enemy without preparation. You migh have been hero of this world but not a very good one it seems. Thanks to your ignorance entire kingdom is doomed from the start, you'll be forever cursed by your ancestors and everyone you swore to protect. GAME OVER.");
    // Ukryj inne elementy interfejsu

    for (QPushButton* button : findChildren<QPushButton*>()) {
        if (button != ui->quitButton && button != ui->newGame) {
            button->setEnabled(false);
            button->hide();
        }
    }

    for (QGraphicsView* tlo : findChildren<QGraphicsView*>()) {
        tlo->hide();
    }

    for (QPlainTextEdit* cele : findChildren<QPlainTextEdit*>()) {
        cele->hide();
    }

    for (QLabel* etyk : findChildren<QLabel*>()) {
        etyk->hide();
    }

    // Ustaw styl tła na obraz końcowy
    setStyleSheet("QMainWindow { background-image: url(:/images/stupidity.jpg); background-repeat: no-repeat;}");

    ui->newGame->setVisible(true);
    ui->newGame->setEnabled(true);
}

void MainWindow::displayGameOver2() {
    clearLog();

    // Wyświetl komunikat końcowy
    logMessage("You fought long and hard, The amber Lord had the upper hand form the very begining. At the last second when he was about to end your life you manage to slip rom his grasp and jump onto his back. In the act of heroism you manage to plant your last water bomb right in the mouth of The Amber Lord. You watch as suprised creature can't comprehand what's happening and split seconds later you watch as it explodes, throwing water acros the room like a fountain. Lifeless body of the most dangerous dragon lays before your eyes, yet you cannot believe it;s all over. Centuries of the tyrany are finally over. You go back to the Pyroklas Castle as a victor, everyone cheers at your return. King throws massive feast to comemorate this beatiful victory. You feel accomplished. After the ceremony you quietly leave the city and as the sun sets you are left with only one unexpected feeling: 'what if htere's even greater threat hiding in the shadows...' ");
    // Ukryj inne elementy interfejsu

    for (QPushButton* button : findChildren<QPushButton*>()) {
        if (button != ui->quitButton && button != ui->newGame) {
            button->setEnabled(false);
            button->hide();
        }
    }

    for (QGraphicsView* tlo : findChildren<QGraphicsView*>()) {
        tlo->hide();
    }
    for (QPlainTextEdit* cele : findChildren<QPlainTextEdit*>()) {
        cele->hide();
    }

    for (QLabel* etyk : findChildren<QLabel*>()) {
        etyk->hide();
    }

    // Ustaw styl tła na obraz końcowy
    setStyleSheet("QMainWindow { background-image: url(:/images/final.jpg); background-repeat: no-repeat;}");

    ui->newGame->setVisible(true);
    ui->newGame->setEnabled(true);
}

void MainWindow::on_newGame_clicked() {
    // Zresetuj grę
    game.resetGame(); // Wywołanie metody resetGame

    // Pokaż wszystkie ukryte elementy interfejsu
    for (QPushButton* button : findChildren<QPushButton*>()) {
        button->setEnabled(true); // Włącz przyciski
        button->show();
    }

    for (QGraphicsView* tlo : findChildren<QGraphicsView*>()) {
        tlo->show();
    }

    for (QPlainTextEdit* cele : findChildren<QPlainTextEdit*>()) {
        cele->show();
    }

    for (QLabel* etyk : findChildren<QLabel*>()) {
        etyk->show();
    }

    // Ustaw styl tła na domyślny
    setStyleSheet("");

    // Ukryj przycisk "New Game"
    ui->newGame->setVisible(false);

    // Zaktualizuj interfejs użytkownika
    updateUI();
}
