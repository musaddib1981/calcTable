#-------------------------------------------------
#
# Project created by QtCreator 2017-07-12T13:25:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calcTable
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel1.cpp \
    doublespinboxdelegate.cpp \
    comboboxdelegate.cpp \
    tabledata.cpp \
    levels.cpp \
    tablemodel2.cpp \
    orders.cpp

HEADERS  += mainwindow.h \
    tablemodel1.h \
    doublespinboxdelegate.h \
    comboboxdelegate.h \
    tabledata.h \
    levels.h \
    tablemodel2.h \
    orders.h

QMAKE_CXXFLAGS += -std=c++11
