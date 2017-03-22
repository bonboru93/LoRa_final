#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T15:33:42
#
#-------------------------------------------------

QT       += core gui serialport sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SOSoLR_Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialcom.cpp \
    newserver.cpp \
    dbmanager.cpp \
    mapmanager.cpp

HEADERS  += mainwindow.h \
    serialcom.h \
    newserver.h \
    dbmanager.h \
    mapmanager.h

FORMS    += mainwindow.ui \
    newclient.ui \
    newserver.ui

DISTFILES +=

RESOURCES +=
