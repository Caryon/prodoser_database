#ifndef DOSEREXCHANGE_H
#define DOSEREXCHANGE_H

#include <QObject>
#include <QMap>
#include "doser_memory_model.h"

class ModbusProtocol;

class DoserExchange : public QObject
{
public:
    DoserExchange(QObject *parent = nullptr);
    virtual ~DoserExchange();

    bool addDevice(quint8 deviceNum);
    void removeDevice(quint8 deviceNum);

private:
    void onSuccess();
    void onError();
    void onTimeout();

    void next();

private:
    enum {
        Timeout = 1000
    };

    ModbusProtocol* protocol;

    QMap<quint8, DoserMemoryModel> devices;
};

#endif // DOSEREXCHANGE_H
