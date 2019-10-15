#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:57:00
#
#-------------------------------------------------
TARGET = FD3D
TEMPLATE = lib
CONFIG += console c++17
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/.obj/$${TARGET}

DEPENDPATH += \
    include \
    ../thirdparty/glm \

INCLUDEPATH += \
    include \
    ../thirdparty/glm \

SOURCES += \
    src/Light.cpp \
    src/Material.cpp \
    src/Projection.cpp \
    src/Transform.cpp \
    src/Camera.cpp \

HEADERS += \
    include/FD3D/Light.h \
    include/FD3D/Material.h \
    include/FD3D/Projection.h \
    include/FD3D/Transform.h \
    include/FD3D/Camera.h \
    include/FD3D/Vertex.h \
    include/FD3D/Texture.h \
    include/FD3D/Mesh.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
