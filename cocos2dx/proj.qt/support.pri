include(data_support.pri)
include(image_support.pri)
include(zip_support.pri)

HEADERS += \
    ../support/TransformUtils.h \
    ../support/CCVertex.h \
    ../support/ccUtils.h \
    ../support/CCUserDefault.h \
    ../support/CCProfiling.h \
    ../support/CCPointExtension.h \
    ../support/CCNotificationCenter.h \
    ../support/base64.h

SOURCES += \
    ../support/TransformUtils.cpp \
    ../support/CCVertex.cpp \
    ../support/ccUtils.cpp \
    ../support/CCUserDefault.cpp \
    ../support/CCProfiling.cpp \
    ../support/CCPointExtension.cpp \
    ../support/CCNotificationCenter.cpp \
    ../support/base64.cpp
