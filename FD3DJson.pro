#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:28:10
#
#-------------------------------------------------

TARGET = FD3DJson
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib -lFDCore -lFD3D -lFDSerialize -lFDJson \
    -L../thirdparty/assimp/bin \
    -lassimp

INCLUDEPATH += include \
    ../FDSerialize/include \
    ../FDCore/include \
    ../FDJson/include \
    ../thirdparty/rapidjson/include \
    ../thirdparty/glm \
    ../thirdparty/assimp/include \

SOURCES += \
    src/Glm_Json_utils.cpp \
    src/VertexProxy_Json.cpp \
    src/Transform_Json.cpp \
    src/Projection_Json.cpp \
    src/Camera_Json.cpp \
    src/Light_Json.cpp \
    src/Material_Json.cpp \
    src/Mesh_Json.cpp \
    src/Component_Json.cpp \
    src/SceneNode_Json.cpp

HEADERS += \
    include/FD3D/Serialization/Json/Glm_Json_fwd.h \
    include/FD3D/Serialization/Json/Glm_Json_utils.h \
    include/FD3D/Serialization/Json/VertexProxy_Json.h \
    include/FD3D/Serialization/Json/Transform_Json.h \
    include/FD3D/Serialization/Json/Projection_Json.h \
    include/FD3D/Serialization/Glm_Serialize_utils.h \
    include/FD3D/Serialization/Json/Camera_Json.h \
    include/FD3D/Serialization/Json/Light_Json.h \
    include/FD3D/Serialization/Json/Material_Json.h \
    include/FD3D/Serialization/Json/Mesh_Json.h \
    include/FD3D/Serialization/Json/Component_Json.h \
    include/FD3D/Serialization/Json/SceneNode_Json.h \
    include/FD3D/Serialization/Json/SceneNode_Json_fwd.h \
    include/FD3D/Serialization/Json/FD3D_Json_fwd.h \
    include/FD3D/Serialization/Json/FD3D_Json_utils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
