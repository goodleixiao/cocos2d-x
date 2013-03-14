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

#ifndef __ACTIONS_CCACTION_H__
#define __ACTIONS_CCACTION_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

enum {
    //! Default tag
    //! 默认标示
    kCCActionTagInvalid = -1,
};

/**
 * @addtogroup actions      动作
 * @{
 */

/** 
@brief Base class for CCAction objects.
 */
// 动作基类
class CC_DLL CCAction : public CCObject 
{
public:
    CCAction(void);
    virtual ~CCAction(void);

    const char* description();

    virtual CCObject* copyWithZone(CCZone *pZone);

    //! return true if the action has finished
    //! 若动作完成，则返回true
    virtual bool isDone(void);

    //! called before the action start. It will also set the target.
    //! 动作开始时调用
    virtual void startWithTarget(CCNode *pTarget);

    /** 
    called after the action has finished. It will set the 'target' to nil.
    IMPORTANT: You should never call "[action stop]" manually. Instead, use: "target->stopAction(action);"
    */
    // 动作结束时调用，可以设置目标为nil; 不要调用[aciton stop],使用target->stopAction(action)
    virtual void stop(void);

    //! called every frame with it's delta time. DON'T override unless you know what you are doing.
    //! 每帧调用，使用时间差；不要重载
    virtual void step(float dt);

    /** 
    called once per frame. time a value between 0 and 1

    For example: 
    - 0 means that the action just started
    - 0.5 means that the action is in the middle
    - 1 means that the action is over
    */
    // 每帧调用一次，0为开始，0.5为中间，1为结束
    virtual void update(float time);
    
    inline CCNode* getTarget(void) { return m_pTarget; }
    /** The action will modify the target properties. */
    // 修改目标属性
    inline void setTarget(CCNode *pTarget) { m_pTarget = pTarget; }
    
    inline CCNode* getOriginalTarget(void) { return m_pOriginalTarget; } 
    /** Set the original target, since target can be nil.
    Is the target that were used to run the action. Unless you are doing something complex, like CCActionManager, you should NOT call this method.
    The target is 'assigned', it is not 'retained'.
    @since v0.8.2
    */
    // 设置原目标；目标为assigned,不是retained
    inline void setOriginalTarget(CCNode *pOriginalTarget) { m_pOriginalTarget = pOriginalTarget; }

    inline int getTag(void) { return m_nTag; }
    inline void setTag(int nTag) { m_nTag = nTag; }

public:
    /** Create an action */
    // 创建一个动作
    static CCAction* create();
protected:
    CCNode    *m_pOriginalTarget;
    /** The "target".
    The target will be set with the 'startWithTarget' method.
    When the 'stop' method is called, target will be set to nil.
    The target is 'assigned', it is not 'retained'.
    */
    // 目标；启动方法，而停止方法调用时，目标设为nil。目标位assigned，不是retained
    CCNode    *m_pTarget;
    /** The action tag. An identifier of the action */
    // 动作标示
    int     m_nTag;
};

/** 
@brief 
 Base class actions that do have a finite time duration.
 Possible actions:
   - An action with a duration of 0 seconds
   - An action with a duration of 35.5 seconds

 Infinite time actions are valid
 */
// 瞬时动作，具有一个瞬时间隔；可能为0或者35。5秒；则为有效
class CC_DLL CCFiniteTimeAction : public CCAction
{
public:
    CCFiniteTimeAction()
        : m_fDuration(0)
    {}
    virtual ~CCFiniteTimeAction(){}
    //! get duration in seconds of the action
    //! 获取动作间隔
    inline float getDuration(void) { return m_fDuration; }
    //! set duration in seconds of the action
    //! 设置动作时间间隔
    inline void setDuration(float duration) { m_fDuration = duration; }

    /** returns a reversed action */
    // 返回一个反向动作
    virtual CCFiniteTimeAction* reverse(void);
protected:
    //! duration in seconds
    //! 时间间隔
    float m_fDuration;
};

class CCActionInterval;
class CCRepeatForever;

/** 
 @brief Changes the speed of an action, making it take longer (speed>1)
 or less (speed<1) time.
 Useful to simulate 'slow motion' or 'fast forward' effect.
 @warning This action can't be Sequenceable because it is not an CCIntervalAction
 */
// 改变动作速度；用于模拟慢与块效果，不能序列化，不是衣蛾间隔动作
class CC_DLL CCSpeed : public CCAction
{
public:
    CCSpeed()
        : m_fSpeed(0.0)
        , m_pInnerAction(NULL)
    {}
    virtual ~CCSpeed(void);

    inline float getSpeed(void) { return m_fSpeed; }
    /** alter the speed of the inner function in runtime */
    // 设置速度
    inline void setSpeed(float fSpeed) { m_fSpeed = fSpeed; }

    /** initializes the action */
    // 初始化动作
    bool initWithAction(CCActionInterval *pAction, float fSpeed);

    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void startWithTarget(CCNode* pTarget);
    virtual void stop();
    virtual void step(float dt);
    virtual bool isDone(void);
    virtual CCActionInterval* reverse(void);

    void setInnerAction(CCActionInterval *pAction);

    inline CCActionInterval* getInnerAction()
    {
        return m_pInnerAction;
    }

public:
    /** create the action */
    // 创建动作
    static CCSpeed* create(CCActionInterval* pAction, float fSpeed);
protected:
    float m_fSpeed;
    CCActionInterval *m_pInnerAction;
};

/** 
@brief CCFollow is an action that "follows" a node.

Eg:
layer->runAction(CCFollow::actionWithTarget(hero));

Instead of using CCCamera as a "follower", use this action instead.
@since v0.99.2
*/
// 是一个动作跟随节点；如layer->runAction(CCFollow::actionWithTarget(hero)); 可以替代摄像做为跟随者
class CC_DLL CCFollow : public CCAction
{
public:
    CCFollow()
        : m_pobFollowedNode(NULL)
        , m_bBoundarySet(false)
        , m_bBoundaryFullyCovered(false)        
        , m_fLeftBoundary(0.0)
        , m_fRightBoundary(0.0)
        , m_fTopBoundary(0.0)
        , m_fBottomBoundary(0.0)
    {}
    virtual ~CCFollow(void);
    
    inline bool isBoundarySet(void) { return m_bBoundarySet; }
    /** alter behavior - turn on/off boundary */
    // 改变属性，边界设置
    inline void setBoudarySet(bool bValue) { m_bBoundarySet = bValue; }

    /** initializes the action with a set boundary */
    // 带有边界的动作初始化
    bool initWithTarget(CCNode *pFollowedNode, const CCRect& rect = CCRectZero);

    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void step(float dt);
    virtual bool isDone(void);
    virtual void stop(void);

public:
    /** creates the action with a set boundary,
    It will work with no boundary if @param rect is equal to CCRectZero.
    */
    // 创建动作，边界为CCRectZero
    static CCFollow* create(CCNode *pFollowedNode, const CCRect& rect = CCRectZero);
protected:
    // node to follow
    // 跟随节点
    CCNode *m_pobFollowedNode;

    // whether camera should be limited to certain area
    // 限制摄像在特定范围内
    bool m_bBoundarySet;

    // if screen size is bigger than the boundary - update not needed
    // 若果屏幕大小大于边界，不在更新
    bool m_bBoundaryFullyCovered;

    // fast access to the screen dimensions
    // 快速访问屏幕尺寸
    CCPoint m_obHalfScreenSize;
    CCPoint m_obFullScreenSize;

    // world boundaries
    // 边界值
    float m_fLeftBoundary;
    float m_fRightBoundary;
    float m_fTopBoundary;
    float m_fBottomBoundary;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTIONS_CCACTION_H__
