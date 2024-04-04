#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QDialog>

namespace Ui {
class Keyboard;
}

class Keyboard : public QDialog
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = nullptr);
    ~Keyboard();

private slots:
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
    void on_btnDelete_clicked();
    void on_btnEnter_clicked();
    void on_btnExit_clicked();

signals:
    void sendEnteredNumber(QString);

private:
    QString enteredNumber;
    void numberClickHandler(QString);
    Ui::Keyboard *ui;
};

#endif // KEYBOARD_H
