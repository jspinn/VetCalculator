#include "editdialog.h"
#include "ui_editdialog.h"
#include "mainwindow.h"
#include <QDoubleValidator>

EditDialog::EditDialog(Medication med, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);

    // Hides ? button at top of window
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->doseLineEdit->setValidator(new QDoubleValidator(WEIGHT_MIN, WEIGHT_MAX, DECIMAL_PTS));
    ui->concLineEdit->setValidator(new QDoubleValidator(WEIGHT_MIN, WEIGHT_MAX, DECIMAL_PTS));

    QString doseText = QString::number(med.getDose());
    QString concText = QString::number(med.getConcentration());


    ui->nameLineEdit->setText(med.getName());
    ui->doseLineEdit->setText(doseText);
    ui->concLineEdit->setText(concText);

}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::on_okButton_clicked()
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

        Medication replacement(name, dose, conc);

        sendReplaceMed(replacement);

        this->accept();
    }
}

void EditDialog::on_cancelButton_clicked()
{
    this->reject();
}
