#include "vetdialog.h"
#include "ui_vetdialog.h"

VetDialog::VetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VetDialog)
{
    ui->setupUi(this);
}

VetDialog::~VetDialog()
{
    delete ui;
}
