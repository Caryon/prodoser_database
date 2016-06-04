#ifndef WEIGHTACCUMULATIONSMODEL_H
#define WEIGHTACCUMULATIONSMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>

class WeightAccumulationsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    struct ComponentData
    {
        int number;
        double weight;
        int amount;
        QDateTime time;

        enum { fieldsNum = 4 };
    };

    WeightAccumulationsModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

private:
    QList<ComponentData> componentsData;

    const QStringList headers;
};

#endif // WEIGHTACCUMULATIONSMODEL_H
