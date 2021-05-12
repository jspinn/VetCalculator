#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "veterinarian.h"
#include "vetdialog.h"
#include "newmeddialog.h"
#include "confirmdialog.h"
#include "editdialog.h"
#include "noticedialog.h"
#include <fstream>
#include <io.h>
#include <iostream>
#include <QFile>
#include <QDataStream>


const double KG_CONVERSION = 2.2;

const double WEIGHT_MAX = 1500;
const double WEIGHT_MIN = 0.01;

const double DOSE_MAX = 10000;
const double DOSE_MIN = 0.01;

const double CONC_MAX = 10000;
const double CONC_MIN = 0.01;

const double DECIMAL_PTS = 2;

const QVector<QString> DEFAULT_SPECIES_LIST = {"Canine", "Feline"};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateMedTable(int index);

    void updateCalcMeds(int vetIndex, int specIndex);

    double CalculateDose(double weight, double dose, double concentration);

private slots:

    void on_calcButton_clicked();

    void on_addVetButton_clicked();

    void addVet(QString name);

    void on_calcVetCB_currentIndexChanged(int index);

    void on_calcSpeciesCB_currentIndexChanged(int index);

    void on_vetComboBox_currentIndexChanged(int index);

    void on_calcAddButton_clicked();

    void on_calcAllButton_clicked();

    void receiveMed(Medication med, int speciesIndex);

    void replaceMed(Medication med);

    void on_addButton_clicked();

    void on_speciesCB_currentIndexChanged(int index);

    void on_deleteVetButton_clicked();

    void on_saveButton_clicked();

    void loadData();

    void on_calcRemoveButton_clicked();

    void on_calcRemoveAllButton_clicked();

    void on_EditButton_clicked();

    void on_DeleteButton_clicked();

    void on_calcAddAllButton_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QVector<Veterinarian> vetList;

    QVector<Medication> calcMedsList;

    VetDialog* vetDialog;

    NewMedDialog* medDialog;

    ConfirmDialog* confDialog;

    EditDialog* editDialog;

    NoticeDialog* noticeDialog;

    bool changesMade;




};
#endif // MAINWINDOW_H
