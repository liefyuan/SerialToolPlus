QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    serialportplus.cpp

HEADERS += \
    fftw-3.3.5-dll64/fftw3.h \
    mainwindow.h \
    qcustomplot.h \
    serialportplus.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:  LIBS  +=  $$PWD/fftw-3.3.5-dll64/libfftw3-3.lib
unix:  LIBS  +=  -L$$PWD/fftw-3.3.5-dll64/  -lfftw3-3
