#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void displayGameOver();
    void displayGameOver1();
    void displayGameOver2();
    void logMessage(const QString &message);
    void changeBackground(const QString &filePath);
    void updateLocationLabel(const QString &location);
    void updateUI();

private slots:
    void on_moveButton_clicked();
    void on_checkInventoryButton_clicked();
    void on_saveGameButton_clicked();
    void on_loadGameButton_clicked();
    void clearLog();
    void showLocationHistory();
    void onQuitButtonClicked();
    void on_newGame_clicked();

private:
    Ui::MainWindow *ui;
    Game game;
    std::map<QString, QString> locationHistories;
};

#endif // MAINWINDOW_H
