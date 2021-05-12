#ifndef NEWMEDDIALOG_H
#define NEWMEDDIALOG_H

#include <QDialog>

#include "medication.h"

namespace Ui {
class NewMedDialog;
}

class NewMedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMedDialog(int speciesIndex, QWidget *parent = nullptr);
    ~NewMedDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void send_med(Medication med, int speciesIndex);

private:
    Ui::NewMedDialog *ui;
    int speciesIndex;
};

#endif // NEWMEDDIALOG_H
