#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T16:38:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT +=multimedia

QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = calismiyo
TEMPLATE = app

CONFIG += mobility

SOURCES += main.cpp\
        anaekran.cpp \
    qcustomplot.cpp \
    dialog.cpp

HEADERS  += anaekran.h \
    qcustomplot.h \
    dialog.h

FORMS    += anaekran.ui \
    dialog.ui

RESOURCES += \
    resources.qrc






