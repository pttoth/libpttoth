#TEMPLATE = app
TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle qt
CONFIG += staticlib


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
    pttoth/src/math/constants.cpp \
    pttoth/test/test_config.hpp

HEADERS += \
    pttoth/include/pt/config.h \
    pttoth/include/pt/math.h \
    pttoth/include/pt/math/bool1.h \
    pttoth/include/pt/math/bool2.h \
    pttoth/include/pt/math/bool3.h \
    pttoth/include/pt/math/bool4.h \
    pttoth/include/pt/math/boolswizzle.h \
    pttoth/include/pt/math/float1.h \
    pttoth/include/pt/math/float2.h \
    pttoth/include/pt/math/float2swizzle.h \
    pttoth/include/pt/math/float3.h \
    pttoth/include/pt/math/float3swizzle.h \
    pttoth/include/pt/math/float4.h \
    pttoth/include/pt/math/float4swizzle.h \
    pttoth/include/pt/math/float4x4.h \
    pttoth/include/pt/math/floatswizzle.h \
    pttoth/include/pt/math/int1.h \
    pttoth/include/pt/math/int2.h \
    pttoth/include/pt/math/int3.h \
    pttoth/include/pt/math/int4.h \
    pttoth/include/pt/math/intswizzle.h \
    pttoth/include/pt/std_extension.hpp \
    pttoth/include/pt/event.hpp
