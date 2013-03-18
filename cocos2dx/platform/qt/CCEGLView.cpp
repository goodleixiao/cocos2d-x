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
#include "CCEGLView.h"
#include "CCDirectorCaller.h"
#include "cocoa/CCSet.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"



NS_CC_BEGIN

CCEGLView* CCEGLView::s_sharedView = NULL;

static void mouseMove(QMouseEvent *event)
{
    CCEGLView::sharedOpenGLView()->mouseMove(event);
}

static void mousePress(QMouseEvent *event)
{
    CCEGLView::sharedOpenGLView()->mousePress(event);
}

static void mouseRelease(QMouseEvent *event)
{
    CCEGLView::sharedOpenGLView()->mouseRelease(event);
}

CCEGLView* CCEGLView::sharedOpenGLView(void)
{
    if (!s_sharedView)
    {
        CCEGLView* pCCEGLView = new CCEGLView();
        do{
             CC_BREAK_IF(! pCCEGLView|| ! pCCEGLView->Create(480, 320));

             CC_ASSERT(s_sharedView);
        }while(0);
    }
    return s_sharedView;
}

CCEGLView::CCEGLView(void)
    : m_bCaptured(false)
    , m_bOrientationReverted(false)
    , m_bOrientationInitVertical(false)
    , m_pDelegate(NULL)
    , bIsInit(false)
    , m_eInitOrientation(0)
    , m_fScreenScaleFactor(1.0f)
    , m_window(NULL)
    , m_bIsSubWindow(false)
{
        m_pTouch = new CCTouch;
        m_pSet = new CCSet;
//        m_sSizeInPoint.width = m_sSizeInPoint.height = 0;
 }

CCEGLView::~CCEGLView(void)
{
    CCLOG("cocos2d: deallocing CCEGLView %0x", this);
    s_sharedView = NULL;
}

bool CCEGLView::Create(int iWidth, int iHeight)
{
    m_window = new GLWidget(iWidth,iHeight, CCDirector::sharedDirector());

    m_window->setMouseMoveFunc(&cocos2d::mouseMove);
    m_window->setMousePressFunc(&cocos2d::mousePress);
    m_window->setMouseReleaseFunc(&cocos2d::mouseRelease);

    m_window->setWindowFlags(m_window->windowFlags()& ~Qt::WindowMaximizeButtonHint);
    m_window->setFixedSize(iWidth, iHeight);
    m_window->show();

    m_bIsSubWindow = true;

    bIsInit = true;
    s_sharedView = this;

    setFrameSize(iWidth, iHeight);
//    m_sSizeInPoint.width = iWidth;
//    m_sSizeInPoint.height = iHeight;
    m_bOrientationInitVertical = false;

    return true;
}

bool CCEGLView::SetWindow(GLWidget* window)
{
    if (NULL == window)
        return false;

    CC_SAFE_DELETE(m_window);
    m_window = window;

    bIsInit = true;
    s_sharedView = this;

    setDesignResolutionSize(m_window->width(), m_window->height(), kResolutionNoBorder);
//    m_sSizeInPoint.width = m_window->width();
//    m_sSizeInPoint.height = m_window->height();

    return true;
}

//CCSize CCEGLView::getSize()
//{
//    return CCSize((float)(m_sSizeInPoint.width), (float)(m_sSizeInPoint.height));
//}

bool CCEGLView::isOpenGLReady(void)
{
    return bIsInit;
}


void CCEGLView::end(void)
{
    CCDirectorCaller::sharedDirectorCaller()->end();

    CCLOG("CCEGLView end !!!!!");
    // destroy EAGLView
//    [[EAGLView sharedEGLView] removeFromSuperview];
     s_sharedView  =  NULL;

    delete this;
}

void CCEGLView::release()
{
    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_pDelegate);

    s_sharedView  =  NULL;

    // delete the opengl window only when it is created by CCEGLView::Create()
    if (! m_bIsSubWindow)
        CC_SAFE_DELETE(m_window);

    delete this;
}

void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate) {
    //TODO touch event
    m_pDelegate = pDelegate;

}

void CCEGLView::swapBuffers()
{
    if (bIsInit) {
        /* Swap buffers */
        m_window->swapBuffers();
    }
}

int CCEGLView::setDeviceOrientation(int eOritation) {
    do
    {
        bool bVertical = false;

        CC_BREAK_IF(m_bOrientationReverted && bVertical != m_bOrientationInitVertical);
        CC_BREAK_IF(! m_bOrientationReverted && bVertical == m_bOrientationInitVertical);

        m_bOrientationReverted = (bVertical == m_bOrientationInitVertical) ? false : true;

        // swap width and height
        QSize size = m_window->size();
        m_window->resize(size.height(), size.width());
    } while (0);

    return m_eInitOrientation;
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
//    if (bOpen)
//    {
//        [[EAGLView sharedEGLView] becomeFirstResponder];
//    }
//    else
//    {
//        [[EAGLView sharedEGLView] resignFirstResponder];
//    }
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    //	TODO
        if (bIsInit) {
            float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
            glViewport((GLint)(x * factor) + m_rcViewPort.origin.x,
                    (GLint)(y * factor) + m_rcViewPort.origin.y,
                    (GLint)(w * factor),
                    (GLint)(h * factor));
        }
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    //TODO
    if (bIsInit) {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glScissor((GLint)(x * factor) + m_rcViewPort.origin.x,
                (GLint)(y * factor) + m_rcViewPort.origin.y,
                (GLint)(w * factor),
                (GLint)(h * factor));
    }
}

void CCEGLView::setMultiTouchMask(bool mask)
{
	//EAGLView *glView = [EAGLView sharedEGLView];
	//glView.multipleTouchEnabled = mask ? YES : NO;
}

bool CCEGLView::canSetContentScaleFactor() {
    return false;
}

bool CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
    CCLog("could not set contentScaleFactor after initialized");
       return false;
}

void CCEGLView::mouseMove(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (! m_bCaptured)
        return;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);
    m_pDelegate->touchesMoved(m_pSet, NULL);
}

void CCEGLView::mousePress(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = true;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);
    m_pSet->addObject(m_pTouch);
    m_pDelegate->touchesBegan(m_pSet, NULL);
}

void CCEGLView::mouseRelease(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = false;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);
    m_pDelegate->touchesEnded(m_pSet, NULL);
    m_pSet->removeObject(m_pTouch);
}


NS_CC_END // end of namespace cocos2d;
