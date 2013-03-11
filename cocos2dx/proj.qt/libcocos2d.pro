#-------------------------------------------------
#
# Project created by QtCreator 2011-12-31T10:49:00
#
#-------------------------------------------------

QT       += core gui opengl xml

TEMPLATE = lib
CONFIG += staticlib qt

include(actions.pri)
include(base_nodes.pri)
include(cocoa.pri)
include(effects.pri)
include(keypad_dispatcher.pri)
include(label_nodes.pri)
include(layers_scenes_transitions_nodes.pri)
include(menu_nodes.pri)
include(misc_nodes.pri)
include(particle_nodes.pri)
include(platform.pri)
include(script_support.pri)
include(sprite_nodes.pri)
include(support.pri)
include(text_input_node.pri)
include(textures.pri)
include(tileMap_parallax_nodes.pri)
include(touch_dispatcher.pri)
include(kazmath.pri)
include(shaders.pri)

win32 {
    TARGET = libcocos2d

    # You may need to change this include directory
    DEFINES += WIN32
    DEFINES += _WINDOWS
    INCLUDEPATH += \
            ../platform/third_party/win32/iconv \
            ../platform/third_party/win32/zlib \
            ../platform/third_party/win32/libjpeg \
            ../platform/third_party/win32/libpng \
            ../platform/third_party/win32/pthread \
            ../platform/third_party/win32/libxml2

    LIBS += -lglew32
    LIBS += -lopengl32
    LIBS += -L../platform/third_party/win32/libraries -llibxml2
    LIBS += -L../platform/third_party/win32/libraries -llibpng
    LIBS += -L../platform/third_party/win32/libraries -llibzlib
    LIBS += -L../platform/third_party/win32/libraries -llibjpeg
    LIBS += -L../platform/third_party/win32/libraries -llibiconv
    LIBS += -L../platform/third_party/win32/libraries -lpthreadVCE2
}

unix {
    TARGET = cocos2d

    INCLUDEPATH += /usr/local/include \
            /usr/include/libxml2 \
            ../cocos2dx

    LIBS += -L/usr/local/lib/ -lpng
    LIBS += -L/usr/local/lib/ -ljpeg
    LIBS += -L/usr/local/lib/ -lxml2
#    LIBS += -L/usr/local/lib/ -lGLEW
    LIBS += -L/usr/local/lib/ -lz
    LIBS += -L/usr/local/lib/ -lcurl
}

#DEFINES += _USRDLL
DEFINES += __QT__
DEFINES += TARGET_MAC_QT
DEFINES += USE_FILE32API
DEFINES += COCOS2D_DEBUG=1
DEFINES += COCOS2D_LIBRARY

#INCLUDEPATH += ../platform \
#        ../platform/qt \
#        ../kazmath/include \
#        ../include \
#        ..

INCLUDEPATH += \
    $$PWD/../include \
    $$PWD/../platform/qt \
    $$PWD/../platform \
    $$PWD/../support \
    $$PWD/../cocoa \
    $$PWD/../kazmath/include \
    $$PWD/../actions \
    $$PWD/../base_nodes \
    $$PWD/../effects \
    $$PWD/../label_nodes \
    $$PWD/../sprite_nodes \
    $$PWD/../script_support \
    $$PWD/../shaders \
    $$PWD/../textures \
    $$PWD/../touch_dispatcher \
    $$PWD/../menu_nodes \
    $$PWD/../misc_nodes \
    $$PWD/../keypad_dispatcher \
    $$PWD/../layers_scenes_transitions_nodes \
    $$PWD/../particle_nodes \
    $$PWD/../tileMap_parallax_nodes \
    $$PWD/../text_input_node \
    $$PWD/../

CONFIG(debug, debug|release) {
    OBJECTS_DIR = debug/
    DESTDIR = ../Debug.qt
}

CONFIG(release, debug|release) {
    OBJECTS_DIR = release/
    DESTDIR = ../Release.qt
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

HEADERS += \
    ../CCConfiguration.h \

SOURCES += \
    ../cocos2d.cpp \
    ../CCScheduler.cpp \
    ../CCDrawingPrimitives.cpp \
    ../CCDirector.cpp \
    ../CCConfiguration.cpp \
    ../CCCamera.cpp
