#include "modbus_protocol.h"
#include <QSerialPortInfo>
#include <QTimer>
#include <QDataStream>
#include <QDebug>

ModbusProtocol::ModbusProtocol(int timeoutMs, QObject *parent)
    : QSerialPort(parent)
    , timer(new QTimer(parent))
{

    connect(this, &QSerialPort::readyRead, this, &ModbusProtocol::onReadyRead);

    this->timer->setInterval(timeoutMs);
    this->timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &ModbusProtocol::onTimeout);
}

void ModbusProtocol::readHoldingRegisters(quint8 deviceNum, qint16 address, int num)
{
    this->deviceNum = deviceNum;
    this->memoryAddress = address;

    QByteArray buf;
    buf.append(deviceNum);
    buf.append(ReadHoldingRegisters);
    buf.append(address >> 8);
    buf.append(address & 0xff);
    buf.append(num >> 8);
    buf.append(num & 0xff);
    quint16 checksum = this->calcChecksum(buf);
    buf.append(checksum >> 8);
    buf.append(checksum & 0xff);

    this->write(buf);
    this->timer->start();
}

void ModbusProtocol::writeMultipleRegisters(quint8 deviceNum, qint16 address, int num, QByteArray data)
{
    this->deviceNum = deviceNum;
    this->memoryAddress = address;

    QByteArray buf;
    buf.append(deviceNum);
    buf.append(PresetMultipleRegisters);
    buf.append(address >> 8);
    buf.append(address & 0xff);
    buf.append(num >> 8);
    buf.append(num & 0xff);
    buf.append(num * 2);
    buf.append(data);
    quint16 checksum = this->calcChecksum(buf);
    buf.append(checksum >> 8);
    buf.append(checksum & 0xff);

    this->write(buf);
    this->timer->start();
}

void ModbusProtocol::readCoils(quint8 deviceNum, int num)
{
    this->deviceNum = deviceNum;

    QByteArray buf;
    ///

    this->write(buf);
    this->timer->start();
}

void ModbusProtocol::readDiscreteInputs(quint8 deviceNum, int num)
{
    this->deviceNum = deviceNum;

    QByteArray buf;
    ///

    this->write(buf);
    this->timer->start();
}

void ModbusProtocol::onTimeout()
{
    this->buf.clear();

    emit timeout(this->deviceNum);
}

void ModbusProtocol::onReadyRead()
{
    this->buf.append(this->readAll());

    if (this->isPacketFull(this->buf)) this->processPacket(this->buf);

    this->buf.clear();
}

bool ModbusProtocol::isPacketFull(const QByteArray& packet)
{
    const quint8 device = packet[0];
    const quint8 cmd = packet[1] & 0x7f;

    if (this->deviceNum != device) {
        qDebug() << "Device number mismatch:" << this->deviceNum << device;
        return false;
    }

    if (!this->availableCommands().contains(cmd)) return false;

    return (this->calcChecksum(packet) == 0);
}

void ModbusProtocol::processPacket(const QByteArray& packet)
{
    const quint8 device = packet[0];
    const quint8 cmd = packet[1] & 0x7f;
    const bool error = ((packet[1] & 0x80) != 0);

    if (error) emit this->error(device);

    switch (cmd) {
        case ReadHoldingRegisters:
        {
            const quint8 bytesNum = packet[2];
            this->memoryBlock.registers.clear();
            this->memoryBlock.address = this->memoryAddress;
            //QByteArray data = packet.mid(3, bytesNum);
            //for (int i = 0; i < bytesNum/2; i++) {
            //    quint16 reg = (data.at(i*2) << 8) + data.at(i*2 + 1);
            //    this->memoryBlock.registers << reg;
            //}
            QDataStream stream(packet.mid(3, bytesNum));
            quint8 reg;
            while (!stream.atEnd()) {
                stream >> reg;
                this->memoryBlock.registers << reg;
            }
        }
            emit success(device);
            break;

        case PresetMultipleRegisters:
            emit success(device);
            break;
    }

}

//for standard CRC16 (remainder of division)
//to start a new CRC, set CRC16 = SEED
//then for each byte call calcChecksum(byte, &checksum);
//checksum will contain the result
//(if you calculate all of the incoming data
//INCLUDING the CRC, the result should be 0x0000
//and if you are sending the CRC be sure to
//send the bytes in the correct order)
void crc16(unsigned char b, quint16* checksum)
{
    //const quint16 SEED = 0xFFFF;  //initialization for CRC16
    const quint16 GP = 0xa001;  //generating polynomial

   checksum[0] ^= b & 0xff;
   for (int i = 0; i < 8; i++) {
      char carry = checksum[0] & 0x0001;
      checksum[0]>>=1;
      if (carry) checksum[0] ^= GP;
   }
}

quint16 ModbusProtocol::calcChecksum(const QByteArray& frame)
{
    quint16 checksum = 0xffff; //initialization for CRC16

    foreach(quint8 b, frame) {
        crc16(b, &checksum);
    }

    return checksum;
}

QSet<quint8> ModbusProtocol::availableCommands() const
{
    static QSet<quint8> commands = {ReadCoilStatus, ReadDiscreteInputs, ReadHoldingRegisters, ReadInputRegisters, ForceSingleCoil, PresetSingleRegister, ReadExceptionStatus, ForceMultipleCoils, PresetMultipleRegisters, MaskWriteRegister, ReportSlaveID};
    return commands;
}
