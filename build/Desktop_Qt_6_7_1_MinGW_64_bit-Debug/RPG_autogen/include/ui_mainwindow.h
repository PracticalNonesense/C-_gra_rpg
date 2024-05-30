/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *locationLabel;
    QLabel *xpLabel;
    QLabel *healthLabel;
    QPushButton *moveButton;
    QPushButton *checkInventoryButton;
    QPushButton *saveGameButton;
    QPushButton *loadGameButton;
    QGraphicsView *tlo;
    QTextEdit *TextEdit;
    QPushButton *history;
    QPushButton *trash;
    QPushButton *quitButton;
    QPushButton *newGame;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(797, 482);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        locationLabel = new QLabel(centralwidget);
        locationLabel->setObjectName("locationLabel");
        locationLabel->setGeometry(QRect(630, 20, 151, 21));
        locationLabel->setStyleSheet(QString::fromUtf8("background: rgb(0, 0, 0)"));
        xpLabel = new QLabel(centralwidget);
        xpLabel->setObjectName("xpLabel");
        xpLabel->setGeometry(QRect(540, 20, 71, 21));
        xpLabel->setStyleSheet(QString::fromUtf8("background: rgb(0, 0, 0)"));
        healthLabel = new QLabel(centralwidget);
        healthLabel->setObjectName("healthLabel");
        healthLabel->setGeometry(QRect(430, 20, 101, 21));
        healthLabel->setStyleSheet(QString::fromUtf8("background: rgb(0, 0, 0)"));
        moveButton = new QPushButton(centralwidget);
        moveButton->setObjectName("moveButton");
        moveButton->setGeometry(QRect(20, 270, 80, 24));
        checkInventoryButton = new QPushButton(centralwidget);
        checkInventoryButton->setObjectName("checkInventoryButton");
        checkInventoryButton->setGeometry(QRect(120, 270, 80, 24));
        saveGameButton = new QPushButton(centralwidget);
        saveGameButton->setObjectName("saveGameButton");
        saveGameButton->setGeometry(QRect(710, 170, 80, 24));
        loadGameButton = new QPushButton(centralwidget);
        loadGameButton->setObjectName("loadGameButton");
        loadGameButton->setGeometry(QRect(710, 200, 80, 24));
        tlo = new QGraphicsView(centralwidget);
        tlo->setObjectName("tlo");
        tlo->setEnabled(true);
        tlo->setGeometry(QRect(-20, -30, 831, 351));
        TextEdit = new QTextEdit(centralwidget);
        TextEdit->setObjectName("TextEdit");
        TextEdit->setEnabled(false);
        TextEdit->setGeometry(QRect(0, 320, 801, 131));
        history = new QPushButton(centralwidget);
        history->setObjectName("history");
        history->setGeometry(QRect(640, 50, 141, 21));
        trash = new QPushButton(centralwidget);
        trash->setObjectName("trash");
        trash->setGeometry(QRect(710, 290, 81, 31));
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName("quitButton");
        quitButton->setGeometry(QRect(710, 230, 80, 24));
        newGame = new QPushButton(centralwidget);
        newGame->setObjectName("newGame");
        newGame->setGeometry(QRect(310, 210, 141, 41));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setEnabled(false);
        plainTextEdit->setGeometry(QRect(10, 30, 111, 141));
        MainWindow->setCentralWidget(centralwidget);
        tlo->raise();
        moveButton->raise();
        checkInventoryButton->raise();
        saveGameButton->raise();
        loadGameButton->raise();
        TextEdit->raise();
        healthLabel->raise();
        xpLabel->raise();
        locationLabel->raise();
        history->raise();
        trash->raise();
        quitButton->raise();
        newGame->raise();
        plainTextEdit->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 797, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        locationLabel->setText(QCoreApplication::translate("MainWindow", "locationLabel", nullptr));
        xpLabel->setText(QCoreApplication::translate("MainWindow", "xpLabel ", nullptr));
        healthLabel->setText(QCoreApplication::translate("MainWindow", "healthLabel ", nullptr));
        moveButton->setText(QCoreApplication::translate("MainWindow", "New location", nullptr));
        checkInventoryButton->setText(QCoreApplication::translate("MainWindow", "Inventory", nullptr));
        saveGameButton->setText(QCoreApplication::translate("MainWindow", "Save game", nullptr));
        loadGameButton->setText(QCoreApplication::translate("MainWindow", "Load game", nullptr));
        history->setText(QCoreApplication::translate("MainWindow", "History about location", nullptr));
        trash->setText(QCoreApplication::translate("MainWindow", "Clear window", nullptr));
        quitButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        newGame->setText(QCoreApplication::translate("MainWindow", "New game", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("MainWindow", "---OBJECTIVES----\n"
"\n"
"- Enter Volcanic Mountains\n"
"\n"
"- Defeat The Amber Lord", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
