#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
}

void MainWindow::handleButton() {
    emit statusUpdateMessage(QString("Button 1 was clicked!"), 0);
}

void MainWindow::handleButton2() {
    emit statusUpdateMessage(QString("Other button is now pressed!"), 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

