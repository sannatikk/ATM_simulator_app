#ifndef RFIDREADER_H
#define RFIDREADER_H
#include <QSerialPort>
#include <QObject>
#include <QDebug>
#include "RFIDReader_global.h"

class RFIDREADER_EXPORT RFIDReader : public QObject
{
    Q_OBJECT
public:
    RFIDReader(QObject * parent = nullptr);

signals:
    void serialSignal(QString);

private slots:
    void serialReceived();
    void handleCloseSerial();
    void handleOpenSerial();

private:
    QSerialPort *serial;

    QString checkRFIDPort(QString);

};

#endif // RFIDREADER_H
