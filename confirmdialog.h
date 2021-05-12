#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QString text, QWidget *parent = nullptr);
    ~ConfirmDialog();

private slots:
    void on_yesButton_clicked();

    void on_noButton_clicked();

private:
    Ui::ConfirmDialog *ui;
};

#endif // CONFIRMDIALOG_H
