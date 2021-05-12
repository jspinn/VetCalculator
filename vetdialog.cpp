#include "vetdialog.h"
#include "ui_vetdialog.h"

VetDialog::VetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VetDialog)
{
    ui->setupUi(this);

    // Hides ? button at top of window
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

VetDialog::~VetDialog()
{
    delete ui;
}

void VetDialog::on_okButton_clicked()
{
    if (ui->newVetLineEdit->text() != "")
    {
        sendName(ui->newVetLineEdit->text());
        this->close();
    }

}

void VetDialog::on_cancelButton_clicked()
{
    this->close();
}

