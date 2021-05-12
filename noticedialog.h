#ifndef NOTICEDIALOG_H
#define NOTICEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class NoticeDialog;
}

class NoticeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeDialog(QString message, QWidget *parent = nullptr);
    ~NoticeDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NoticeDialog *ui;
};

#endif // NOTICEDIALOG_H
