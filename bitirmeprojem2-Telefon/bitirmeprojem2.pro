#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T16:38:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bitirmeprojem2
TEMPLATE = app

CONFIG += mobility
MOBILITY =
SOURCES += main.cpp\
        anaekran.cpp

HEADERS  += anaekran.h

FORMS    += anaekran.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \


ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android




