#-------------------------------------------------
#
# Project created by QtCreator 2013-03-08T17:39:44
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld_Test
TEMPLATE = app


SOURCES += main.cpp \
    ../Classes/HelloWorldScene.cpp \
    ../Classes/AppDelegate.cpp

HEADERS  +=     main.h \
    ../Classes/HelloWorldScene.h \
    ../Classes/AppMacros.h \
    ../Classes/AppDelegate.h

#RESOURCES += ./Resources/

CONFIG(debug, debug|release) {
    DESTDIR = ../../../Debug.qt
}

CONFIG(release, debug|release) {
    DESTDIR = ../../../Release.qt
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    LIBS += -L/usr/local/lib/ -lpng
    LIBS += -L/usr/local/lib/ -ljpeg
    LIBS += -L/usr/local/lib/ -lxml2
#    LIBS += -L/usr/local/lib/ -lGLEW
    LIBS += -L/usr/local/lib/ -lz
    LIBS += -L/usr/local/lib/ -lcurl
    INSTALLS += target
}

DEFINES += COCOS2D_LIBRARY TARGET_MAC_QT  USE_FILE32API COCOS2D_DEBUG=1

INCLUDEPATH += \
    $$PWD/../../../cocos2dx/include \
    $$PWD/../../../cocos2dx/platform/qt\
    $$PWD/../../../cocos2dx/platform \
    $$PWD/../../../cocos2dx/support \
    $$PWD/../../../cocos2dx/cocoa \
    $$PWD/../../../cocos2dx/kazmath/include \
    $$PWD/../../../cocos2dx/actions \
    $$PWD/../../../cocos2dx/base_nodes \
    $$PWD/../../../cocos2dx/effects \
    $$PWD/../../../cocos2dx/label_nodes \
    $$PWD/../../../cocos2dx/sprite_nodes \
    $$PWD/../../../cocos2dx/script_support \
    $$PWD/../../../cocos2dx/shaders \
    $$PWD/../../../cocos2dx/textures \
    $$PWD/../../../cocos2dx/touch_dispatcher \
    $$PWD/../../../cocos2dx/menu_nodes \
    $$PWD/../../../cocos2dx/misc_nodes \
    $$PWD/../../../cocos2dx/keypad_dispatcher \
    $$PWD/../../../cocos2dx/layers_scenes_transitions_nodes \
    $$PWD/../../../cocos2dx/particle_nodes \
    $$PWD/../../../cocos2dx/tileMap_parallax_nodes \
    $$PWD/../../../cocos2dx/text_input_node \
    $$PWD/../../../cocos2dx/ \
    $$PWD/../Classes/


unix: LIBS += -L$$PWD/../../../Debug.qt/ -lcocos2d

INCLUDEPATH += $$PWD/../../../Debug.qt
DEPENDPATH += $$PWD/../../../Debug.qt

unix: PRE_TARGETDEPS += $$PWD/../../../Debug.qt/libcocos2d.a

RESOURCES += \
    resources.qrc

OTHER_FILES +=     fps_images.png \
    fps_images-ipadhd.png \
    fps_images-hd.png

FORMS += \
    dialog.ui

