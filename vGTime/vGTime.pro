QT = gui core widgets svg xml

TEMPLATE = lib
DEFINES += VGTIME_LIBRARY

CONFIG += c++1z

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    vgtime.cpp

HEADERS += \
    vGTime_global.h \
    vgtime.h

INCLUDEPATH += \
    "../../vGLsumtp/vGCore" \
    "../../vGLsumtp/public"
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
CONFIG(debug,debug|release):DESTDIR = $$PWD/../plugins/debug
else: DESTDIR = $$PWD/../plugins/release

!isEmpty(target.path): INSTALLS += target

FORMS += \
    vgtime.ui

RESOURCES += \
    vGTime.qrc
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../vGLsumtp/vGCore/release/ -lvGCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../vGLsumtp/vGCore/debug/ -lvGCore
else:unix: LIBS += -L$$OUT_PWD/../../vGLsumtp/vGCore/ -lvGCore

INCLUDEPATH += $$PWD/../../vGLsumtp/vGCore
DEPENDPATH += $$PWD/../../vGLsumtp/vGCore
