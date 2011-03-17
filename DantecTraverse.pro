#-------------------------------------------------
#
# Project created by QtCreator 2010-07-28T15:14:45
#
#-------------------------------------------------

QT       += core gui

TARGET = DantecTraverse
TEMPLATE = app

#LIBS += -L"./qextserialport-build-desktop/build" -lqextserialport

SOURCES += main.cpp\
		mainwindow.cpp \
    qextserialport.cpp \
    qextserialenumerator.cpp \
    qextserialbase.cpp

HEADERS  += mainwindow.h \
    qextserialport.h \
    qextserialenumerator.h \
    qextserialbase.h

unix:HEADERS           += posix_qextserialport.h
unix:SOURCES           += posix_qextserialport.cpp
unix:DEFINES           += _TTY_POSIX_


win32:HEADERS          += win_qextserialport.h
win32:SOURCES          += win_qextserialport.cpp
win32:DEFINES          += _TTY_WIN_

win32:LIBS             += -lsetupapi

FORMS    += mainwindow.ui

OTHER_FILES +=
