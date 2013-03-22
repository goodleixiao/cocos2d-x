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
    CCAssert(s_sharedView, "s_sharedView already exist");

    return s_sharedView;
}

CCEGLView::CCEGLView(void)
    :  CCEGLViewProtocol()
    , m_bCaptured(false)
//    , m_bOrientationReverted(false)
//    , m_bOrientationInitVertical(false)
    , m_window(NULL)
{
        CCAssert(! s_sharedView, "s_sharedView already exist");

        m_pTouch = new CCTouch;
        m_pSet = new CCSet;

        s_sharedView = this;
 }

CCEGLView::~CCEGLView(void)
{
    CCLOG("cocos2d: deallocing CCEGLView %0x", this);
    CCAssert(this == s_sharedView, "sm_pSharedApplication != this");
    s_sharedView = NULL;
}

bool CCEGLView::Create(int iWidth, int iHeight,QWidget *parent)
{
    m_window = new GLWidget(iWidth,iHeight, CCDirector::sharedDirector(), parent);

    m_window->setMouseMoveFunc(&cocos2d::mouseMove);
    m_window->setMousePressFunc(&cocos2d::mousePress);
    m_window->setMouseReleaseFunc(&cocos2d::mouseRelease);

    m_window->setWindowFlags(m_window->windowFlags()& ~Qt::WindowMaximizeButtonHint);
    m_window->setFixedSize(iWidth, iHeight);
    if (parent == NULL)
        m_window->show();

    s_sharedView = this;

    setFrameSize(iWidth, iHeight);
//    m_bOrientationInitVertical = false;

    return true;
}

bool CCEGLView::SetWindow(GLWidget* window)
{
    if (NULL == window)
        return false;

    CC_SAFE_DELETE(m_window);
    m_window = window;

    s_sharedView = this;

    setDesignResolutionSize(m_window->width(), m_window->height(), kResolutionNoBorder);

    return true;
}


bool CCEGLView::isOpenGLReady(void)
{
    return m_window != NULL;
}

void CCEGLView::startMainLoop()
{
    if (m_window != NULL)
    {
        m_window->startMainLoop();
    }
}

void CCEGLView::setAnimationInterval(double interval)
{
    if (m_window != NULL)
        m_window->setAnimationInterval(interval);
}

void CCEGLView::end(void)
{

    CCLOG("CCEGLView end !!!!!");
    // destroy EAGLView
    m_pDelegate = NULL;

    if (!m_window->IsSubWindow())
    {
        m_window->close();
    }
    else
    {
        m_window->stop();
    }
}

void CCEGLView::release()
{
    // delete the opengl window only when it is created by CCEGLView::Create()

    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_pDelegate);

    s_sharedView  =  NULL;

    if (!m_window->IsSubWindow())
        CC_SAFE_DELETE(m_window);

    delete this;
}

void CCEGLView::swapBuffers()
{
    if (m_window != NULL) {
        /* Swap buffers */
        m_window->swapBuffers();
    }
}

int CCEGLView::setDeviceOrientation(int eOritation) {
//    do
//    {
//        bool bVertical = false;

//        CC_BREAK_IF(m_bOrientationReverted && bVertical != m_bOrientationInitVertical);
//        CC_BREAK_IF(! m_bOrientationReverted && bVertical == m_bOrientationInitVertical);

//        m_bOrientationReverted = (bVertical == m_bOrientationInitVertical) ? false : true;

//        // swap width and height
//        QSize size = m_window->size();
//        m_window->resize(size.height(), size.width());
//    } while (0);

    return 0;
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{

}

//void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
//{
//    //	TODO
//        if (bIsInit) {
//            float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
//            glViewport((GLint)(x * factor) + m_rcViewPort.origin.x,
//                    (GLint)(y * factor) + m_rcViewPort.origin.y,
//                    (GLint)(w * factor),
//                    (GLint)(h * factor));
//        }
//}

//void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
//{
//    //TODO
//    if (bIsInit) {
//        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
//        glScissor((GLint)(x * factor) + m_rcViewPort.origin.x,
//                (GLint)(y * factor) + m_rcViewPort.origin.y,
//                (GLint)(w * factor),
//                (GLint)(h * factor));
//    }
//}

void CCEGLView::mouseMove(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (! m_bCaptured)
        return;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScaleX,
        (float)(event->y()) / m_fScaleY);
    m_pDelegate->touchesMoved(m_pSet, NULL);
}

void CCEGLView::mousePress(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = true;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScaleX,
        (float)(event->y()) / m_fScaleY);
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

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScaleX,
        (float)(event->y()) / m_fScaleY);
    m_pDelegate->touchesEnded(m_pSet, NULL);
    m_pSet->removeObject(m_pTouch);
}


NS_CC_END // end of namespace cocos2d;
