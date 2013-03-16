#ifndef __CCEGLVIEWPROTOCOL_H__
#define __CCEGLVIEWPROTOCOL_H__

#include "ccTypes.h"

enum ResolutionPolicy
{
    // The entire application is visible in the specified area without trying to preserve the original aspect ratio.
    // Distortion can occur, and the application may appear stretched or compressed.
    // 应用的可见区域，没有指定原始宽高比率；可能会发生扭曲，应用程序会出现倾斜或压缩
    kResolutionExactFit,
    // The entire application fills the specified area, without distortion but possibly with some cropping,
    // while maintaining the original aspect ratio of the application.
    // 整个应用程序填满指定区域，不失真，但有可能进行一些裁切，同时保持应用程序的原始高宽比。
    kResolutionNoBorder,
    // The entire application is visible in the specified area without distortion while maintaining the original
    // aspect ratio of the application. Borders can appear on two sides of the application.
    // 整个应用程序在指定的区域不失真，同时保持原有的可见,宽高比的应用程序。双方的应用程序可能会显示边框。
    kResolutionShowAll,

    kResolutionUnKnown,
};

NS_CC_BEGIN

#define CC_MAX_TOUCHES  5

class EGLTouchDelegate;
class CCSet;

/**
 * @addtogroup platform     平台
 * @{
 */

class CC_DLL CCEGLViewProtocol
{
public:
    CCEGLViewProtocol();
    virtual ~CCEGLViewProtocol();

    /** Force destroying EGL view, subclass must implement this method. */
    // 强制消耗gl视图，子类必须实现此方法
    virtual void    end() = 0;

    /** Get whether opengl render system is ready, subclass must implement this method. */
    // opengl渲染系统准备好，子类需要实现
    virtual bool    isOpenGLReady() = 0;

    /** Exchanges the front and back buffers, subclass must implement this method. */
    // 交换前后缓存，子类需要实现
    virtual void    swapBuffers() = 0;

    /** Open or close IME keyboard , subclass must implement this method. */
    // 打开或关闭键盘，子类需要实现
    virtual void    setIMEKeyboardState(bool bOpen) = 0;

    /**
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     */
    // 获取gl视图大小
    virtual const CCSize& getFrameSize() const;

    /**
     * Set the frame size of EGL view.
     */
    // 设置帧大小
    virtual void setFrameSize(float width, float height);

    /**
     * Get the visible area size of opengl viewport.
     */
    // 获取视口可见区域
    virtual CCSize getVisibleSize() const;

    /**
     * Get the visible origin point of opengl viewport.
     */
    // 获取视口原点
    virtual CCPoint getVisibleOrigin() const;

    /**
     * Set the design resolution size.
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy desired, you may choose:
     *                         [1] kResolutionExactFit Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.
     *                         [2] kResolutionNoBorder Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.
     *                         [3] kResolutionShowAll  Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.
     */
    // 设置设计大小
    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

    /** Get design resolution size.
     *  Default resolution size is the same as 'getFrameSize'.
     */
    // 获取分辨率大小
    virtual const CCSize&  getDesignResolutionSize() const;

    /** Set touch delegate */
    // 设置触摸委托
    virtual void setTouchDelegate(EGLTouchDelegate * pDelegate);

    /**
     * Set opengl view port rectangle with points.
     */
    // 设置视口，以点
    virtual void setViewPortInPoints(float x , float y , float w , float h);

    /**
     * Set Scissor rectangle with points.
     */
    // 设置点的剪式矩形
    virtual void setScissorInPoints(float x , float y , float w , float h);

    virtual void setViewName(const char* pszViewName);

    const char* getViewName();

    /** Touch events are handled by default; if you want to customize your handlers, please override these functions: */
    // 触摸事件处理方法
    virtual void handleTouchesBegin(int num, int ids[], float xs[], float ys[]);
    virtual void handleTouchesMove(int num, int ids[], float xs[], float ys[]);
    virtual void handleTouchesEnd(int num, int ids[], float xs[], float ys[]);
    virtual void handleTouchesCancel(int num, int ids[], float xs[], float ys[]);

    /**
     * Get the opengl view port rectangle.
     */
    // 获取opengl视口矩形
    const CCRect& getViewPortRect() const;

    /**
     * Get scale factor of the horizontal direction.
     */
    // 获取x轴缩放
    float getScaleX() const;

    /**
     * Get scale factor of the vertical direction.
     */
    // 获取y轴缩放
    float getScaleY() const;
private:
    void getSetOfTouchesEndOrCancel(CCSet& set, int num, int ids[], float xs[], float ys[]);

protected:
    EGLTouchDelegate* m_pDelegate;

    // real screen size
    // 真实屏幕大小
    CCSize m_obScreenSize;
    // resolution size, it is the size appropriate for the app resources.
    // 分辨率大小
    CCSize m_obDesignResolutionSize;
    // the view port size
    // 视口大小
    CCRect m_obViewPortRect;
    // the view name
    // 视图名称
    char   m_szViewName[50];

    float  m_fScaleX;
    float  m_fScaleY;
    ResolutionPolicy m_eResolutionPolicy;
};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCEGLVIEWPROTOCOL_H__ */
