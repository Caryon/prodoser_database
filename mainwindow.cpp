#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "connection_settings_dialog.h"
#include "device_form.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionConnection_triggered()
{
    ConnectionSettingsDialog::Config config;

    QDialog* dialog = new ConnectionSettingsDialog(config, this);

    dialog->show();
}

void MainWindow::on_actionAddDevice_triggered()
{
    const QString id = QString::number(this->devices.size()); //TODO: set name
    DeviceForm* device = new DeviceForm(id, this);

    this->devices[id] = device;

    device->show();

    connect(device, &DeviceForm::hidden, this, &MainWindow::removeDevice);
}

void MainWindow::removeDevice()
{
    DeviceForm* device = qobject_cast<DeviceForm*>(this->sender());

    const QString id = device->windowTitle();

    qDebug() << "removed device" << id;

    this->devices.remove(id);
    device->deleteLater();
}

