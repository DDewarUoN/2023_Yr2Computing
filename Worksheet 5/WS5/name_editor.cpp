#include "name_editor.h"
#include "ui_name_editor.h"

Name_Editor::Name_Editor(QString editType, QString labelText, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Name_Editor)
{
    ui->setupUi(this);
    ui->label->setText("Change "+editType+" to:");
    ui->textEdit->setText(labelText);
}

Name_Editor::~Name_Editor()
{
    delete ui;
}

QString Name_Editor::getText() {
    QString acqText = ui->textEdit->toPlainText();
    return acqText;
}
