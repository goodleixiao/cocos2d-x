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

#import "CCDirectorCaller.h"
#import "CCDirector.h"
#include "cocoa/CCAutoreleasePool.h"


CCDirectorCaller * CCDirectorCaller::sm_pSharedDirectorCaller = 0;

CCDirectorCaller::CCDirectorCaller():
    m_timer(NULL)
{
    CCAssert(!sm_pSharedDirectorCaller, "sm_pSharedDirectorCaller already exist");
    sm_pSharedDirectorCaller = this;
}

CCDirectorCaller::~CCDirectorCaller()
{
    CCAssert(this == sm_pSharedDirectorCaller, "sm_pSharedDirectorCaller != this");
    sm_pSharedDirectorCaller = NULL;

    CC_SAFE_DELETE(m_timer);
}

CCDirectorCaller* CCDirectorCaller::sharedDirectorCaller()
{
    if (sm_pSharedDirectorCaller == NULL)
    {
        new CCDirectorCaller();
    }
    CCAssert(sm_pSharedDirectorCaller, "sm_pSharedDirectorCaller not set");
    return  sm_pSharedDirectorCaller;
}

void CCDirectorCaller::startMainLoop()
{
    CCAssert(!m_timer, "m_timer already exist ");

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
//    m_timer->start(m_nInterval);
}

void CCDirectorCaller::end()
{
    if (m_timer)
    {
        m_timer->stop();
    }
}

void CCDirectorCaller::setAnimationInterval(double interval)
{
    m_nInterval = interval * 1000.0f;
    if (m_timer)
    {
        m_timer->start(m_nInterval);
    }
}

void CCDirectorCaller::timerUpdate()
{
    CCDirector::sharedDirector()->mainLoop();
}
