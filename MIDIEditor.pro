#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T14:12:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MIDIEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    miditest.cpp \
    strummify.cpp \
    parsetrack.cpp \
    changenote.cpp \
    changedelta.cpp \
    changevolume.cpp \
    overwritemid.cpp

HEADERS  += mainwindow.h \
    miditest.h \
    strummify.h \
    parsetrack.h \
    changenote.h \
    changedelta.h \
    changevolume.h \
    overwritemid.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3238/midifile/lib/release/ -lmidifile
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3238/midifile/lib/debug/ -lmidifile
else:unix: LIBS += -L$$PWD/../3238/midifile/lib/ -lmidifile

INCLUDEPATH += $$PWD/../3238/midifile/include
DEPENDPATH += $$PWD/../3238/midifile/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3238/midifile/lib/release/libmidifile.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3238/midifile/lib/debug/libmidifile.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3238/midifile/lib/release/midifile.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3238/midifile/lib/debug/midifile.lib
else:unix: PRE_TARGETDEPS += $$PWD/../3238/midifile/lib/libmidifile.a
