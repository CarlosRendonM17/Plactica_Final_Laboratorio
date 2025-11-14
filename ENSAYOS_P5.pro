TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Obstaculo.cpp \
        Particula.cpp \
        Simulador.cpp \
        Vector2.cpp \
        main.cpp

HEADERS += \
    Obstaculo.h \
    Particula.h \
    Simulador.h \
    Vector2.h

DISTFILES += \
    salida.txt
