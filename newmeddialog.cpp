#include "newmeddialog.h"
#include "ui_newmeddialog.h"
#include "mainwindow.h"
#include <QDoubleValidator>

NewMedDialog::NewMedDialog(int speciesIndex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMedDialog)
{
    ui->setupUi(this);
    this->speciesIndex = speciesIndex;

    ui->doseLineEdit->setValidator(new QDoubleValidator(WEIGHT_MIN, WEIGHT_MAX, DECIMAL_PTS));
    ui->concLineEdit->setValidator(new QDoubleValidator(WEIGHT_MIN, WEIGHT_MAX, DECIMAL_PTS));

    // Hides ? button at top of window
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

NewMedDialog::~NewMedDialog()
{
    delete ui;
}

void NewMedDialog::on_okButton_clicked()
{
    if (ui->nameLineEdit->text().isEmpty())
    {
        ui->errorLabel->setText("Must enter name.");
        ui->nameLineEdit->setFocus();
    }
    else if (ui->doseLineEdit->text().isEmpty())
    {
        ui->errorLabel->setText("Must enter dose.");
        ui->doseLineEdit->setFocus();
    }
    else if (ui->concLineEdit->text().isEmpty())
    {
        ui->errorLabel->setText("Must enter concentration.");
        ui->concLineEdit->setFocus();
    }
    else
    {
        QString name = ui->nameLineEdit->text();
        double dose = ui->doseLineEdit->text().toDouble();
        double conc = ui->concLineEdit->text().toDouble();
        Medication med = Medication(name, dose, conc);

        send_med(med, speciesIndex);
        this->close();
    }
}

void NewMedDialog::on_cancelButton_clicked()
{
    this->close();
}
