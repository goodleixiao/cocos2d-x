/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Erawppa
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

#ifndef __CCNOTIFICATIONCENTER_H__
#define __CCNOTIFICATIONCENTER_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

class CC_DLL CCNotificationCenter : public CCObject
{
public:
    /** CCNotificationCenter constructor */
    // 通知中心构造
    CCNotificationCenter();

    /** CCNotificationCenter destructor */
    // 通知中心析构
    ~CCNotificationCenter();
    
    /** Gets the single instance of CCNotificationCenter. */
    // 获取单例
    static CCNotificationCenter *sharedNotificationCenter(void);

    /** Destroys the single instance of CCNotificationCenter. */
    // 清除单例
    static void purgeNotificationCenter(void);

    /** @brief Adds an observer for the specified target.
     *  @param target The target which wants to observe notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    // 增加一个观察者到指定目标上； 参数：目标，选择器，通知名称，额外参数
    void addObserver(CCObject *target, 
                     SEL_CallFuncO selector,
                     const char *name,
                     CCObject *obj);

    /** @brief Removes the observer by the specified target and name.
     *  @param target The target of this notification.
     *  @param name The name of this notification. 
     */
    // 移除观察者，使用目标，通知名称为参数
    void removeObserver(CCObject *target,const char *name);
    
    /** @brief Registers one hander for script binding.
     *  @note Only supports Lua Binding now.
     *  @param handler The lua handler.
     */
    // 注册一个处理
    void registerScriptObserver(int handler);

    /** Unregisters script observer */
    // 取消脚本观察者
    void unregisterScriptObserver(void);
    
    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     */
    // 发布一个通知事件，使用通知名称
    void postNotification(const char *name);

    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     *  @param object The extra parameter.
     */
    //// 发布一个通知事件，使用通知名称, 对象（为额外参数）为参数
    void postNotification(const char *name, CCObject *object);
    
    /** @brief Gets script handler.
     *  @note Only supports Lua Binding now.
     *  @return The script handle.
     */
    // 获取脚本管理者，用于Lua; 
    inline int getScriptHandler() { return m_scriptHandler; };
private:
    // internal functions

    // Check whether the observer exists by the specified target and name.
    // 检测是否已经存在观察者，使用目标，通知名称为参数
    bool observerExisted(CCObject *target,const char *name);
    
    // variables
    //  变量
    CCArray *m_observers;
    int     m_scriptHandler;
};

class CC_DLL CCNotificationObserver : public CCObject
{
public:
    /** @brief CCNotificationObserver constructor
     *  @param target The target which wants to observer notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    // 通知观察者构造， 参数：目标，选择器，名称，对象（额外参数）
    CCNotificationObserver(CCObject *target, 
                           SEL_CallFuncO selector,
                           const char *name,
                           CCObject *obj);

    /** CCNotificationObserver destructor function */
    // 析构
    ~CCNotificationObserver();      
    
    /** Invokes the callback function of this observer */
    // 回调
    void performSelector(CCObject *obj);
private:
    CC_PROPERTY_READONLY(CCObject *, m_target, Target);
    CC_PROPERTY_READONLY(SEL_CallFuncO, m_selector, Selector);
    CC_PROPERTY_READONLY(char *, m_name, Name);
    CC_PROPERTY_READONLY(CCObject *, m_object, Object);
};

NS_CC_END

#endif//__CCNOTIFICATIONCENTER_H__
