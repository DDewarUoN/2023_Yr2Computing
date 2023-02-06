#ifndef NAME_EDITOR_H
#define NAME_EDITOR_H

#include <QDialog>

namespace Ui {
class Name_Editor;
}

class Name_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Name_Editor(QString editType, QString labelText, QWidget *parent = nullptr);
    ~Name_Editor();

public slots:
    QString getText();

private:
    Ui::Name_Editor *ui;
};

#endif // NAME_EDITOR_H
