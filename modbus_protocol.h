#ifndef MODBUSPROTOCOL_H
#define MODBUSPROTOCOL_H

#include <QSerialPort>
#include <QSet>

class QSerialPortInfo;
class QTimer;

struct ModbusMemoryBlock
{
    quint16 address;
    QList<quint16> registers;
};

class ModbusProtocol : public QSerialPort
{
    Q_OBJECT
public:
    ModbusProtocol(int timeoutMs, QObject *parent = nullptr);

    void readHoldingRegisters(quint8 deviceNum, qint16 address, int num);
    void writeMultipleRegisters(quint8 deviceNum, qint16 address, int num, QByteArray data);
    void readCoils(quint8 deviceNum, int num);
    void readDiscreteInputs(quint8 deviceNum, int num);

signals:
    void timeout(quint8 deviceNum);
    void success(quint8 deviceNum);
    void error(quint8 deviceNum);

private slots:
    void onTimeout();
    void onReadyRead();

private:
    bool isPacketFull(const QByteArray& packet);
    void processPacket(const QByteArray& packet);
    quint16 calcChecksum(const QByteArray& frame);

    QSet<quint8> availableCommands() const;

private:
    QTimer* timer;

    quint8 deviceNum;
    quint16 memoryAddress;
    ModbusMemoryBlock memoryBlock;

    QByteArray buf;

    enum Commands : quint8
    {
        ReadCoilStatus = 0x01, //чтение значений из нескольких регистров флагов
        ReadDiscreteInputs = 0x02, //чтение значений из нескольких дискретных входов
        ReadHoldingRegisters = 0x03, //чтение значений из нескольких регистров хранения
        ReadInputRegisters = 0x04, //чтение значений из нескольких регистров ввода
        ForceSingleCoil = 0x05, //запись значения одного флага
        PresetSingleRegister = 0x06, //запись значения в один регистр хранения
        ReadExceptionStatus = 0x07, //Чтение сигналов состояния
        ForceMultipleCoils = 0x0F, //запись значений в несколько регистров флагов
        PresetMultipleRegisters = 0x10, //запись значений в несколько регистров хранения
        MaskWriteRegister = 0x16, //запись в один регистр хранения с использованием маски «И» и маски «ИЛИ»
        ReportSlaveID = 0x11 //Чтение информации об устройстве
    };
};

#endif // MODBUSPROTOCOL_H
