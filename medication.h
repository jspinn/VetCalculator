#ifndef MEDICATION_H
#define MEDICATION_H

#include <QString>
#include <QVariant>
#include <QDataStream>
#include <QMetaType>


using namespace std;

class Medication
{

private:
    QString name;

    double dose;
    double concentration;


public:
    Medication();

    Medication(QString n, double d, double concen);

    QString getName() const;

    void setName(QString n);

    double getConcentration() const;

    void setConcentration(double concen);

    double getDose() const;

    void setDose(double dose);

    double calculateResult(double weight);

    bool operator == (const Medication rmed) const;
};

Q_DECLARE_METATYPE(Medication)

QDataStream &operator<<(QDataStream& stream, const Medication& med);
QDataStream &operator>>(QDataStream& stream, Medication& med);



#endif // MEDICATION_H
