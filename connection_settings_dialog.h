#ifndef CONNECTION_SETTINGS_DIALOG_H
#define CONNECTION_SETTINGS_DIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionSettingsDialog;
}

class ConnectionSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    struct Config
    {
        int a;
    };

    explicit ConnectionSettingsDialog(const Config& config, QWidget *parent = nullptr);
    ~ConnectionSettingsDialog();

private:
    Ui::ConnectionSettingsDialog *ui;
};

#endif // CONNECTION_SETTINGS_DIALOG_H
