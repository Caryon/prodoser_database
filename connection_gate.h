#ifndef CONNECTIONGATE_H
#define CONNECTIONGATE_H

#include <QObject>
#include <QList>
#include <QSerialPortInfo>

class QSerialPort;
class QSerialPortInfo;
class ModbusProtocol;

class ConnectionGate : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionGate(QObject *parent = 0);
    virtual ~ConnectionGate();

    void findPort();

signals:
    void portFound(const QString& portName);

private slots:
    void onHandshakeOk();
    void onHandshakeTimeout();
    void onHandshakeError();

private:
    QList<ModbusProtocol*> ports;

    enum {
        TimeoutMs = 1000
    };
};

#endif // CONNECTIONGATE_H
