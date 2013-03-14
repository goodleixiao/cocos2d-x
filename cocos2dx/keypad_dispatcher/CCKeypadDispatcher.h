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

#ifndef __CCKEYPAD_DISPATCHER_H__
#define __CCKEYPAD_DISPATCHER_H__

#include "CCKeypadDelegate.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup input    输入
 * @{
 */

typedef enum {
    // the back key clicked msg
    // 返回键点击信息
    kTypeBackClicked = 1,
    kTypeMenuClicked,
} ccKeypadMSGType;

struct _ccCArray;
/**
@class CCKeypadDispatcher
@brief Dispatch the keypad message from the phone
*/
// 处理键盘消息
class CC_DLL CCKeypadDispatcher : public CCObject
{
public:
    CCKeypadDispatcher();
    ~CCKeypadDispatcher();

    /**
    @brief add delegate to concern keypad msg
    */
    // 增加一个委托，关注键盘消息
    void addDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief remove the delegate from the delegates who concern keypad msg
    */
    // 移除一个委托，使用委托为参数
    void removeDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief force add the delegate
    */
    // 强制增加一个委托
    void forceAddDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief force remove the delegate
    */
    // 强制移除一个委托
    void forceRemoveDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief dispatch the key pad msg
    */
    // 调度键盘消息
    bool dispatchKeypadMSG(ccKeypadMSGType nMsgType);

protected:

    CCArray* m_pDelegates;
    bool m_bLocked;
    bool m_bToAdd;
    bool m_bToRemove;

    struct _ccCArray *m_pHandlersToAdd;
    struct _ccCArray *m_pHandlersToRemove;
};

// end of input group
/// @} 

NS_CC_END

#endif //__CCKEYPAD_DISPATCHER_H__
