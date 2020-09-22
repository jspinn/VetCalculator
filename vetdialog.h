#ifndef VETDIALOG_H
#define VETDIALOG_H

#include <QDialog>

namespace Ui {
class VetDialog;
}

class VetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VetDialog(QWidget *parent = nullptr);
    ~VetDialog();

private:
    Ui::VetDialog *ui;
};

#endif // VETDIALOG_H
