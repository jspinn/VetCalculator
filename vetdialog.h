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

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void sendName(QString name);


private:
    Ui::VetDialog *ui;
};

#endif // VETDIALOG_H
