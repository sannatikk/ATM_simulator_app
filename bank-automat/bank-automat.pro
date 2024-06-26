QT       += core gui
QT += serialport
QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountselect.cpp \
    balance.cpp \
    customwithdrawal.cpp \
    environment.cpp \
    main.cpp \
    mainwindow.cpp \
    transactions.cpp \
    usermenu.cpp \
    withdrawal.cpp

HEADERS += \
    accountselect.h \
    balance.h \
    customwithdrawal.h \
    environment.h \
    mainwindow.h \
    transactions.h \
    usermenu.h \
    withdrawal.h

FORMS += \
    accountselect.ui \
    balance.ui \
    customwithdrawal.ui \
    mainwindow.ui \
    transactions.ui \
    usermenu.ui \
    withdrawal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#RFIDReader dll
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/RFIDReader/build/release/ -lRFIDReader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/RFIDReader/build/debug/ -lRFIDReader
else:unix: LIBS += -L$$PWD/RFIDReader/build/ -lRFIDReader

INCLUDEPATH += $$PWD/RFIDReader
DEPENDPATH += $$PWD/RFIDReader

#PinUI dll
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/PinUI/build/release/ -lPinUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/PinUI/build/debug/ -lPinUI
else:unix: LIBS += -L$$PWD/PinUI/build/ -lPinUI

INCLUDEPATH += $$PWD/PinUI
DEPENDPATH += $$PWD/PinUI


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/LoginHandler/build/release/ -lLoginHandler
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/LoginHandler/build/debug/ -lLoginHandler
else:unix: LIBS += -L$$PWD/LoginHandler/build/ -lLoginHandler

INCLUDEPATH += $$PWD/LoginHandler
DEPENDPATH += $$PWD/LoginHandler

DISTFILES += \
    styles/myStyle.qss
