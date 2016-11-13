#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T22:06:43
#
#-------------------------------------------------

QT       += core gui
QT       +=sql
QT  +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = untitled8
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    dialog.cpp


HEADERS  += mainwindow.h \
    qcustomplot.h \
    dialog.h


FORMS    += mainwindow.ui \
    dialog.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resource.qrc

