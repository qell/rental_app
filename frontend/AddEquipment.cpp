#include "AddEquipment.h"
#include "backend/Database.h"
#include <QComboBox>
#include <QDialog>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>

namespace Frontend {

AddEquipment::AddEquipment(Backend::Database& database)
    : mUi(new Ui::AddEquipment)
    , mDatabase(database)
{
    mUi->setupUi(&mDialog);
    Common::fillEquipmentTypeComboBox(*mUi->equipmentType);
    connect(mUi->addEquipmentButton, SIGNAL(pressed()), this, SLOT(addEquipmentPressed()));
    connect(mUi->cancelButton, SIGNAL(pressed()), this, SLOT(cancelPressed()));

    mDialog.exec();
}

Common::EquipmentType AddEquipment::getEquipmentType()
{
    if (not mUi->equipmentType->currentIndex())
        throw QString("Nie wybrano typu urządzenia!");

    return static_cast<Common::EquipmentType>(mUi->equipmentType->currentIndex());
}

QString AddEquipment::getName()
{
    QString tmp = mUi->name->text();

    if (not tmp.size())
        throw QString("Pole nazwa nie moze byc puste!");

    return tmp;
}

QString AddEquipment::getProducer()
{
    QString tmp = mUi->producer->text();

    if (not tmp.size())
        throw QString("Pole producent nie moze byc puste!");

    return tmp;
}

double AddEquipment::getPrice()
{
    QString tmp = mUi->Price->text();

    if (not tmp.size())
        throw QString("Pole cena nie moze byc puste!");

    bool   result = true;
    double price  = tmp.toDouble(&result);

    if (result == false)
        throw QString("Blędna cena! (przykład: 12.5)");

    return price;
}

double AddEquipment::getPledge()
{
    QString tmp = mUi->pledge->text();

    if (not tmp.size())
        throw QString("Pole zysk nie moze byc puste!");

    bool   result = true;
    double pledge = tmp.toDouble(&result);

    if (result == false)
        throw QString("Blędna wartość zysku! (przykład: 150.5 lub 200)");

    return pledge;
}

uint AddEquipment::getAmount()
{
    QString tmp = mUi->amount->text();

    if (not tmp.size())
        throw QString("Pole ilość nie moze byc puste!");

    bool result = true;
    uint amount = tmp.toUInt(&result);

    if (result == false)
        throw QString("Blędna ilość!");

    return amount;
}

void AddEquipment::addEquipmentPressed()
{
    qDebug("addEquipmentPressed");
    try
    {
        Common::EquipmentParameters tmp;
        tmp.type     = getEquipmentType();
        tmp.name     = getName();
        tmp.price    = getPrice();
        tmp.pledge   = getPledge();
        tmp.amount   = getAmount();
        tmp.producer = getProducer();

        mDatabase.addEquipment(
            tmp, static_cast<Common::EquipmentType>(mUi->equipmentType->currentIndex()));

        mDialog.close();
    }
    catch (QString& e)
    {
        QMessageBox msgBox;
        msgBox.setFont(QFont(QString("Arial"), 14));
        msgBox.setText(e);
        msgBox.exec();
    }
}

void AddEquipment::cancelPressed()
{
    mDialog.close();
}

} // namespace Frontend
