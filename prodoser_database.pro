#-------------------------------------------------
#
# Project created by QtCreator 2015-07-11T22:24:12
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prodoser_database
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        modbus_protocol.cpp \
        connection_gate.cpp \
    doserexchange.cpp \
    doser_memory_model.cpp \
    connection_settings_dialog.cpp \
    device_form.cpp \
    weight_accumulations_model.cpp

HEADERS  += mainwindow.h \
        modbus_protocol.h \
        connection_gate.h \
    doserexchange.h \
    doser_memory_model.h \
    connection_settings_dialog.h \
    device_form.h \
    weight_accumulations_model.h

FORMS    += mainwindow.ui \
    connection_settings_dialog.ui \
    device_form.ui

#QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
