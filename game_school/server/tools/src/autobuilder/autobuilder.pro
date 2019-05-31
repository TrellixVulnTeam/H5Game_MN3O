#-------------------------------------------------
#
# Project created by QtCreator 2014-06-15T10:30:13
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = autobuilder
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    pw_gdb_chunks.cpp \
    pw_gdb_platform.cpp \
    pw_gdb_reader_writer.cpp \
    pw_gdb_socket_base_connection.cpp \
    pw_gdb_socket_client.cpp \
    pw_gdb_socket_connection.cpp \
    pw_gdb_socket_listener.cpp \
    pw_gdb_socket_reactor_linux.cpp \
    pw_gdb_socket_reactor_select.cpp \
    pw_gdb_socket_reactor_win32.cpp \
    pw_gdb_socket_utils.cpp

HEADERS += \
    pw_gdb_chunks.h \
    pw_gdb_linked_ptr.h \
    pw_gdb_platform.h \
    pw_gdb_reader_writer.h \
    pw_gdb_refcounted.h \
    pw_gdb_socket_base_connection.h \
    pw_gdb_socket_client.h \
    pw_gdb_socket_connection.h \
    pw_gdb_socket_listener.h \
    pw_gdb_socket_reactor.h \
    pw_gdb_socket_reactor_linux.h \
    pw_gdb_socket_reactor_select.h \
    pw_gdb_socket_reactor_win32.h \
    pw_gdb_socket_utils.h \
    pw_gdb_stdint.h
