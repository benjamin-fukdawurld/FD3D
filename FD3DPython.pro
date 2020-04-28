#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:28:10
#
#-------------------------------------------------

TARGET = FD3DPython
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += link_pkgconfig
PKGCONFIG += python3

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib -lFDCore -lFD3D \
    -L../thirdparty/assimp/bin \
    -lassimp

INCLUDEPATH += include \
    ../FDCore/include \
    ../thirdparty/glm \
    ../thirdparty/assimp/include \
    ../thirdparty/pybind11/include \

SOURCES += \
    src/Glm_vec_python.cpp \
    src/Projection_python.cpp \
    src/VertexProxy_python.cpp \
    src/Component_python.cpp \
    src/SceneNode_python.cpp \
    src/Transform_python.cpp \
    src/Behavior_python.cpp \
    src/Scene_python.cpp \
    src/Camera_python.cpp \
    src/Light_python.cpp \
    src/Material_python.cpp \
    src/Mesh_python.cpp

HEADERS += \
    include/FD3D/Binding/Python/FD3DPython.h \
    include/FD3D/Binding/Python/Glm_vec_python.h \
    include/FD3D/Binding/Python/Projection_python.h \
    include/FD3D/Binding/Python/VertexProxy_python.h \
    include/FD3D/Binding/Python/Component_python.h \
    include/FD3D/Binding/Python/SceneNode_python.h \
    include/FD3D/Binding/Python/Transform_python.h \
    include/FD3D/Binding/Python/Behavior_python.h \
    include/FD3D/Binding/Python/Scene_python.h \
    include/FD3D/Binding/Python/Camera_python.h \
    include/FD3D/Binding/Python/Light_python.h \
    include/FD3D/Binding/Python/Material_python.h \
    include/FD3D/Binding/Python/Mesh_python.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
