#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:28:10
#
#-------------------------------------------------

TARGET = FD3DXml
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib -lFDCore -lFD3D -lFDXml \
    -L../thirdparty/assimp/bin \
    -lassimp

INCLUDEPATH += include \
    ../FDSerialize/include \
    ../FDCore/include \
    ../FDXml/include \
    ../thirdparty/ \
    ../thirdparty/glm \
    ../thirdparty/assimp/include \

SOURCES +=

HEADERS += \
    include/FD3D/Serialization/Glm_Serialize_utils.h \
    include/FD3D/Serialization/Xml/Glm_xml_fwd.h \
    include/FD3D/Serialization/Xml/Glm_xml.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
