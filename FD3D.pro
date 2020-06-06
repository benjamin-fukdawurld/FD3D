#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:57:00
#
#-------------------------------------------------
TARGET = FD3D
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += \
    -L../thirdparty/assimp/bin \
    -lassimp
    -lFDCore

INCLUDEPATH += \
    include \
    ../FDCore/include \
    ../thirdparty/glm \
    ../thirdparty/assimp/include \
    ../thirdparty/ \

SOURCES += \
    src/Component.cpp \
    src/IndexProxy.cpp \
    src/Light.cpp \
    src/Projection.cpp \
    src/Scene.cpp \
    src/SceneLoader.cpp \
    src/SceneNode.cpp \
    src/Transform.cpp \
    src/Camera.cpp \
    src/ModelLoader.cpp \
    src/VertexProxy.cpp \
    src/LightColor.cpp \
    src/LightAttenuation.cpp \
    src/LightCone.cpp \
    src/TransformStack.cpp \
    src/Element.cpp \
    src/SceneManager.cpp \
    src/TextureComponent.cpp \
    src/AbstractTexture.cpp \
    src/MaterialComponent.cpp \
    src/Material.cpp \
    src/Texture.cpp \
    src/AbstractMeshComponent.cpp \
    src/MeshComponent.cpp \
    src/AbstractMesh.cpp \
    src/Mesh.cpp \
    src/AbstractBehaviorComponent.cpp \
    src/BehaviorComponent.cpp \
    src/StrategyBehaviorComponent.cpp \
    src/AbstractBehavior.cpp \
    src/BaseBehavior.cpp \
    src/AbstractBehaviorGenerator.cpp \
    src/StrategyBehavior.cpp \
    src/EmbeddedTexture.cpp

HEADERS += \
    include/FD3D/SceneGraph/Component.h \
    include/FD3D/SceneGraph/SceneLoader.h \
    include/FD3D/SceneGraph/Scene.h \
    include/FD3D/SceneGraph/SceneNode.h \
    \
    include/FD3D/Light/Light.h \
    include/FD3D/Light/LightColor.h \
    include/FD3D/Light/LightAttenuation.h \
    include/FD3D/Light/LightCone.h \
    include/FD3D/Light/LightType.h \
    \
    include/FD3D/Camera/Camera.h \
    include/FD3D/Camera/Projection.h \
    include/FD3D/Camera/ProjectionType.h \
    \
    \
    include/FD3D/Utils/IndexProxy.h \
    include/FD3D/Utils/Transform.h \
    include/FD3D/Utils/VertexProxy.h \
    include/FD3D/Utils/TransformStack.h \
    \
    \
    \` \
    include/FD3D/SceneGraph/Element.h \
    include/FD3D/SceneGraph/SceneManager.h \
    include/FD3D/Material/TextureComponent.h \
    include/FD3D/Material/AbstractTexture.h \
    include/FD3D/Material/MaterialComponent.h \
    include/FD3D/Material/Material.h \
    include/FD3D/Material/Texture.h \
    include/FD3D/Mesh/AbstractMeshComponent.h \
    include/FD3D/Mesh/MeshComponent.h \
    include/FD3D/Mesh/AbstractMesh.h \
    include/FD3D/Mesh/Mesh.h \
    include/FD3D/Behavior/AbstractBehaviorComponent.h \
    include/FD3D/Behavior/BehaviorComponent.h \
    include/FD3D/Behavior/StrategyBehaviorComponent.h \
    include/FD3D/Behavior/AbstractBehavior.h \
    include/FD3D/Behavior/BaseBehavior.h \
    include/FD3D/Behavior/AbstractBehaviorGenerator.h \
    include/FD3D/Behavior/StrategyBehavior.h \
    include/FD3D/SceneGraph/SceneNodeProxy.h \
    include/FD3D/Material/EmbeddedTexture.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
