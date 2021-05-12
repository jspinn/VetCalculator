#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    changesMade = false;


    // Limit QLineEdits to only numbers
    ui->manualWeightEdit->setValidator(new QDoubleValidator(WEIGHT_MIN, WEIGHT_MAX, DECIMAL_PTS));
    ui->manualDoseEdit->setValidator(new QDoubleValidator(DOSE_MIN, DOSE_MAX, DECIMAL_PTS));
    ui->manualConcEdit->setValidator(new QDoubleValidator(CONC_MIN, CONC_MAX, DECIMAL_PTS));

    // Set up medTable
    ui->medTableWidget->setColumnCount(3);
    ui->medTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->medTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->medTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Dose (mg/kg)"));
    ui->medTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Concentration (mg/ml)"));

    ui->calcResultView->setColumnCount(3);
    ui->calcResultView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->calcResultView->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->calcResultView->setHorizontalHeaderItem(1, new QTableWidgetItem("Dose"));
    ui->calcResultView->setHorizontalHeaderItem(2, new QTableWidgetItem("Result"));


    loadData();

    // Set up vet combo boxes
    for (int i = 0; i < Veterinarian::getSpeciesList().size(); i++)
    {
        ui->speciesCB->addItem(Veterinarian::getSpeciesList()[i]);
        ui->calcSpeciesCB->addItem(Veterinarian::getSpeciesList()[i]);
    }

    for (int i = 0; i < vetList.size(); i++)
    {
        QString name = vetList[i].getName();
        ui->vetComboBox->addItem(name);
        ui->calcVetCB->addItem(name);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMedTable(int index)
{
    ui->medTableWidget->setRowCount(0);

    int speciesIndex = ui->speciesCB->currentIndex();
    QVector<Medication> meds = vetList[index].getMedList()[speciesIndex];

    for (int i = 0; i < meds.size(); i++)
    {
        ui->medTableWidget->insertRow(ui->medTableWidget->rowCount());
        ui->medTableWidget->setItem(ui->medTableWidget->rowCount()-1, 0, new QTableWidgetItem(meds[i].getName()));
        ui->medTableWidget->setItem(ui->medTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(meds[i].getDose())));
        ui->medTableWidget->setItem(ui->medTableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::number(meds[i].getConcentration())));
    }
}

void MainWindow::updateCalcMeds(int vetIndex, int specIndex)
{

    ui->allMedsView->clear();
    ui->calcMedsView->clear();

    calcMedsList.clear();

    QVector<Medication> meds = vetList[vetIndex].getMedList()[specIndex];
    for (int i = 0; i < meds.size(); i++)
    {
        ui->allMedsView->addItem(meds[i].getName());
    }
}

double MainWindow::CalculateDose(double weight, double dose, double concentration)
{
    return weight / KG_CONVERSION * dose / concentration;
}

// Manual tab slots

void MainWindow::on_calcButton_clicked()
{
    if (ui->manualWeightEdit->text() == "") {
        ui->manualResultLabel->setText("Must enter weight");
        ui->manualWeightEdit->setFocus();
    }
    else if (ui->manualDoseEdit->text() == "") {
        ui->manualResultLabel->setText("Must enter dose");
        ui->manualDoseEdit->setFocus();
    }
    else if (ui->manualConcEdit->text() == "") {
        ui->manualResultLabel->setText("Must enter concentration");
        ui->manualConcEdit->setFocus();
    }

    else {
    double weight = (ui->manualWeightEdit->text()).toDouble();
    double dose = ui->manualDoseEdit->text().toDouble();
    double conc = ui->manualConcEdit->text().toDouble();
    double calculatedDose = CalculateDose(weight, dose, conc);
    QString doseText = QString::number(calculatedDose, 'f', 2) + " mls";
    ui->manualResultLabel->setText(doseText);
    }

}

// Calculator tab slots

void MainWindow::on_calcVetCB_currentIndexChanged(int index)
{

    if (index >= 0)
    {
        updateCalcMeds(index, ui->calcSpeciesCB->currentIndex());
    }
    else
    {
        ui->allMedsView->clear();
        ui->calcMedsView->clear();
    }
}

void MainWindow::on_calcSpeciesCB_currentIndexChanged(int index)
{
    if (ui->calcVetCB->currentIndex() >= 0)
        updateCalcMeds(ui->calcVetCB->currentIndex(), index);
}

void MainWindow::on_calcAddButton_clicked()
{
    if (ui->allMedsView->currentRow() >= 0)
    {
        int medIndex = ui->allMedsView->currentRow();
        int specIndex = ui->speciesCB->currentIndex();
        int vetIndex = ui->calcVetCB->currentIndex();

        Medication med = vetList[vetIndex].getMedList()[specIndex][medIndex];

        if (!calcMedsList.contains(med))
        {
            calcMedsList.push_back(med);

            ui->calcMedsView->addItem(med.getName());

        }

    }
}

void MainWindow::on_calcRemoveButton_clicked()
{

    int selectedIndex = ui->calcMedsView->currentRow();
    if (selectedIndex >= 0)
    {
        calcMedsList.remove(selectedIndex);
        ui->calcMedsView->takeItem(selectedIndex);
    }
}

void MainWindow::on_calcRemoveAllButton_clicked()
{
    calcMedsList.clear();
    ui->calcMedsView->clear();
}

void MainWindow::on_calcAddAllButton_clicked()
{
    int specIndex = ui->speciesCB->currentIndex();
    int vetIndex = ui->calcVetCB->currentIndex();

    calcMedsList = vetList[vetIndex].getMedList()[specIndex];

    for (Medication med : calcMedsList)
    {
        ui->calcMedsView->addItem(med.getName());
    }
}

void MainWindow::on_calcAllButton_clicked()
{

    ui->calcResultView->setRowCount(0);

    if (ui->calcWeightLineEdit->text().isEmpty())
    {
        noticeDialog = new NoticeDialog("Must enter valid weight.");
        noticeDialog->show();

    }
    else if (calcMedsList.size() == 0)
    {
        noticeDialog = new NoticeDialog("No medications selected.");
        noticeDialog->show();

    }
    else
    {
        double weight = ui->calcWeightLineEdit->text().toDouble();
        for (Medication med : calcMedsList)
        {

            double result = med.calculateResult(weight);
            QString resultText = QString::number(result, 'f', 2) + " mls";

            QString nameText = med.getName() + " (" + QString::number(med.getConcentration()) + "mg/ml)";

            QString doseText = QString::number(med.getDose()) + " mg/kg";

            ui->calcResultView->insertRow(ui->calcResultView->rowCount());
            ui->calcResultView->setItem(ui->calcResultView->rowCount()-1, 0, new QTableWidgetItem(nameText));
            ui->calcResultView->setItem(ui->calcResultView->rowCount()-1, 1, new QTableWidgetItem(doseText));
            ui->calcResultView->setItem(ui->calcResultView->rowCount()-1, 2, new QTableWidgetItem(resultText));
        }
    }

}



// Vet Tab Slots

void MainWindow::on_vetComboBox_currentIndexChanged(int index)
{
    if (vetList.size() > 0)
    {
        updateMedTable(index);
    }
    else
    {
        ui->medTableWidget->setRowCount(0);
    }

}

void MainWindow::receiveMed(Medication med, int speciesIndex)
{

    vetList[(ui->vetComboBox->currentIndex())].addMed(med, speciesIndex);

    updateMedTable(ui->vetComboBox->currentIndex());
    updateCalcMeds(ui->calcVetCB->currentIndex(), ui->calcSpeciesCB->currentIndex());

    changesMade = true;

}

void MainWindow::replaceMed(Medication med)
{
    int medIndex = ui->medTableWidget->currentRow();
    int vetIndex = ui->vetComboBox->currentIndex();
    int specIndex = ui->speciesCB->currentIndex();

    vetList[vetIndex].replaceMed(specIndex, medIndex, med);

    updateMedTable(vetIndex);

    changesMade = true;
}

void MainWindow::on_addVetButton_clicked()
{
    vetDialog = new VetDialog(this);
    connect(vetDialog, SIGNAL(sendName(QString)), this, SLOT(addVet(QString)));

    vetDialog->exec();

    delete vetDialog;
}

void MainWindow::addVet(QString name) {
    Veterinarian newVet = Veterinarian(name);
    vetList.push_back(newVet);
    ui->vetComboBox->addItem(newVet.getName());
    ui->calcVetCB->addItem(newVet.getName());
    ui->vetComboBox->setCurrentIndex(ui->vetComboBox->count() - 1);

    changesMade = true;
}


void MainWindow::on_addButton_clicked()
{
    if (vetList.size() > 0)
    {

        medDialog = new NewMedDialog(ui->speciesCB->currentIndex());
        connect(medDialog, SIGNAL(send_med(Medication, int)), this, SLOT(receiveMed(Medication, int)));

        medDialog->show();
    }
}

void MainWindow::on_speciesCB_currentIndexChanged(int index)
{
    if (vetList.size() > 0)
        updateMedTable(index);
}

void MainWindow::on_deleteVetButton_clicked()
{

    if (vetList.size() > 0)
    {
        QString confText = "Are you sure you want to delete " +
                vetList[ui->vetComboBox->currentIndex()].getName() +
                "?";

        confDialog = new ConfirmDialog(confText);

        confDialog->exec();

        if (confDialog->result() == QDialog::Accepted)
        {
            int index = ui->vetComboBox->currentIndex();

            vetList.erase(vetList.begin() + index);
            ui->vetComboBox->removeItem(index);
            ui->calcVetCB->removeItem(index);
        }

        delete confDialog;
    }

}


void MainWindow::on_saveButton_clicked()
{
    QFile speciesFile("species.dat");
    speciesFile.open(QIODevice::WriteOnly);

    QDataStream sout(&speciesFile);
    for (int i = 0; i < Veterinarian::speciesList.size(); i++)
    {
        sout << Veterinarian::speciesList[i];
    }

    speciesFile.close();

    QFile vetFile("vets.dat");
    QDataStream vout(&vetFile);
    vetFile.open(QIODevice::WriteOnly);

    for (int i = 0; i < vetList.size(); i++)
    {
        vout << vetList[i];
    }

    vetFile.close();

    noticeDialog = new NoticeDialog("Data saved.");
    noticeDialog->show();

    changesMade = false;

}



void MainWindow::on_EditButton_clicked()
{
    int medIndex = ui->medTableWidget->currentRow();
    int vetIndex = ui->vetComboBox->currentIndex();
    int specIndex = ui->speciesCB->currentIndex();


    if (medIndex >= 0)
    {
        Medication med = vetList[vetIndex].getMedList()[specIndex][medIndex];

        editDialog = new EditDialog(med);

        connect(editDialog, SIGNAL(sendReplaceMed(Medication)), this, SLOT(replaceMed(Medication)));

        editDialog->exec();

        delete editDialog;

    }

}

void MainWindow::on_DeleteButton_clicked()
{
    int medIndex = ui->medTableWidget->currentRow();
    int vetIndex = ui->vetComboBox->currentIndex();
    int specIndex = ui->speciesCB->currentIndex();

    if (medIndex >= 0)
    {
        QString confText = "Are you sure you want to delete " +
                vetList[vetIndex].getMedList()[specIndex][medIndex].getName() +
                "?";

        confDialog = new ConfirmDialog(confText);

        confDialog->exec();

        if (confDialog->result() == QDialog::Accepted)
        {
            vetList[vetIndex].getMedList()[specIndex].remove(medIndex);
            ui->medTableWidget->removeRow(medIndex);

            changesMade = true;
        }

        delete confDialog;
    }


}

void MainWindow::loadData()
{
    // Load species List
    QFile speciesFile("species.dat");
    speciesFile.open(QIODevice::ReadOnly);

    QDataStream sin(&speciesFile);
    QString spec;
    while (!sin.atEnd())
    {
        sin >> spec;
        Veterinarian::speciesList.push_back(spec);
    }
    speciesFile.close();

    // Create default species list if doesn't exist
    if (Veterinarian::speciesList.size() == 0)
        Veterinarian::speciesList = DEFAULT_SPECIES_LIST;

    QFile vetFile("vets.dat");
    QDataStream vin(&vetFile);
    vetFile.open(QIODevice::ReadOnly);


    Veterinarian vet;

    while (!vin.atEnd())
    {
        vin >> vet;
        vetList.push_back(vet);
    }

    vetFile.close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (changesMade)
    {
        confDialog = new ConfirmDialog("Would you like to save changes?");
        confDialog->exec();

        if (confDialog->result() == QDialog::Accepted)
            on_saveButton_clicked();
    }

}


