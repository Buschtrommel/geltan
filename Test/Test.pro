TEMPLATE = app

TARGET = geltanTest

QT += network quick widgets qml webengine

CONFIG += c++11

SOURCES += \
    main.cpp \
    gtconfig.cpp \
    PP/authenticationtest.cpp

INSTALLS += target


RESOURCES = qml.qrc

HEADERS += \
    gtconfig.h \
    PP/authenticationtest.h

LIBS += -L$$OUT_PWD/../Geltan -lgeltan
INCLUDEPATH += $$PWD/../

target.path = /usr/bin
INSTALLS += target
