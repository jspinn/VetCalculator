#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QString>
#include "medication.h"

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(Medication med, QWidget *parent = nullptr);
    ~EditDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void sendReplaceMed(Medication med);

private:
    Ui::EditDialog *ui;

};

#endif // EDITDIALOG_H
