TARGET = QtTest

CONFIG += qt
CONFIG += debug

HEADERS += Params.hh
HEADERS += Args.hh
HEADERS += QtTest.hh
HEADERS += CannonField.hh
HEADERS += GameBoard.hh
HEADERS += LcdRange.hh

SOURCES += Params.cc
SOURCES += Args.cc
SOURCES += Main.cc
SOURCES += QtTest.cc
SOURCES += CannonField.cc
SOURCES += GameBoard.cc
SOURCES += LcdRange.cc

DEFINES += LINUX
DEFINES += _BSD_TYPES
DEFINES += F_UNDERSCORE2
DEFINES += _LARGEFILE_SOURCE
DEFINES += _FILE_OFFSET_BITS=64

INCLUDEPATH += /home/dixon/cvs/include
INCLUDEPATH += /home/dixon/projDir/include

LIBS += -L/home/dixon/cvs/lib
LIBS += -ltoolsa
LIBS += -ltdrp


