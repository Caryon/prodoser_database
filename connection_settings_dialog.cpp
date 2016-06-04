#include "connection_settings_dialog.h"
#include "ui_connection_settings_dialog.h"

#include <QDebug>

ConnectionSettingsDialog::ConnectionSettingsDialog(const Config& config, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSettingsDialog)
{
    qDebug() << Q_FUNC_INFO << config.a;

    ui->setupUi(this);

    connect(this, &QDialog::accepted, this, &QDialog::deleteLater);
    connect(this, &QDialog::rejected, this, &QDialog::deleteLater);
}

ConnectionSettingsDialog::~ConnectionSettingsDialog()
{
    qDebug() << Q_FUNC_INFO;

    delete ui;
}
