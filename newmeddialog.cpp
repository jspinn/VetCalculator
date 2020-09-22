#include "newmeddialog.h"
#include "ui_newmeddialog.h"

NewMedDialog::NewMedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMedDialog)
{
    ui->setupUi(this);
}

NewMedDialog::~NewMedDialog()
{
    delete ui;
}
