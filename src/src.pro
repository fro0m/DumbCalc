QT += quick
CONFIG += c++14 exceptions_off rtti_off

SOURCES += main.cpp \
    core/threadmanager.cpp \
    core/settingsmanager.cpp \
    DataModels/journalmodel.cpp \
    DataTypes/journalitem.cpp \
    Workers/calculatingthread.cpp \
    core/queuerequests.cpp \
    core/queueresults.cpp \
    Workers/queueswatcher.cpp

RESOURCES += qml.qrc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

win32-msvc* {
  contains(QMAKE_HOST.arch, x86_64) {
    QMAKE_LFLAGS         += /MACHINE:X64
  } else {
    QMAKE_LFLAGS         += /MACHINE:X86
  }
}

DEPENDPATH += $$PWD/../libs/include
INCLUDEPATH += $$PWD/../libs/include

# this is built only for MSVC2015
win32:CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../libs/Debug/calclib -lcalcLib
}
else:win32:CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../libs/Release/calclib -lcalcLib
}

HEADERS += \
    tests.h \
    core/threadmanager.h \
    core/settingsmanager.h \
    DataModels/journalmodel.h \
    DataTypes/journalitem.h \
    Workers/calculatingthread.h \
    DataTypes/task.h \
    DataTypes/result.h \
    core/queuerequests.h \
    core/queueresults.h \
    Workers/queueswatcher.h
