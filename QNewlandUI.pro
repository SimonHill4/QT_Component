#-------------------------------------------------
#
# Project created by QtCreator 2019-09-02T08:45:03
#
#-------------------------------------------------

QT       += widgets

TARGET = QNewlandUI
TEMPLATE = lib

DEFINES += QNEWLANDUI_LIBRARY
DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES +=\
    qnbutton.cpp \
    qnlistinfo.cpp \
    qnrangeselector.cpp \
    qntitle.cpp \
    desklistwidget.cpp \
    qndesktop.cpp \
    qninputbar.cpp \
    qnpopwindow.cpp \
    qnprogressbar.cpp \
    qnstatusbar.cpp \
    qncombobox.cpp \
    qnlabinfo.cpp \
    qnpushbutton.cpp \
    qcomboboxreload.cpp
QMAKE_CFLAGS   += -flto -Os
QMAKE_CXXFLAGS += -flto -Os
QMAKE_LFLAGS   += -flto -Os -Wl,--hash-style=gnu -Wl,--as-needed
HEADERS +=\
    qnbutton.h \
    qnlistinfo.h \
    qnrangeselector.h \
    qntitle.h \
    desklistwidget.h \
    qndesktop.h \
    qninputbar.h \
    qnpopwindow.h \
    qnprogressbar.h \
    qnstatusbar.h \
    qncombobox.h \
    qnlabinfo.h \
    qnpushbutton.h \
    qcomboboxreload.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


