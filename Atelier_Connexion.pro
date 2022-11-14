#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += sql network multimedia multimediawidgets charts printsupport widgets axcontainer

LIBS += -LC:/OpenSSL-Win32/lib/MinGW -llibeay32
LIBS += -LC:/OpenSSL-Win32/lib/MinGW -lssleay32
INCLUDEPATH += C:/OpenSSL-Win32/include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    QrCode.cpp \
    affaires_judiciaires.cpp \
    exportexcelprojet.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    smtp.cpp

HEADERS += \
    QrCode.h \
    affaires_judiciaires.h \
    exportexcelprojet.h \
        mainwindow.h \
    connection.h \
    smtp.h

FORMS += \
        ../../../Downloads/formation_QT/formation_QT/camera.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../formation_QT/formation_QT/libeay32.dll \
    ../../formation_QT/formation_QT/ssleay32.dll

RESOURCES += \
    Hi.qrc \
    Image.qrc
