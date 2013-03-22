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

#ifndef __CC_EGLVIEW_MAC_H__
#define __CC_EGLVIEW_MAC_H__

#include "platform/CCCommon.h"
#include "platform/CCEGLViewProtocol.h"
#include "CCGLWidget.h"
#include <QMouseEvent>

NS_CC_BEGIN

class CCSet;
class CCTouch;
class CCSize;


class CC_DLL CCEGLView : public CCEGLViewProtocol
{
public:
    static CCEGLView* sharedOpenGLView(void);
    CCEGLView(void);
    virtual ~CCEGLView(void);
    
    virtual bool isOpenGLReady(void);
    virtual void end();
    virtual void swapBuffers(void);
    
    virtual void setIMEKeyboardState(bool bOpen);

public:
    // Create opengl window
    bool Create(int iWidth, int iHeight, QWidget *parent = 0);

    // Set openGL window
    bool SetWindow(GLWidget *window);


    void release();

    int setDeviceOrientation(int eOritation);

    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseRelease(QMouseEvent *event);

    // main loop
    void startMainLoop();

    void setAnimationInterval(double interval);

private:
    static CCEGLView* s_sharedView;

    bool m_bCaptured;
//    bool m_bOrientationReverted;
//    bool m_bOrientationInitVertical;
    CCSet * m_pSet;
    CCTouch * m_pTouch;

    //store current mouse point for moving, valid if and only if the mouse pressed
    CCPoint m_mousePoint;

//    float m_fScreenScaleFactor;

    GLWidget* m_window;
};

NS_CC_END   // end of namespace   cocos2d

#endif	// end of __CC_EGLVIEW_MAC_H__
