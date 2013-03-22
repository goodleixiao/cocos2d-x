/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "CCApplication.h"
#include <algorithm>

#include "cocoa/CCGeometry.h"
#include "CCDirector.h"
#include "CCEGLView.h"

NS_CC_BEGIN

CCApplication* CCApplication::sm_pSharedApplication = 0;

int tmpArgc = 1;
char* tmpArgv[] = {"", NULL};

CCApplication::CCApplication():
    QApplication(tmpArgc,tmpArgv)
{
    CCAssert(! sm_pSharedApplication, "sm_pSharedApplication already exist");
    sm_pSharedApplication = this;

}

CCApplication::CCApplication(int& argc, char** argv):
    QApplication(argc, argv)
{
    CCAssert(! sm_pSharedApplication, "sm_pSharedApplication already exist");
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CCAssert(this == sm_pSharedApplication, "sm_pSharedApplication != this");
    sm_pSharedApplication = 0;
}

bool CCApplication::applicationInitInstance()
{
    CCLOG("Do not implement applicationInitInstance() ");
    return false;
}

int CCApplication::run()
{
    CCLOG("Do not implement kkk applicationInitInstance() ");
    // Make sure the view is initialized
    CCEGLView* view = NULL;
    if (!applicationInitInstance())
    {
        view  = new CCEGLView();
       view->Create(480, 320);
    }
    else
    {
        view = CCEGLView::sharedOpenGLView();
    }


    if (/*initInstance() &&*/ applicationDidFinishLaunching())
    {
        view->startMainLoop();
    }

    return exec();
}

void CCApplication::setAnimationInterval(double interval)
{
    CCEGLView::sharedOpenGLView()->setAnimationInterval(interval);
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetMacOS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

CCApplication* CCApplication::sharedApplication()
{
    CCAssert(sm_pSharedApplication, "sm_pSharedApplication not set");
    return sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    // get the current language and country config

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)

    QString lang = "zh";

    if (lang == "zh")
    {
        return kLanguageChinese;
    }
    else if (lang == "fr")
    {
        return kLanguageFrench;
    }
    else if (lang == "it")
    {
        return kLanguageItalian;
    }
    else if (lang == "de")
    {
        return kLanguageGerman;
    }
    else if (lang == "es")
    {
        return kLanguageSpanish;
    }
    else if (lang == "ru")
    {
        return kLanguageRussian;
    }

    return kLanguageEnglish;
    
}

void CCApplication::setResourceRootPath(const std::string& rootResDir)
{
    m_resourceRootPath = rootResDir;
    std::replace(m_resourceRootPath.begin(), m_resourceRootPath.end(), '\\', '/');
    if (m_resourceRootPath[m_resourceRootPath.length() - 1] != '/')
    {
        m_resourceRootPath += '/';
    }
    CCLOG("resource root path [ %s]",m_resourceRootPath.c_str());
}

const std::string& CCApplication::getResourceRootPath(void)
{
    return m_resourceRootPath;
}

void CCApplication::setStartupScriptFilename(const std::string& startupScriptFile)
{
    m_startupScriptFilename = startupScriptFile;
    std::replace(m_startupScriptFilename.begin(), m_startupScriptFilename.end(), '\\', '/');
}

const std::string& CCApplication::getStartupScriptFilename(void)
{
    return m_startupScriptFilename;
}

NS_CC_END
