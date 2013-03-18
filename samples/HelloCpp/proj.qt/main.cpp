/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#include "AppDelegate.h"

#include "CCFileUtils.h"

int main(int argc, char **argv)
{
//#ifdef Q_OS_SYMBIAN
//        CCFileUtils::sharedFileUtils()->setResourcePath("/private/E8AA3F79/resources");
//#else
//        CCFileUtils::sharedFileUtils()->setResourcePath("/opt/helloworld/Resources");
//#endif

    AppDelegate app;
    // create the application instance
    Q_INIT_RESOURCE(resources);
    CCApplication::sharedApplication()->setResourceRootPath(":/");
//    app.setOrientation(CCApplication::kOrientationLandscapeLeft);
    return CCApplication::sharedApplication()->run();

//    AppDelegate app(argc, argv);

//    return cocos2d::CCApplication::sharedApplication().run();
}
