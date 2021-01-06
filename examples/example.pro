QT += core gui widgets
CONFIG += c++17

SOURCES += \
    ../CreateHandler.cpp \
    ../DeleteHandler.cpp \
    ../ResizeHandler.cpp \
    ../SignalerGraphicsView.cpp \
    ../ZoomHandler.cpp \
    MainWidget.cpp \
    main.cpp

HEADERS += \
    ../CreateHandler.h \
    ../DeleteHandler.h \
    ../ResizeHandler.h \
    ../ResizeMode.h \
    ../SignalerGraphicsView.h \
    ../ZoomHandler.h \
    MainWidget.h

FORMS += \
    MainWidget.ui
