#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T10:25:22
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gps_emulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../beacon_2/sv_udpstream.cpp \
    ../beacon_2/converting.cpp \
    ../../../Common/sv_settings.cpp

HEADERS  += mainwindow.h \
    ../beacon_2/sv_udpstream.h \
    ../beacon_2/converting.h \
    ../../../Common/sv_settings.h

FORMS    += mainwindow.ui
