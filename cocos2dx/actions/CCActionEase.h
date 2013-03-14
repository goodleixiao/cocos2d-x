/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2009 Jason Booth

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

#ifndef __ACTION_CCEASE_ACTION_H__
#define __ACTION_CCEASE_ACTION_H__

#include "CCActionInterval.h"

NS_CC_BEGIN

class CCObject;
class CCZone;

/**
 * @addtogroup actions  动作
 * @{
 */

/** 
 @brief Base class for Easing actions
 @ingroup Actions
 */
// 缓解动作
class CC_DLL CCActionEase : public CCActionInterval
{
public:
    virtual ~CCActionEase(void);

    /** initializes the action */
    // 初始化动作
    bool initWithAction(CCActionInterval *pAction);

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCActionInterval* getInnerAction();

public:

    /** creates the action */
    // 创建动作
    static CCActionEase* create(CCActionInterval *pAction);

protected:
    /** The inner action */
    // 内联动作
    CCActionInterval *m_pInner;
};

/** 
 @brief Base class for Easing actions with rate parameters
 @ingroup Actions
 */
// 带有速率参数的缓解动作
class CC_DLL CCEaseRateAction : public CCActionEase
{
public:
    virtual ~CCEaseRateAction(void);

    /** set rate value for the actions */
    // 设置速率值
    inline void setRate(float rate) { m_fRate = rate; }
    /** get rate value for the actions */
    // 获取速率值
    inline float getRate(void) { return m_fRate; }

    /** Initializes the action with the inner action and the rate parameter */
    // 使用间隔动作和速率初始化
    bool initWithAction(CCActionInterval *pAction, float fRate);

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual CCActionInterval* reverse(void);

public:

    /** Creates the action with the inner action and the rate parameter */
    // 使用间隔动作和速率创建
    static CCEaseRateAction* create(CCActionInterval* pAction, float fRate);

protected:
    float m_fRate;
};

/** 
 @brief CCEaseIn action with a rate
 @ingroup Actions
 */
// 向里缓解动作
class CC_DLL CCEaseIn : public CCEaseRateAction
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);
public:

    /** Creates the action with the inner action and the rate parameter */
    // 使用间隔动作和速率初始化
    static CCEaseIn* create(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEaseOut action with a rate
 @ingroup Actions
 */
// 向外缓解动作
class CC_DLL CCEaseOut : public CCEaseRateAction
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse();
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the rate parameter */
    // 使用间隔动作和速率初始化
    static CCEaseOut* create(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEaseInOut action with a rate
 @ingroup Actions
 */
// 带有速率参数缓解动作
class CC_DLL CCEaseInOut : public CCEaseRateAction
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual CCActionInterval* reverse(void);

public:

    /** Creates the action with the inner action and the rate parameter */
    // 使用间隔动作和速率初始化
    static CCEaseInOut* create(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEase Exponential In
 @ingroup Actions
 */
// 指数缓解动作
class CC_DLL CCEaseExponentialIn : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    // 创建动作
    static CCEaseExponentialIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Exponential Out
 @ingroup Actions
 */
// 指数缓解动作
class CC_DLL CCEaseExponentialOut : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    // 创建动作
    static CCEaseExponentialOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Exponential InOut
 @ingroup Actions
 */
// 指数缓解动作 出
class CC_DLL CCEaseExponentialInOut : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual CCActionInterval* reverse();

public:

    /** creates the action */
    // 创建动作
    static CCEaseExponentialInOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine In
 @ingroup Actions
 */
// 正弦缓解动作
class CC_DLL CCEaseSineIn : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    // 创建动作
    static CCEaseSineIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine Out
 @ingroup Actions
 */
// 正弦缓解动作
class CC_DLL CCEaseSineOut : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    // 创建动作
    static CCEaseSineOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine InOut
 @ingroup Actions
 */
// 正弦缓解动作
class CC_DLL CCEaseSineInOut : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual CCActionInterval* reverse();

public:

    /** creates the action */
    // 创建动作
    static CCEaseSineInOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Elastic abstract class
 @since v0.8.2
 @ingroup Actions
 */
// 弹性缓解类
class CC_DLL CCEaseElastic : public CCActionEase
{
public:
    /** get period of the wave in radians. default is 0.3 */
    // 获取波半径的周期，默认为0.3
    inline float getPeriod(void) { return m_fPeriod; }
    /** set period of the wave in radians. */
    // 设置波周期，以弧度
    inline void setPeriod(float fPeriod) { m_fPeriod = fPeriod; }

    /** Initializes the action with the inner action and the period in radians (default is 0.3) */
    // 初始化一个动作，半径为参数
    bool initWithAction(CCActionInterval *pAction, float fPeriod = 0.3f);

    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    // 创建一个动作，使用间隔动作和周期以弧度为单位
    static CCEaseElastic* create(CCActionInterval *pAction, float fPeriod);
    static CCEaseElastic* create(CCActionInterval *pAction);
protected:
    float m_fPeriod;
};

/** 
 @brief Ease Elastic In action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 弹性动作
class CC_DLL CCEaseElasticIn : public CCEaseElastic
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    // 创建一个动作，使用间隔动作和周期以弧度为单位
    static CCEaseElasticIn* create(CCActionInterval *pAction, float fPeriod);
    static CCEaseElasticIn* create(CCActionInterval *pAction);
};

/** 
 @brief Ease Elastic Out action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 弹性动作
class CC_DLL CCEaseElasticOut : public CCEaseElastic
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    // 创建一个动作，使用间隔动作和周期以弧度为单位
    static CCEaseElasticOut* create(CCActionInterval *pAction, float fPeriod);
    static CCEaseElasticOut* create(CCActionInterval *pAction);
};

/** 
 @brief Ease Elastic InOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 缓解动作
class CC_DLL CCEaseElasticInOut : public CCEaseElastic
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    // 创建一个动作，使用间隔动作和周期以弧度为单位
    static CCEaseElasticInOut* create(CCActionInterval *pAction, float fPeriod);
    static CCEaseElasticInOut* create(CCActionInterval *pAction);
};

/** 
 @brief CCEaseBounce abstract class.
 @since v0.8.2
 @ingroup Actions
*/
// 弹跳缓解动作
class CC_DLL CCEaseBounce : public CCActionEase
{
public:
    float bounceTime(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual CCActionInterval* reverse();

public:

    /** creates the action */
    // 创建动作
    static CCEaseBounce* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBounceIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
*/
// 创建缓解动作
class CC_DLL CCEaseBounceIn : public CCEaseBounce
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    // 创建动作
    static CCEaseBounceIn* create(CCActionInterval* pAction);
};

/** 
 @brief EaseBounceOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 弹跳缓解出动作
class CC_DLL CCEaseBounceOut : public CCEaseBounce
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    // 创建动作
    static CCEaseBounceOut* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBounceInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 弹跳缓解动作
class CC_DLL CCEaseBounceInOut : public CCEaseBounce
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual CCActionInterval* reverse();

public:

    /** creates the action */
    // 创建动作
    static CCEaseBounceInOut* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 返回缓解动作
class CC_DLL CCEaseBackIn : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    // 创建动作
    static CCEaseBackIn* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 向外返回动作
class CC_DLL CCEaseBackOut : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    // 创建动作
    static CCEaseBackOut* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
// 返回外动作
class CC_DLL CCEaseBackInOut : public CCActionEase
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual CCActionInterval* reverse();

public:

    /** creates the action */
    // 创建动作
    static CCEaseBackInOut* create(CCActionInterval* pAction);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__
