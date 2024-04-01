#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RFID_dll = new RFIDReader(this);

    //Connect closeSerialSignal to library
    connect(this, SIGNAL(closeSerialSignal()),
            RFID_dll, SLOT(handleCloseSerial()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSerialID(QString data)
{
    qDebug() << data;

    emit closeSerialSignal();

    PinUI_dll = new PinUI(this);
    PinUI_dll->show();
}

