QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

RC_FILE = logo.rc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/tools/fileparser.cpp \
    src/tools/model.cpp \
    src/tools/util.cpp \
    src/ui/fileparsewin.cpp \
    main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/parseservicewin.cpp \
    third-party/qftp/qftp.cpp

HEADERS += \
    src/tools/fileparser.h \
    src/tools/iparser.h \
    src/tools/model.h \
    src/tools/util.h \
    src/ui/fileparsewin.h \
    src/ui/mainwindow.h \
    src/ui/parseservicewin.h \
    third-party/qftp/qftp.h

INCLUDEPATH += \
    third-party

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
