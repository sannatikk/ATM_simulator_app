#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir("../styles");
    QString stylesFolder = dir.absolutePath();
    QString cssFilePath = stylesFolder + "/myStyle.qss";

    QFile file(cssFilePath);

    if (!file.open(QFile::ReadOnly)) {
        // Tiedoston avaaminen epäonnistui
        qDebug()<<"Tyylitiedoston avaus epäonnistui";
            return -1;
    }

    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
