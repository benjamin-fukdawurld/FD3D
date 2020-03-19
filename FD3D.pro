#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:57:00
#
#-------------------------------------------------
TARGET = FD3D
TEMPLATE = lib
CONFIG += console c++17
#CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/.obj/$${TARGET}

LIBS += \
    -L../thirdparty/assimp/bin \
    -lassimp

INCLUDEPATH += \
    include \
    ../FDCore/include \
    ../thirdparty/glm \
    ../thirdparty/assimp/include \

SOURCES += \
    src/AbstractMesh.cpp \
    src/Component.cpp \
    src/IndexProxy.cpp \
    src/Light.cpp \
    src/Material.cpp \
    src/Mesh.cpp \
    src/Projection.cpp \
    src/Scene.cpp \
    src/SceneLoader.cpp \
    src/SceneNode.cpp \
    src/Texture.cpp \
    src/Transform.cpp \
    src/Camera.cpp \
    src/ModelLoader.cpp \
    src/VertexProxy.cpp

HEADERS += \
    include/FD3D/SceneGraph/Component.h \
    include/FD3D/SceneGraph/SceneLoader.h \
    include/FD3D/SceneGraph/Scene.h \
    include/FD3D/SceneGraph/SceneNode.h \
    \
    include/FD3D/Light/Light.h \
    \
    include/FD3D/Camera/Camera.h \
    include/FD3D/Camera/Projection.h \
    \
    include/FD3D/Material/Material.h \
    include/FD3D/Material/Texture.h \
    \
    include/FD3D/Utils/IndexProxy.h \
    include/FD3D/Utils/Vertex.h \
    include/FD3D/Utils/Transform.h \
    include/FD3D/Utils/VertexProxy.h \
    \
    include/FD3D/Mesh/AbstractMesh.h \
    include/FD3D/Mesh/Model.h \
    include/FD3D/Mesh/Mesh.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}
