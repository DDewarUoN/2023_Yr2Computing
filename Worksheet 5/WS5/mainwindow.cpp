#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qmessagebox.h>
#include "ModelPart.h"
#include "ModelPartList.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    
    //Create the ModelList
    this->partList = new ModelPartList("PartList");

    //Link the ModelList to the TreeView GUI
    ui->treeView->setModel(this->partList);

    //Create the Model Tree
    ModelPart* rootItem = this->partList->getRootItem();

    //Add 3 top level items
    for (int i = 0; i < 3; ++i) {
        //Create Strings for both data columns:
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        //Create child item
        ModelPart* childItem = new ModelPart({ name, visible });

        //Append to tree top-level
        rootItem->appendChild(childItem);

        //Add 5 sub-items:
        for (int j = 0; j < 5; ++j) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name, visible });

            //Append to parent
            childItem->appendChild(childChildItem);
        }

    }

}

void MainWindow::handleButton() {
    emit statusUpdateMessage(QString("Button 1 was clicked!"), 0);
}

void MainWindow::handleButton2() {
    emit statusUpdateMessage(QString("Other button is now pressed!"), 0);
}

void MainWindow::handleTreeClicked() {
    //Get the index of the selected item:
    QModelIndex index = ui->treeView->currentIndex();

    //Get a pointer to the item from the index
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    //Retrieve the name string from the QVariant Data Array
    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

