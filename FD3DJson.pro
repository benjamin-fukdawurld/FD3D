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

LIBS += -L../build/lib -lFDCore -lFD3D -lFDSerialize -lFDJson -lFDCoreJson \
    -L../thirdparty/assimp/bin \
    -lassimp

INCLUDEPATH += include \
    ../FDSerialize/include \
    ../FDCore/include \
    ../FDJson/include \
    ../thirdparty/rapidjson/include \
    ../thirdparty/glm \
    ../thirdparty/assimp/include \

SOURCES +=

HEADERS += \
    include/FD3D/Serialization/Glm_Serialize_utils.h \
    include/FD3D/Serialization/Json/FD3DJson_fwd.h \
    include/FD3D/Serialization/Json/FD3DJson.h \
    include/FD3D/Serialization/Json/Camera_json.h \
    include/FD3D/Serialization/Json/Camera_json_fwd.h \
    include/FD3D/Serialization/Json/Component_json.h \
    include/FD3D/Serialization/Json/Component_json_fwd.h \
    include/FD3D/Serialization/Json/Glm_json_fwd.h \
    include/FD3D/Serialization/Json/Glm_json.h \
    include/FD3D/Serialization/Json/Light_json.h \
    include/FD3D/Serialization/Json/Light_json_fwd.h \
    include/FD3D/Serialization/Json/Material_json.h \
    include/FD3D/Serialization/Json/Material_json_fwd.h \
    include/FD3D/Serialization/Json/Mesh_json.h \
    include/FD3D/Serialization/Json/Mesh_json_fwd.h \
    include/FD3D/Serialization/Json/Scene_json_fwd.h \
    include/FD3D/Serialization/Json/Scene_json.h \
    include/FD3D/Serialization/Json/SceneNode_json.h \
    include/FD3D/Serialization/Json/SceneNode_json_fwd.h \
    include/FD3D/Serialization/Json/Projection_json.h \
    include/FD3D/Serialization/Json/Projection_json_fwd.h \
    include/FD3D/Serialization/Json/Transform_json.h \
    include/FD3D/Serialization/Json/Transform_json_fwd.h \
    include/FD3D/Serialization/Json/VertexProxy_json.h \
    include/FD3D/Serialization/Json/VertexProxy_json_fwd.h \
    include/FD3D/Serialization/Json/Element_json_fwd.h \
    include/FD3D/Serialization/Json/Element_json.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
