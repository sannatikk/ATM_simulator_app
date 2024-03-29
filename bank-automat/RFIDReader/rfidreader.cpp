#include "rfidreader.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <QSerialPortInfo>

RFIDReader::RFIDReader(QObject * parent) : QObject(parent)
{
    QString targetProductID = "OL56DED005B8E8A";

    serial = new QSerialPort(this);
    QString portName = checkRFIDPort(targetProductID);
    if (portName != "") {
        serial->setPortName(portName);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->open(QIODevice::ReadOnly);  //Open serial port for read-only

        connect(serial, SIGNAL(readyRead()),
                this, SLOT(serialReceived()));  //Send signal to serialReceived if data is read

        qDebug() << "Serialport ready to read data...";
    }
    else {
        qDebug() << "RFID reader not found";
    }
}

void RFIDReader::serialReceived()
{
    QByteArray data;

    data = serial->readAll();   //Read data from serialport to variable

    //Parse data to wanted form
    data.erase(std::remove_if(data.begin(), data.end(), [](unsigned char x){return std::isspace(x);}),data.end());
    data.erase(std::remove(data.begin(), data.end(), '-'), data.end());
    data.erase(std::remove(data.begin(), data.end(), '>'), data.end());

    connect(this, SIGNAL(serialSignal(QString)),
            this->parent(), SLOT(setSerialID(QString)));

    QString result = QString(data); //Convert data to QString

    emit serialSignal(result);
}

void RFIDReader::handleCloseSerial()
{
    serial->close();
    qDebug() << "Serialport closed";
}

void RFIDReader::handleOpenSerial()
{
    serial->open(QIODevice::ReadOnly);
    qDebug() << "Serialport opened";
}

QString RFIDReader::checkRFIDPort(QString deviceID)
{
    QList portList = QSerialPortInfo::availablePorts(); //Check available ports

    //Iterate portlist to see if it matches to deviceID
    for (const QSerialPortInfo &portInfo : portList) {
        if (portInfo.serialNumber() == deviceID) {
            qDebug() << "RFID reader found on port: " << portInfo.portName();
            return portInfo.portName();
        }
    }
    qDebug() << "Target device not found";
    return "";
}
