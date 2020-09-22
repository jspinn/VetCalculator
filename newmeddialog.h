#ifndef NEWMEDDIALOG_H
#define NEWMEDDIALOG_H

#include <QDialog>

namespace Ui {
class NewMedDialog;
}

class NewMedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMedDialog(QWidget *parent = nullptr);
    ~NewMedDialog();

private:
    Ui::NewMedDialog *ui;
};

#endif // NEWMEDDIALOG_H
