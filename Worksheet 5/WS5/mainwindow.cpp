#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
}

void MainWindow::handleButton() {
    QMessageBox msgBox;
    msgBox.setText("Button 1 was pressed");
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

