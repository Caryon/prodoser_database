#ifndef DEVICE_FORM_H
#define DEVICE_FORM_H

#include <QWidget>

namespace Ui {
class DeviceForm;
}

class WeightAccumulationsModel;

class DeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceForm(const QString& name, QWidget *parent = nullptr);
    ~DeviceForm();

    void hideEvent(QHideEvent *event) override;

signals:
    void hidden();

private:
    Ui::DeviceForm *ui;

    WeightAccumulationsModel* weightAccumulationsModel;
};

#endif // DEVICE_FORM_H
