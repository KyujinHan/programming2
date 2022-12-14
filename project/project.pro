QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    category_menu.cpp \
    dialog.cpp \
    dialog_delete.cpp \
    main.cpp \
    mainwindow.cpp \
    planning.cpp \
    recordplan.cpp \
    secmainwindow.cpp \
    summary.cpp \

HEADERS += \
    category_menu.h \
    dialog.h \
    dialog_delete.h \
    mainwindow.h \
    planning.h \
    recordplan.h \
    secmainwindow.h \
    summary.h

FORMS += \
    category_menu.ui \
    dialog.ui \
    dialog_delete.ui \
    mainwindow.ui \
    planning.ui \
    recordplan.ui \
    secmainwindow.ui \
    summary.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=

