#-------------------------------------------------
#
# Project created by QtCreator 2013-03-08T17:39:44
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld_Test
TEMPLATE = app

include(AccelerometerTest.pri)
include(ActionManagerTest.pri)
include(ActionsEaseTest.pri)
include(ActionsProgressTest.pri)
include(ActionsTest.pri)
include(Box2DTest.pri)
include(Box2DTestBed.pri)
include(BugsTest.pri)
include(ChipmunkAccelTouchTest.pri)
include(ClickAndMoveTest.pri)
include(CocosDenshionTest.pri)
include(CurlTest.pri)
include(CurrentLanguageTest.pri)
include(DrawPrimitivesTest.pri)
include(EffectsAdvancedTest.pri)
include(EffectsTest.pri)
include(ExtensionsTest.pri)
include(FontTest.pri)
include(IntervalTest.pri)
include(KeypadTest.pri)
include(LabelTest.pri)
include(LayerTest.pri)
include(MenuTest.pri)
include(MotionStreakTest.pri)
include(MutiTouchTest.pri)
include(NodeTest.pri)
include(ParallaxTest.pri)
include(ParticleTest.pri)
include(PerformanceTest.pri)
include(RenderTextureTest.pri)
include(RotateWorldTest.pri)
include(SceneTest.pri)
include(SchedulerTest.pri)
include(ShaderTest.pri)
include(SpriteTest.pri)
include(TextInputTest.pri)
include(Texture2dTest.pri)
include(TextureCacheTest.pri)
include(TileMapTest.pri)
include(TouchesTest.pri)
include(TransitionsTest.pri)
include(UserDefaultTest.pri)
include(ZwoptexTest.pri)


SOURCES += main.cpp \
    ../Classes/AppDelegate.cpp \
    ../Classes/VisibleRect.cpp \
    ../Classes/testBasic.cpp \
    ../Classes/controller.cpp

HEADERS  +=     main.h \
    ../Classes/AppDelegate.h \
    ../Classes/VisibleRect.h \
    ../Classes/tests.h \
    ../Classes/testResource.h \
    ../Classes/testBasic.h \
    ../Classes/controller.h

COCOS2DPATH = $$PWD/../../..

DEFINES += COCOS2D_LIBRARY TARGET_MAC_QT  USE_FILE32API COCOS2D_DEBUG=1

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../
}

CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../
}

unix {
     LIBS += -L$$COCOS2DPATH/Debug.qt/ -lcocos2d
#    LIBS += -L/usr/local/lib/ -lpng
#    LIBS += -L/usr/local/lib/ -ljpeg
    LIBS += -L/usr/local/lib/ -lxml2
#    LIBS += -L/usr/local/lib/ -lGLEW
    LIBS += -L/usr/local/lib/ -lz
#    LIBS += -L/usr/local/lib/ -lcurl
    PRE_TARGETDEPS += $$COCOS2DPATH/Debug.qt/libcocos2d.a
}

INCLUDEPATH += \
    $$COCOS2DPATH/cocos2dx/include \
    $$COCOS2DPATH/cocos2dx/platform/qt\
    $$COCOS2DPATH/cocos2dx/platform \
    $$COCOS2DPATH/cocos2dx/support \
    $$COCOS2DPATH/cocos2dx/cocoa \
    $$COCOS2DPATH/cocos2dx/kazmath/include \
    $$COCOS2DPATH/cocos2dx/actions \
    $$COCOS2DPATH/cocos2dx/base_nodes \
    $$COCOS2DPATH/cocos2dx/effects \
    $$COCOS2DPATH/cocos2dx/label_nodes \
    $$COCOS2DPATH/cocos2dx/sprite_nodes \
    $$COCOS2DPATH/cocos2dx/script_support \
    $$COCOS2DPATH/cocos2dx/shaders \
    $$COCOS2DPATH/cocos2dx/textures \
    $$COCOS2DPATH/cocos2dx/touch_dispatcher \
    $$COCOS2DPATH/cocos2dx/menu_nodes \
    $$COCOS2DPATH/cocos2dx/misc_nodes \
    $$COCOS2DPATH/cocos2dx/keypad_dispatcher \
    $$COCOS2DPATH/cocos2dx/layers_scenes_transitions_nodes \
    $$COCOS2DPATH/cocos2dx/particle_nodes \
    $$COCOS2DPATH/cocos2dx/tileMap_parallax_nodes \
    $$COCOS2DPATH/cocos2dx/text_input_node \
    $$COCOS2DPATH/cocos2dx/ \
    $$COCOS2DPATH/external/ \
    $$COCOS2DPATH/external/chipmunk/include/chipmunk \
    $$COCOS2DPATH/CocosDenshion/include \
    $$COCOS2DPATH/extensions \
    $$PWD/../Classes

RESOURCES += \
    ../Resources/resources.qrc


