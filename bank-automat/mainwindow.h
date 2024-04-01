#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rfidreader.h"
#include "pinui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //void reset();

signals:
    void closeSerialSignal();
    void openSerialSignal();

private slots:
    void setSerialID(QString);

private:
    Ui::MainWindow *ui;
    RFIDReader *RFID_dll;
    PinUI *PinUI_dll;
};
#endif // MAINWINDOW_H
