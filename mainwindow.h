#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class DeviceForm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionConnection_triggered();
    void on_actionAddDevice_triggered();

    void removeDevice();

private:
    Ui::MainWindow *ui;

    QMap<QString, DeviceForm*> devices;

    enum
    {
        MaximumDevices = 4
    };
};

#endif // MAINWINDOW_H
