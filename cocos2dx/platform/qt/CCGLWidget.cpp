#include "CCGLWidget.h"
#include "CCApplication.h"
#include <QtCore/QTimer>

GLWidget::GLWidget(int width, int height, CCDirector* director, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
  , mouseMoveFunc(NULL)
  , mousePressFunc(NULL)
  , mouseReleaseFunc(NULL)
  , m_timer(NULL)
  , m_director(director)
{
    resize(width, height);

}

GLWidget::~GLWidget()
{
    stop();

    m_director = NULL;
}

void GLWidget::stop()
{
    if (m_timer != NULL)
         m_timer->stop();

    CC_SAFE_DELETE(m_timer);
}

bool GLWidget::IsSubWindow()
{
    if(this->parent() == NULL)
        return false;
    else
        return true;
}

void GLWidget::startMainLoop(double interval)
{
    CC_SAFE_DELETE(m_timer);

    int iTimer = interval * 1000;

    if (iTimer <= 10)
        iTimer = 250;

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(iTimer);
}

void GLWidget::setAnimationInterval(double interval)
{
    if (m_timer != NULL)
    {
        int iTimer = interval * 1000;
        CCLOG("GLWidget setAnimationInterval %d", iTimer);
        m_timer->start(iTimer);
    }

}

void GLWidget::setMouseMoveFunc(PTRFUN func)
{
    mouseMoveFunc = func;
}

void GLWidget::setMousePressFunc(PTRFUN func)
{
    mousePressFunc = func;
}

void GLWidget::setMouseReleaseFunc(PTRFUN func)
{
    mouseReleaseFunc = func;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseMoveFunc)
        mouseMoveFunc(event);

    QGLWidget::mouseMoveEvent(event);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (mousePressFunc)
        mousePressFunc(event);

    QGLWidget::mousePressEvent(event);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (mouseReleaseFunc)
        mouseReleaseFunc(event);

    QGLWidget::mouseReleaseEvent(event);
}

void GLWidget::closeEvent(QCloseEvent *event)
{
    CCLOG("GLWidget closeEvent");
    stop();
     QGLWidget::closeEvent(event);
}

void GLWidget::showEvent ( QShowEvent *event )
{
    CCLOG("GLWidget showEvent");
    CCApplication::sharedApplication()->applicationWillEnterForeground();
    QGLWidget::showEvent(event);
}

void GLWidget::hideEvent ( QHideEvent * event)
{
    CCLOG("GLWidget hideEvent");
    CCApplication::sharedApplication()->applicationDidEnterBackground();
   QGLWidget::hideEvent(event);
}

void GLWidget::update()
{
//	glewInit();
    makeCurrent();

    if (m_director)
        m_director->mainLoop();

    doneCurrent();
}


