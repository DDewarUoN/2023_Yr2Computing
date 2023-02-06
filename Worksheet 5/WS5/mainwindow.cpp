#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qmessagebox.h>
#include "ModelPart.h"
#include "ModelPartList.h"
#include "qfiledialog.h"
#include "optionsdialog.h"
#include "name_editor.h"

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
    //Link right-click context meny to Tree view
    ui->treeView->addAction(ui->actionName_Edit);
    ui->treeView->addAction(ui->actionColour);
    ui->treeView->addAction(ui->actionIs_Visible);

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
    OptionsDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog Accepted"), 0);
    }
    else {
        emit statusUpdateMessage(QString("Dialog Rejected"), 0);
    }
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


void MainWindow::on_actionOpen_File_triggered()
{
    emit statusUpdateMessage(QString("Open File action Triggered"), 0);
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files(*.stl);; Text Files(*.txt)")
    );
}

void MainWindow::on_actionName_Edit_triggered()
{
    QString type = "Name";
    //Get Indexes for 'right-click' selected object in TreeView
    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString selected_objectName = selectedPart->data(0).toString();

    Name_Editor NameEditor(type, selected_objectName, this);
    NameEditor.setWindowTitle(type + " Editor");

    if (NameEditor.exec() == QDialog::Accepted) {
        selectedPart->changeName(NameEditor.getText());
    }
    else {

    }
}

void MainWindow::on_actionColour_triggered()
{

}

void MainWindow::on_actionIs_Visible_triggered()
{

}

