#-------------------------------------------------
#
# Project created by QtCreator 2010-07-28T15:14:45
#
#-------------------------------------------------

QT       += core gui

TARGET = DantecTraverse
TEMPLATE = app

LIBS += -L"../qesp/lib" -lqextserialport1

SOURCES += main.cpp\
		mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES +=
