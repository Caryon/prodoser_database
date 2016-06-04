#include "weight_accumulations_model.h"

WeightAccumulationsModel::WeightAccumulationsModel(QObject* parent)
    : QAbstractTableModel(parent)
    , headers{tr("component"), tr("weight"), tr("amount"), tr("time")}
{

}

int WeightAccumulationsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return this->componentsData.size();
}

int WeightAccumulationsModel::columnCount(const QModelIndex& parent) const
{
    return ComponentData::fieldsNum;
}

QVariant WeightAccumulationsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= componentsData.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
        const ComponentData dat = componentsData.at(index.row());
        switch(index.column()) {
            case 0:
                return QString::number(dat.number);
            case 1:
                return QString::number(dat.weight);
            case 2:
                return QString::number(dat.amount);
            case 3:
                return dat.time.toString();
            default:
                return QVariant();
        }
    }
    else
        return QVariant();
}

QVariant WeightAccumulationsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.at(section);
    else
        return QString("Row %1").arg(section);
}
