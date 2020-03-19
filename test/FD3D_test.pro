#-------------------------------------------------
#
# Project created by FDProjectUtils on 11/24/2019, 16:41:33
#
#-------------------------------------------------

TARGET = FD3D_test
TEMPLATE = app
CONFIG += console c++17 
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../../build/bin
MAKEFILE = ../../build/makefiles/$${TARGET}
OBJECTS_DIR = ../../build/.obj/$${TARGET}

LIBS += \
    -L../../build/lib \
    -L../../thirdparty/googletest/build/lib \
    -L../../thirdparty/assimp/lib \

LIBS += \
    -ldl \
    -pthread \
    -lgtest \
    -lFD3D \
    -lassimp \

INCLUDEPATH += \
    ../include \
    ../../FDCore/include \
    ../../thirdparty/googletest/googletest/include \
    ../../thirdparty/assimp/include \

SOURCES += \
    main.cpp

HEADERS += \
    Camera_test.h \
    Vertex_test.h
