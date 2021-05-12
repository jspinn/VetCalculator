#ifndef VETERINARIAN_H
#define VETERINARIAN_H

#include "medication.h"
#include <QVector>
#include <string>
#include <QString>
#include <QDataStream>
#include <QMetaType>

class Veterinarian
{

private:


    QString name;

    QVector<QVector<Medication>> medList;



public:
    Veterinarian();
    Veterinarian(QString name);

    QString getName() const;

    void setName(QString n);

    QVector<QVector<Medication>> getMedList();

    QVector<QVector<Medication>> getMedList() const;

    void setMedList(QVector<QVector<Medication>>);

    void addMed(Medication med, int speciesIndex);

    void replaceMed(int speciesIndex, int medIndex, Medication med);

    static QVector<QString> getSpeciesList() {return speciesList;};

    static QVector<QString> speciesList;




};

Q_DECLARE_METATYPE(Veterinarian)

QDataStream &operator<<(QDataStream& stream, const Veterinarian& vet);

QDataStream &operator>>(QDataStream& stream, Veterinarian& vet);


#endif // VETERINARIAN_H
