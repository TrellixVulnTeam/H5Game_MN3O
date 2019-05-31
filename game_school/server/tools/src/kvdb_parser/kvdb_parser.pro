TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pw_gdb_parser.cpp \
    pw_gdb_generator.cpp \
    pw_gdb_idl.cpp

HEADERS += \
    pw_gdb_parser.h \
    pw_gdb_generator.h \
    pw_gdb_idl.h

