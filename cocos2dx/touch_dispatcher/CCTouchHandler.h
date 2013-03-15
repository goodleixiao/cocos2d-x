/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      Valentin Milea

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

#ifndef __TOUCH_DISPATCHER_CCTOUCH_HANDLER_H__
#define __TOUCH_DISPATCHER_CCTOUCH_HANDLER_H__

#include "CCTouchDelegateProtocol.h"
#include "CCTouchDispatcher.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCSet.h"

NS_CC_BEGIN

/**
 * @addtogroup input  输入
 * @{
 */

/**
 CCTouchHandler
 Object than contains the delegate and priority of the event handler.
*/
// 每个处理包含委托和优先级
class CC_DLL  CCTouchHandler : public CCObject
{
public:
    virtual ~CCTouchHandler(void);

    /** delegate */
    // 委托
    CCTouchDelegate* getDelegate();
    void setDelegate(CCTouchDelegate *pDelegate);

    /** priority */
    // 优先级
    int getPriority(void);
    void setPriority(int nPriority);

    /** enabled selectors */
    // 启用选择器
    int getEnabledSelectors(void);
    void setEnalbedSelectors(int nValue);

    /** initializes a TouchHandler with a delegate and a priority */
    // 初始化处理程序，使用委托和优先级为参数
    virtual bool initWithDelegate(CCTouchDelegate *pDelegate, int nPriority);

public:
    /** allocates a TouchHandler with a delegate and a priority */
    // 分配一个处理程序，使用委托和优先级为参数
    static CCTouchHandler* handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority);

protected:
    CCTouchDelegate *m_pDelegate;
    int m_nPriority;
    int m_nEnabledSelectors;
};

/** CCStandardTouchHandler
 It forwards each event to the delegate.
 */
// 标准委托
class CC_DLL  CCStandardTouchHandler : public CCTouchHandler
{
public:
    /** initializes a TouchHandler with a delegate and a priority */
    // 初始化处理程序，使用委托和优先级为参数
    virtual bool initWithDelegate(CCTouchDelegate *pDelegate, int nPriority);

public:
    /** allocates a TouchHandler with a delegate and a priority */
    // 分配一个处理程序，使用委托和优先级为参数
    static CCStandardTouchHandler* handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority);
};

/**
 CCTargetedTouchHandler
 Object than contains the claimed touches and if it swallows touches.
 Used internally by TouchDispatcher
 */
// 目标委托。 对象要求触摸有触感
class CC_DLL  CCTargetedTouchHandler : public CCTouchHandler
{
public:
    ~CCTargetedTouchHandler(void);

    /** whether or not the touches are swallowed */
    // 是否有触感
    bool isSwallowsTouches(void);
    void setSwallowsTouches(bool bSwallowsTouches);

    /** MutableSet that contains the claimed touches */
    // 返回多个触摸
    CCSet* getClaimedTouches(void);

    /** initializes a TargetedTouchHandler with a delegate, a priority and whether or not it swallows touches or not */
    // 初始化处理程序，使用委托，优先级，是否有吞噬为参数
    bool initWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow);

public:
    /** allocates a TargetedTouchHandler with a delegate, a priority and whether or not it swallows touches or not */
    //  分配处理程序，使用委托，优先级，是否有吞噬为参数
    static CCTargetedTouchHandler* handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow);

protected:
    bool m_bSwallowsTouches;
    CCSet *m_pClaimedTouches;
};

// end of input group
/// @}

NS_CC_END

#endif // __TOUCH_DISPATCHER_CCTOUCH_HANDLER_H__
