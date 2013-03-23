#ifndef  _GL_WIDGET_H_
#define  _GL_WIDGET_H_

#include "CCDirector.h"
#include "CCCommon.h"
#undef CursorShape
#include <QtOpenGL/QGLWidget>

USING_NS_CC;

class CC_DLL GLWidget : public QGLWidget
{
    Q_OBJECT

    typedef void(*PTRFUN)(QMouseEvent *event);

public:
    GLWidget(){}
    GLWidget(int width, int height, CCDirector* director = NULL, QWidget *parent = 0);

    ~GLWidget();

    void setMouseMoveFunc(PTRFUN func);
    void setMousePressFunc(PTRFUN func);
    void setMouseReleaseFunc(PTRFUN func);

    void startMainLoop(double interval);

    void setAnimationInterval(double interval);

    virtual void stop();
    virtual bool IsSubWindow();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    virtual void showEvent ( QShowEvent *event );
    virtual void hideEvent ( QHideEvent * event);

public slots:
    void update();

private:
    PTRFUN mouseMoveFunc;
    PTRFUN mousePressFunc;
    PTRFUN mouseReleaseFunc;

    QTimer *m_timer;
    CCDirector* m_director;

};

#endif // _GL_WIDGET_H_
