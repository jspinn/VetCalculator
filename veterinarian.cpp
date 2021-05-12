#include "veterinarian.h"
#include <iostream>

QVector<QString> Veterinarian::speciesList;

Veterinarian::Veterinarian()
{
    for (int i = 0; i < speciesList.size(); i++)
    {
        medList.push_back(QVector<Medication>());
    }
}

Veterinarian::Veterinarian(QString n) {
    setName(n);
    for (int i = 0; i < speciesList.size(); i++)
    {
        medList.push_back(QVector<Medication>());
    }
}

QString Veterinarian::getName() const {
    return name;
}

void Veterinarian::setName(QString n) {
    if (n != "")
        name = n;
}

QVector<QVector<Medication>> Veterinarian::getMedList()
{
    return medList;
}

QVector<QVector<Medication>> Veterinarian::getMedList() const
{
    return medList;
}

void Veterinarian::setMedList(QVector<QVector<Medication>> list)
{
    medList = list;
}

void Veterinarian::addMed(Medication med, int speciesIndex)
{
    medList[speciesIndex].push_back(med);
}

void Veterinarian::replaceMed(int speciesIndex, int medIndex, Medication med)
{
    medList[speciesIndex].replace(medIndex, med);
}

QDataStream &operator<<(QDataStream& stream, const Veterinarian& vet)
{
    stream << vet.getName();

    stream << vet.getMedList();

//    stream << qint32(vet.getMedList().size());
//    for (int i = 0; i < vet.getMedList().size(); i++)
//    {
//        stream << qint32(vet.getMedList()[i].size());
//        for (int j = 0; j < vet.getMedList()[i].size(); i++)
//        {
//            stream << vet.getMedList()[i][j];
//        }
//    }

    return stream;
}

QDataStream &operator>>(QDataStream& stream, Veterinarian& vet)
{
    QString name;
    QVector<QVector<Medication>> medList;

    stream >> name;
    vet.setName(name);

    stream >> medList;
    vet.setMedList(medList);
//    stream >> iCount;

//    cout << iCount.toInt();

//    for (int i = 0; i < iCount.toInt(); i++)
//    {
//        stream.
//        cout << jCount.toInt();
//        for (int j = 0; j < jCount.toInt(); i++)
//        {
//            stream >> med;
//            cout << med.getName().toStdString();
//            cout << med.getDose();
//            vet.addMed(med, i);
//        }
//    }

    return stream;

}


