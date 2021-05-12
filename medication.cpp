#include "medication.h"
#include "mainwindow.h"

Medication::Medication()
{

}

Medication::Medication(QString n, double d, double concen) {
    setName(n);
    setDose(d);
    setConcentration(concen);
}

QString Medication::getName() const {
    return name;
}

void Medication::setName(QString n) {
    if (n != "")
      name = n;
}

double Medication::getConcentration() const {
    return concentration;
}

void Medication::setConcentration(double concen) {
    if (concen > 0) {
        concentration = concen;
    }
}

double Medication::getDose() const {
    return dose;
}

void Medication::setDose(double d) {
    dose = d;
}

double Medication::calculateResult(double weight) {
    return (weight / KG_CONVERSION * dose / concentration);
}

bool Medication::operator == (const Medication rmed) const
{
    return (name == rmed.name &&
            dose == rmed.dose &&
            concentration == rmed.concentration);
}

QDataStream &operator<<(QDataStream& stream, const Medication& med)
{
    stream << med.getName();
    stream << QVariant(med.getDose());
    stream << QVariant(med.getConcentration());

    return stream;
}

QDataStream &operator>>(QDataStream& stream, Medication& med) {
    QString name;
    QVariant dose;
    QVariant conc;

    stream >> name >> dose >> conc;

    med.setName(name);
    med.setDose(dose.toDouble());
    med.setConcentration(conc.toDouble());

    return stream;

}
