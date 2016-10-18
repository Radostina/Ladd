#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T15:21:55
#
#-------------------------------------------------

QT       += core gui serialport

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ladd
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    settingspage.cpp \
    data/config.cpp \
    data/input.cpp \
    data/inputinfo.cpp \
    data/output.cpp \
    communicator/basecommunicator.cpp \
    communicator/parallelcommunicator.cpp \
    ladder/branch.cpp \
    ladder/ladder.cpp \
    ladder/ladderentities.cpp \
    parser/ladderparser.cpp \
    parser/configparser.cpp \
    controller/maincontroller.cpp \
    controller/communicationcontroller.cpp \
    data/pendingoutput.cpp \
    parser/fileparser.cpp \
    communicator/serialcommunicator.cpp

HEADERS  += widget.h \
        settingspage.h \
    data/config.h \
    data/input.h \
    data/inputinfo.h \
    data/output.h \
    data/outputinfo.h \
    communicator/basecommunicator.h \
    communicator/parallelcommunicator.h \
    ladder/branch.h \
    ladder/ladder.h \
    ladder/ladderentities.h \
    parser/ladderparser.h \
    parser/configparser.h \
    controller/maincontroller.h \
    controller/communicationcontroller.h \
    data/pendingoutput.h \
    parser/fileparser.h \
    communicator/serialcommunicator.h
