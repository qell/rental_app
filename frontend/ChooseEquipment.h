#pragma once

#include "common.h"
#include "ui_chooseequipment.h"
#include <QDialog>
#include <QObject>

namespace Backend {
class Database;
} // namespace Backend

namespace Frontend {

class ChooseEquipment : public QObject
{
    Q_OBJECT

    Ui::ChooseEquipment*                 mUi;
    QDialog                              mDialog;
    Backend::Database&                   mDatabase;
    QVector<Common::EquipmentParameters> mEquipment;

    void printDefaultTable(void);
    void printEquipment();

public:
    explicit ChooseEquipment(Backend::Database& database);
    void exec();

signals:
    void equipmentChosen(const Common::EquipmentParameters& eq);

public slots:
    void addPressed();
    void cancelPressed();
    void equipmentTypeChanged(int index);
};
} // namespace Frontend
