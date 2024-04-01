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
    void handleButtonClick();
private:
    Ui::PinUI *ui;
};

#endif // PINUI_H
