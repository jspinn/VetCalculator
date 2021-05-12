#include "noticedialog.h"
#include "ui_noticedialog.h"

NoticeDialog::NoticeDialog(QString message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoticeDialog)
{
    ui->setupUi(this);

    // Hides ? button at top of window
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->label->setText(message);
}

NoticeDialog::~NoticeDialog()
{
    delete ui;
}

void NoticeDialog::on_pushButton_clicked()
{
    close();
}
