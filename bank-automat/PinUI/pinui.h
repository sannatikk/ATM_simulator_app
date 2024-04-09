#ifndef PINUI_H
#define PINUI_H
#include "PinUI_global.h"
#include <QDialog>

namespace Ui {
class PinUI;
}

class PINUI_EXPORT PinUI : public QDialog
{
    Q_OBJECT

public:
    explicit PinUI(QWidget *parent = nullptr);
    ~PinUI();

signals:
    void pincodeSignal(QString);

private slots:
    void setLoginResponseSlot(QString);
    void handleButtonClick();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();
    void on_btn0_clicked();
    void on_btnBackspace_clicked();
    void on_btnQuit_clicked();

private:
    Ui::PinUI *ui;
    void handleNumberClick(QString);
    QString enteredNumber;
    QString stars;
};

#endif // PINUI_H
