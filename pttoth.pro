TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

Release:DESTDIR     = $$PWD/bin/release
Release:OBJECTS_DIR = $$PWD/bin/release/.obj
Release:MOC_DIR     = $$PWD/bin/release/.moc
Release:RCC_DIR     = $$PWD/bin/release/.rcc
Release:UI_DIR      = $$PWD/bin/release/.ui

Debug:DESTDIR       = $$PWD/bin/debug
Debug:OBJECTS_DIR   = $$PWD/bin/debug/.obj
Debug:MOC_DIR       = $$PWD/bin/debug/.moc
Debug:RCC_DIR       = $$PWD/bin/debug/.rcc
Debug:UI_DIR        = $$PWD/bin/debug/.ui


INCLUDEPATH += ./pttoth/include \
               ./pttoth

#LIBS +=


SOURCES += main.cpp \
    pttoth/src/config.cpp \
    pttoth/test/test_config.hpp

#HEADERS +=

HEADERS += \
    pttoth/include/pttoth/config.h \
    pttoth/include/pttoth/std_extension.hpp
