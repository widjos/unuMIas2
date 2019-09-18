TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Analisis/parser.cpp \
        Analisis/scanner.cpp \
        main.cpp \
        operation.cpp

HEADERS += \
    Analisis/Lexicon.l \
    Analisis/Syntact.y \
    Analisis/parser.h \
    Analisis/parser.h \
    Analisis/scanner.h \
    Analisis/scanner.h \
    operation.h
