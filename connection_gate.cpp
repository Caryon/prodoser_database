#include "connection_gate.h"
#include "modbus_protocol.h"

#include <QSerialPort>
#include <QDebug>

ConnectionGate::ConnectionGate(QObject *parent)
    : QObject(parent)
{
}

ConnectionGate::~ConnectionGate()
{
}

void ConnectionGate::onHandshakeOk()
{
    ModbusProtocol* mb = qobject_cast<ModbusProtocol*>(sender());
    emit portFound(mb->portName());
    qDebug() << "PORT FOUND" << mb->portName();
}

void ConnectionGate::onHandshakeTimeout()
{
    ModbusProtocol* mb = qobject_cast<ModbusProtocol*>(sender());
    this->ports.removeOne(mb);
    delete mb;
}

void ConnectionGate::onHandshakeError()
{
    //repeat
}

void ConnectionGate::findPort()
{
    QList<QSerialPortInfo> available(QSerialPortInfo::availablePorts());
    QListIterator<QSerialPortInfo> portIterator(available);

    while (portIterator.hasNext()) {
        ModbusProtocol* mb = new ModbusProtocol(TimeoutMs, this);
        mb->setPort(portIterator.next());
        if (mb->open(QIODevice::ReadWrite)) {
            this->ports << mb;
            connect(mb, &ModbusProtocol::success, this, &ConnectionGate::onHandshakeOk);
            connect(mb, &ModbusProtocol::timeout, this, &ConnectionGate::onHandshakeTimeout);
            connect(mb, &ModbusProtocol::error, this, &ConnectionGate::onHandshakeError);
            mb->readHoldingRegisters(1, 0, 1); //TODO: эту хрень надо продумать, т.к. неизвестны номер устройства и скорость его обмена
        }
    }
}

