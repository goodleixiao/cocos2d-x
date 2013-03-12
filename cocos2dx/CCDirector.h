/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include "platform/CCPlatformMacros.h"
#include "cocoa/CCObject.h"
#include "ccTypes.h"
#include "cocoa/CCGeometry.h"
#include "cocoa/CCArray.h"
#include "CCGL.h"
#include "kazmath/mat4.h"
#include "label_nodes/CCLabelTTF.h"
#include "ccTypeInfo.h"


NS_CC_BEGIN

/**
 * @addtogroup base_nodes	基本节点
 * @{
 */

/** @typedef ccDirectorProjection
 Possible OpenGL projections used by director
 */
// 可能用到opengl投影

typedef enum {
    /// sets a 2D projection (orthogonal projection)
    /// 设置2D投影（正交投影）
    kCCDirectorProjection2D,
    
    /// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
    /// 设置3D投影，参数为fovy=60, znear=0.5f , zfar=1500
    kCCDirectorProjection3D,
    
    /// it calls "updateProjection" on the projection delegate.
    /// 调用更新投影
    kCCDirectorProjectionCustom,
    
    /// Default projection is 3D projection
    /// 设置默认投影为3D投影
    kCCDirectorProjectionDefault = kCCDirectorProjection3D,
} ccDirectorProjection;

/* Forward declarations. */
// 预先声明
class CCLabelAtlas;
class CCScene;
class CCEGLView;
class CCDirectorDelegate;
class CCNode;
class CCScheduler;
class CCActionManager;
class CCTouchDispatcher;
class CCKeypadDispatcher;
class CCAccelerometer;

/**
@brief Class that creates and handle the main Window and manages how
and when to execute the Scenes.
 
 The CCDirector is also responsible for:
  - initializing the OpenGL context
  - setting the OpenGL pixel format (default on is RGB565)
  - setting the OpenGL buffer depth (default one is 0-bit)
  - setting the projection (default one is 3D)
  - setting the orientation (default one is Portrait)
 
 Since the CCDirector is a singleton, the standard way to use it is by calling:
  _ CCDirector::sharedDirector()->methodName();
 
 The CCDirector also sets the default OpenGL context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
*/
/**
该类主要是创建和管理主窗口和运行场景；
主要功能有：
	1，初始化opengl上下文；
	2，设置opengl像素格式(默认为RGB565)
	3，设置Opengl位深度缓存（默认为0）
	4，设置投影（默认为3D)
	5，设置设备方向(默认为竖向)
 */
class CC_DLL CCDirector : public CCObject, public TypeInfo
{
public:
    CCDirector(void);
    virtual ~CCDirector(void);
    virtual bool init(void);
    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CCDirector).name());
		return id;
    }

    // attribute
    // 属性
    /** Get current running Scene. Director can only run one Scene at the time */
    /** 获取当前运行场景。某一时刻，导演只能执行一个场景*/
    inline CCScene* getRunningScene(void) { return m_pRunningScene; }

    /** Get the FPS value */
    /** 获取FPS值 */
    inline double getAnimationInterval(void) { return m_dAnimationInterval; }
    /** Set the FPS value. */
    /** 设置FPS值 */
    virtual void setAnimationInterval(double dValue) = 0;

    /** Whether or not to display the FPS on the bottom-left corner */
    /** 是否显示FPS标签，在左下角 */
    inline bool isDisplayStats(void) { return m_bDisplayStats; }
    /** Display the FPS on the bottom-left corner */
    /** 显示FPS标签 */
    inline void setDisplayStats(bool bDisplayStats) { m_bDisplayStats = bDisplayStats; }
    
    /** seconds per frame */
    /** 每帧时间 */
    inline float getSecondsPerFrame() { return m_fSecondsPerFrame; }

    /** Get the CCEGLView, where everything is rendered */
    /** 获取CCEGLView视图，就是所有对象呈现的地方 */
    inline CCEGLView* getOpenGLView(void) { return m_pobOpenGLView; }
    void setOpenGLView(CCEGLView *pobOpenGLView);

    inline bool isNextDeltaTimeZero(void) { return m_bNextDeltaTimeZero; }
    void setNextDeltaTimeZero(bool bNextDeltaTimeZero);

    /** Whether or not the Director is paused */
    /** 是否暂停导演 */
    inline bool isPaused(void) { return m_bPaused; }

    /** How many frames were called since the director started */
    /** 从开始导演调用了多少帧 */
    inline unsigned int getTotalFrames(void) { return m_uTotalFrames; }
    
    /** Sets an OpenGL projection
     @since v0.8.2
     */
    /** 设置opengl投影 */
    inline ccDirectorProjection getProjection(void) { return m_eProjection; }
    void setProjection(ccDirectorProjection kProjection);
    
    /** Sets the glViewport*/
    /** 设置gl视口 */
    void setViewport();

    /** How many frames were called since the director started */
    
    
    /** Whether or not the replaced scene will receive the cleanup message.
     If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     If the new scene replaces the old one, the it will receive the "cleanup" message.
     @since v0.99.0
     */
    /** 被替换的场景是否接收清除消息；一个新的场景呈现，旧的场景不会收到清理消息
     * 新的替换旧的场景，它会收到清理消息
     */
    inline bool isSendCleanupToScene(void) { return m_bSendCleanupToScene; }

    /** This object will be visited after the main scene is visited.
     This object MUST implement the "visit" selector.
     Useful to hook a notification object, like CCNotifications (http://github.com/manucorporat/CCNotifications)
     @since v0.99.5
     */
    /** 在主场景被访问后，此对象会被访问；
     * 该对象必须实现访问选择器
     * 使用通知队列，像通知可以参考上面链接(http://github.com/manucorporat/CCNotifications)
     */
    CCNode* getNotificationNode();
    void setNotificationNode(CCNode *node);
    
    /** CCDirector delegate. It shall implemente the CCDirectorDelegate protocol
     @since v0.99.5
     */
    /** 导演委托。实现其协议 */
    CCDirectorDelegate* getDelegate() const;
    void setDelegate(CCDirectorDelegate* pDelegate);

    // window size
    // 窗口大小

    /** returns the size of the OpenGL view in points.
    */
    /** 返回opengl视图大小 以点为单位*/
    CCSize getWinSize(void);

    /** returns the size of the OpenGL view in pixels.
    */
    /** 返回opengl视图大小 以像素为单位*/
    CCSize getWinSizeInPixels(void);
    
    /** returns visible size of the OpenGL view in points.
     *  the value is equal to getWinSize if don't invoke
     *  CCEGLView::setDesignResolutionSize()
     */
    /** 返回Opengl视图可见大小。 
     * 如果不调用CCEGLView::setDesignResolutionSize()方法，该值与getWinSize相等
     */
    CCSize getVisibleSize();
    
    /** returns visible origin of the OpenGL view in points.
     */
    /** 返回opengl视图的可见起源 */
    CCPoint getVisibleOrigin();

    /** converts a UIKit coordinate to an OpenGL coordinate
     Useful to convert (multi) touch coordinates to the current layout (portrait or landscape)
     */
    /** 转换UI坐标系到opengl坐标系；
     * 转换（多点）触摸坐标到当前布局（纵向或横向）
     */
    CCPoint convertToGL(const CCPoint& obPoint);

    /** converts an OpenGL coordinate to a UIKit coordinate
     Useful to convert node points to window points for calls such as glScissor
     */
    /** 转换opengl坐标系到UI坐标系
     * 用于转换节点到窗口点，如glScissor
     */
    CCPoint convertToUI(const CCPoint& obPoint);

    /// XXX: missing description  未知描述
    float getZEye(void);

    // Scene Management
    // 场景管理

    /**Enters the Director's main loop with the given Scene. 
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     */
    /** 给定场景导演进入主运行回路；
     * 运行第一个场景时调用此方法；
     * 不要在运行中调用此方法
     * 会调用推入场景，调用开始动画
     */
    void runWithScene(CCScene *pScene);

    /**Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     */
    /** 将场景推入栈中
     * 新的场景将会执行
     * 尽量减少使用大的栈来推入场景，减少内容分配
     * 仅在运行场景中调用此方法
     */
    void pushScene(CCScene *pScene);

    /**Pops out a scene from the queue.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     */
    /** 弹出场景从队列中
     * 场景会替换运行场景
     * 运行场景会被删除。如果栈中没有更多场景，将会终止
     * 仅在运行场景中调用
     */
    void popScene(void);

    /**Pops out all scenes from the queue until the root scene in the queue.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     */
    /** 弹出队列中所有场景直到根场景；
     * 场景替换运行中的场景
     * 运行场景会被删除。栈中没有更多场景，将会终止
     * 仅在运行场景中调用
     */
    void popToRootScene(void);

    /** Replaces the running scene with a new one. The running scene is terminated.
     * ONLY call it if there is a running scene.
     */
    /** 用新的场景替换运行场景。运行场景终止
     * 仅在运行场景中调用
     */
    void replaceScene(CCScene *pScene);

    /** Ends the execution, releases the running scene.
     It doesn't remove the OpenGL view from its parent. You have to do it manually.
     */
    /** 结束执行，释放当前运行场景
     * 但不会移除opengl视图。要手动操作
     */
    void end(void);

    /** Pauses the running scene.
     The running scene will be _drawed_ but all scheduled timers will be paused
     While paused, the draw rate will be 4 FPS to reduce CPU consumption
     */
    /** 暂停当前场景
     * 运行场景会被绘制，但所有预定计数器会暂停
     * 暂停时，绘图频率会为4FPS来减少cpu消耗
     */
    void pause(void);

    /** Resumes the paused scene
     The scheduled timers will be activated again.
     The "delta time" will be 0 (as if the game wasn't paused)
     */
    /** 恢复暂停场景
     * 预定计数器再次激活
     * 时间差为0，如果游戏没有暂停
     */
    void resume(void);

    /** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     If you don't want to pause your animation call [pause] instead.
     */
    /** 停止动画。什么都不绘制。主运行回路中不再触发任何事件
     * 如果你不想停止动画可以调用[pause]
     */
    virtual void stopAnimation(void) = 0;

    /** The main loop is triggered again.
     Call this function only if [stopAnimation] was called earlier
     @warning Don't call this function to start the main loop. To run the main loop call runWithScene
     */
    /** 主运行回路再次触发
     * 当停止动画时，才调用此方法
     * 不要使用此方法来启动主运行回路。使用runWithScene来启动
     */
    virtual void startAnimation(void) = 0;

    /** Draw the scene.
    This method is called every frame. Don't call it manually.
    */
    /** 绘制场景
     * 该方法会被每帧调用。不要手动
     */
    void drawScene(void);

    // Memory Helper

    /** Removes cached all cocos2d cached data.
     It will purge the CCTextureCache, CCSpriteFrameCache, CCLabelBMFont cache
     @since v0.99.3
     */
    /** 移除所有缓存数据
     * 将会清除所有对象的缓存
     */
    void purgeCachedData(void);

    // OpenGL Helper
    // opengl 帮助

    /** sets the OpenGL default values */
    /** 设置opengl默认值 */
    void setGLDefaultValues(void);

    /** enables/disables OpenGL alpha blending */
    /** 启用或禁用opengl阿尔法混合 */
    void setAlphaBlending(bool bOn);

    /** enables/disables OpenGL depth test */
    /** 启用或禁用opengl位深度测试 */
    void setDepthTest(bool bOn);

    virtual void mainLoop(void) = 0;

    /** The size in pixels of the surface. It could be different than the screen size.
    High-res devices might have a higher surface size than the screen size.
    Only available when compiled using SDK >= 4.0.
    @since v0.99.4
    */
    /** 以像素为单位的平面大小。不同设备则屏幕大小不同
     * 高清设备可能具有较高的屏幕大小
     * 仅在sdk大于4.0支持
     */
    void setContentScaleFactor(float scaleFactor);
    float getContentScaleFactor(void);

public:
    /** CCScheduler associated with this director
     @since v2.0
     */
    /** 导演关联预定 */
    CC_PROPERTY(CCScheduler*, m_pScheduler, Scheduler);

    /** CCActionManager associated with this director
     @since v2.0
     */
    /** 导演关联动作管理 */
    CC_PROPERTY(CCActionManager*, m_pActionManager, ActionManager);

    /** CCTouchDispatcher associated with this director
     @since v2.0
     */
    /** 导演关联触摸事件 */
    CC_PROPERTY(CCTouchDispatcher*, m_pTouchDispatcher, TouchDispatcher);

    /** CCKeypadDispatcher associated with this director
     @since v2.0
     */
    /** 导演关联键盘调用 */
    CC_PROPERTY(CCKeypadDispatcher*, m_pKeypadDispatcher, KeypadDispatcher);

    /** CCAccelerometer associated with this director
     @since v2.0
     */
    /** 导演关联加速计 */
    CC_PROPERTY(CCAccelerometer*, m_pAccelerometer, Accelerometer);

    /** returns a shared instance of the director */
    /** 返回导演共享实例 */
    static CCDirector* sharedDirector(void);

protected:

    void purgeDirector();
    bool m_bPurgeDirecotorInNextLoop; // this flag will be set to true in end() 在end()中将此标志设为true
    
    void setNextScene(void);
    
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, unsigned int* length);
    
    /** calculates delta time since last time it was called */  
    /** 计算时间差 */
    void calculateDeltaTime();
protected:
    /* The CCEGLView, where everything is rendered */
    /* gl视图，就是呈现所有对象的地方 */
    CCEGLView    *m_pobOpenGLView;

    double m_dAnimationInterval;
    double m_dOldAnimationInterval;

    /* landscape mode ? */
    /* 风景模式？ */
    bool m_bLandscape;
    
    bool m_bDisplayStats;
    float m_fAccumDt;
    float m_fFrameRate;
    
    CCLabelTTF *m_pFPSLabel;
    CCLabelTTF *m_pSPFLabel;
    CCLabelTTF *m_pDrawsLabel;
    
    /** Whether or not the Director is paused */
    /** 是否暂停 */
    bool m_bPaused;

    /* How many frames were called since the director started */
    /* 导演开始调用了多少帧 */
    unsigned int m_uTotalFrames;
    unsigned int m_uFrames;
    float m_fSecondsPerFrame;
     
    /* The running scene */
    /* 运行场景 */
    CCScene *m_pRunningScene;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference. */
    /* 下一个场景 */
    CCScene *m_pNextScene;
    
    /* If YES, then "old" scene will receive the cleanup message */
    /* 如果设为YES,则旧的场景会接收清理消息 */
    bool    m_bSendCleanupToScene;

    /* scheduled scenes */
    /* 调度场景 */
    CCArray* m_pobScenesStack;
    
    /* last time the main loop was updated */
    /* 主运行回路最后更新时间 */
    struct cc_timeval *m_pLastUpdate;

    /* delta time since last tick to main loop */
    /* 时间差 */
    float m_fDeltaTime;

    /* whether or not the next delta time will be zero */
    /* 下一个时间差是否为0 */
    bool m_bNextDeltaTimeZero;
    
    /* projection used */
    /* 投影使用 */
    ccDirectorProjection m_eProjection;

    /* window size in points */
    /* 以点为单位的窗口大小 */
    CCSize    m_obWinSizeInPoints;
    
    /* content scale factor */
    /* 内容比例因子 */
    float    m_fContentScaleFactor;

    /* store the fps string */
    /* 存储fps字符串 */
    char *m_pszFPS;

    /* This object will be visited after the scene. Useful to hook a notification node */
    /* 访问场景后该对象呗访问。用于通知节点 */
    CCNode *m_pNotificationNode;

    /* Projection protocol delegate */
    /* 投影协议 */
    CCDirectorDelegate *m_pProjectionDelegate;
    
    // CCEGLViewProtocol will recreate stats labels to fit visible rect
    // CCEGLViewProtocol将会重建标签来适于可见矩形
    friend class CCEGLViewProtocol;
};

/** 
 @brief DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 @since v0.8.2
 */
/**
 * 是导演的子类，用于刷新显示频率
 * 特征和限制：
 * 预定定时器和绘制适于刷新率同步
 * 仅在时间间隔为1/60 1/30 & 1/15的动画使用
 */
class CCDisplayLinkDirector : public CCDirector
{
public:
    CCDisplayLinkDirector(void) 
        : m_bInvalid(false)
    {}

    virtual void mainLoop(void);
    virtual void setAnimationInterval(double dValue);
    virtual void startAnimation(void);
    virtual void stopAnimation();

protected:
    bool m_bInvalid;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCDIRECTOR_H__
