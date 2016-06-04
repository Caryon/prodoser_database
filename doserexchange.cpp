#include "doserexchange.h"
#include "modbus_protocol.h"

#include <QDebug>

DoserExchange::DoserExchange(QObject *parent)
    : protocol(new ModbusProtocol(Timeout, parent))
{
    connect(protocol, &ModbusProtocol::success, this, &DoserExchange::onSuccess);
    connect(protocol, &ModbusProtocol::error, this, &DoserExchange::onError);
    connect(protocol, &ModbusProtocol::timeout, this, &DoserExchange::onTimeout);
}

DoserExchange::~DoserExchange()
{
    delete protocol;
}

bool DoserExchange::addDevice(quint8 deviceNum)
{
    if (this->devices.contains(deviceNum)) {
        qDebug() << "Device number" << deviceNum << "already in queue";
        return false;
    }

    this->devices[deviceNum] = DoserMemoryModel();
    return true;
}

void DoserExchange::removeDevice(quint8 deviceNum)
{
    this->devices.remove(deviceNum);
}

void DoserExchange::onSuccess()
{

}

void DoserExchange::onError()
{

}

void DoserExchange::onTimeout()
{

}

void DoserExchange::next()
{

}
