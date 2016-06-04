#include "device_form.h"
#include "ui_device_form.h"

#include "weight_accumulations_model.h"

#include <QDebug>

DeviceForm::DeviceForm(const QString& name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceForm)
    , weightAccumulationsModel(new WeightAccumulationsModel)
{
    ui->setupUi(this);

    this->setWindowTitle(name);
    this->setWindowFlags(Qt::Dialog);

    ui->tableView->setModel(this->weightAccumulationsModel);

    qDebug() << Q_FUNC_INFO;
}

DeviceForm::~DeviceForm()
{
    qDebug() << Q_FUNC_INFO;

    delete ui;
}

void DeviceForm::hideEvent(QHideEvent* event)
{
    emit this->hidden();
}
