/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011 Zynga Inc.

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

#ifndef __CCINSTANT_ACTION_H__
#define __CCINSTANT_ACTION_H__

#include <string>
#include "ccTypeInfo.h"
#include "CCAction.h"

NS_CC_BEGIN

/**
 * @addtogroup actions		动作
 * @{
 */

/** 
@brief Instant actions are immediate actions. They don't have a duration like
the CCIntervalAction actions.
*/ 
// 片刻，瞬间动作是立刻动作，没有间隔像CCIntervalAction动作
class CC_DLL CCActionInstant : public CCFiniteTimeAction //<NSCopying>
{
public:
    CCActionInstant();
    virtual ~CCActionInstant(){}
    // CCAction methods
    // 动作方法
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual bool isDone(void);
    virtual void step(float dt);
    virtual void update(float time);
    //CCFiniteTimeAction method
    // 有限时间动作方法
    virtual CCFiniteTimeAction * reverse(void);
};

/** @brief Show the node
*/
// 显示节点
class CC_DLL CCShow : public CCActionInstant
{
public:
    CCShow(){}
    virtual ~CCShow(){}
    //super methods
    //父类方法
    virtual void update(float time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);
public:

    /** Allocates and initializes the action */
    // 分配和初始化动作
    static CCShow * create();
};



/** 
@brief Hide the node
*/
//隐藏节点
class CC_DLL CCHide : public CCActionInstant
{
public:
    CCHide(){}
    virtual ~CCHide(){}
    //super methods
    //父类方法
    virtual void update(float time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);
public:

    /** Allocates and initializes the action */
    // 分配和初始化动作
    static CCHide * create();
};

/** @brief Toggles the visibility of a node
*/
// 切换节点可见性
class CC_DLL CCToggleVisibility : public CCActionInstant
{
public:
    CCToggleVisibility(){}
    virtual ~CCToggleVisibility(){}
    //super method
    //父类方法
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone *pZone);
public:

    /** Allocates and initializes the action */
    // 分配和初始化动作
    static CCToggleVisibility * create();
};

/** 
@brief Flips the sprite horizontally
@since v0.99.0
*/
//水平翻动
class CC_DLL CCFlipX : public CCActionInstant
{
public:
    CCFlipX()
        :m_bFlipX(false)
    {}
    virtual ~CCFlipX(){}

    /** create the action */
    // 创建动作
    static CCFlipX * create(bool x);

    /** init the action */
    // 初始化动作
    bool initWithFlipX(bool x);
    //super methods
    //父类动作
    virtual void update(float time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);

protected:
    bool    m_bFlipX;
};

/** 
@brief Flips the sprite vertically
@since v0.99.0
*/
// 翻动精灵垂直动作
class CC_DLL CCFlipY : public CCActionInstant
{
public:
    CCFlipY()
        :m_bFlipY(false)
    {}
    virtual ~CCFlipY(){}

    /** create the action */
    // 创建动作
    static CCFlipY * create(bool y);

    /** init the action */
    // 初始化动作
    bool initWithFlipY(bool y);
    //super methods
    // 父类方法
    virtual void update(float time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);

protected:
    bool    m_bFlipY;
};

/** @brief Places the node in a certain position
*/
// 放置节点，在指定位置
class CC_DLL CCPlace : public CCActionInstant //<NSCopying>
{
public:
    CCPlace(){}
    virtual ~CCPlace(){}

    /** creates a Place action with a position */
    // 创建一个放置动作用指定位置
    static CCPlace * create(const CCPoint& pos);
    /** Initializes a Place action with a position */
    // 用位置参数放置动作
    bool initWithPosition(const CCPoint& pos);
    //super methods
    // 父类方法
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone *pZone);
protected:
    CCPoint m_tPosition;
};

/** @brief Calls a 'callback'
*/
// 回调
class CC_DLL CCCallFunc : public CCActionInstant //<NSCopying>
{
public:
    CCCallFunc()
        : m_pSelectorTarget(NULL)
		, m_nScriptHandler(0)
        , m_pCallFunc(NULL)
    {
    }
    virtual ~CCCallFunc();

    /** creates the action with the callback 

    typedef void (CCObject::*SEL_CallFunc)();
    */
    //创建回调动作
    static CCCallFunc * create(CCObject* pSelectorTarget, SEL_CallFunc selector);

	/** creates the action with the handler script function */
	// 使用脚本函数创建动作
	static CCCallFunc * create(int nHandler);

	/** initializes the action with the callback 
    
    typedef void (CCObject::*SEL_CallFunc)();
    */
    // 使用回调初始化动作
    virtual bool initWithTarget(CCObject* pSelectorTarget);
    /** executes the callback */
    // 执行回调
    virtual void execute();
    //super methods
    // 父类方法
    virtual void update(float time);
    CCObject * copyWithZone(CCZone *pZone);

    inline CCObject* getTargetCallback()
    {
        return m_pSelectorTarget;
    }

    inline void setTargetCallback(CCObject* pSel)
    {
        if (pSel != m_pSelectorTarget)
        {
            CC_SAFE_RETAIN(pSel);
            CC_SAFE_RELEASE(m_pSelectorTarget);
            m_pSelectorTarget = pSel; 
        }
    }
    
    inline int getScriptHandler() { return m_nScriptHandler; };
protected:
    /** Target that will be called */
    // 调用目标
    CCObject*   m_pSelectorTarget;

	int m_nScriptHandler;

    union
    {
        SEL_CallFunc    m_pCallFunc;
        SEL_CallFuncN    m_pCallFuncN;
        SEL_CallFuncND    m_pCallFuncND;
        SEL_CallFuncO   m_pCallFuncO;
    };
};

/** 
@brief Calls a 'callback' with the node as the first argument
N means Node
*/
// 使用节点最为第一个参数的回调
class CC_DLL CCCallFuncN : public CCCallFunc, public TypeInfo
{
public:
    CCCallFuncN(){}
    virtual ~CCCallFuncN(){}
    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CCCallFunc).name());
		return id;
    }

    /** creates the action with the callback 

    typedef void (CCObject::*SEL_CallFuncN)(CCNode*);
    */
    // 创建回调动作
    static CCCallFuncN * create(CCObject* pSelectorTarget, SEL_CallFuncN selector);

	/** creates the action with the handler script function */
	// 创建一个动作用脚本函数
	static CCCallFuncN * create(int nHandler);

    /** initializes the action with the callback 

    typedef void (CCObject::*SEL_CallFuncN)(CCNode*);
    */
    // 初始化动作使用回调
    virtual bool initWithTarget(CCObject* pSelectorTarget, SEL_CallFuncN selector);
    // super methods
    // 父类方法
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void execute();
};


/** 
@brief Calls a 'callback' with the node as the first argument and the 2nd argument is data
* ND means: Node and Data. Data is void *, so it could be anything.
*/
// 使用节点和数据作为参数创建回调
class CC_DLL CCCallFuncND : public CCCallFuncN
{
public:
    virtual long getClassTypeInfo() {
        static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CCCallFunc).name());
		return id;
    }

    /** creates the action with the callback and the data to pass as an argument */
    // 创建动作回调，数据作为参数
    static CCCallFuncND * create(CCObject* pSelectorTarget, SEL_CallFuncND selector, void* d);

    /** initializes the action with the callback and the data to pass as an argument */
    // 初始化动作，使用回调，数据作为参数
    virtual bool initWithTarget(CCObject* pSelectorTarget, SEL_CallFuncND selector, void* d);
    // super methods
    // 父类方法
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void execute();

protected:
    void            *m_pData;
};


/**
@brief Calls a 'callback' with an object as the first argument.
O means Object.
@since v0.99.5
*/
// 使用对象作为参数的回调
class CC_DLL CCCallFuncO : public CCCallFunc, public TypeInfo
{
public:
    CCCallFuncO();
    virtual ~CCCallFuncO();

    virtual long getClassTypeInfo() {
	    static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CCCallFunc).name());
		return id;
    }

    /** creates the action with the callback 

    typedef void (CCObject::*SEL_CallFuncO)(CCObject*);
    */
    // 创建动作
    static CCCallFuncO * create(CCObject* pSelectorTarget, SEL_CallFuncO selector, CCObject* pObject);

    /** initializes the action with the callback 

    typedef void (CCObject::*SEL_CallFuncO)(CCObject*);
    */
    // 初始化动作用回调： 声明定义typedef void (CCObject::*SEL_CallFuncO)(CCObject*);
    virtual bool initWithTarget(CCObject* pSelectorTarget, SEL_CallFuncO selector, CCObject* pObject);
    // super methods
    // 父类方法
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void execute();

    inline CCObject* getObject()
    {
        return m_pObject;
    }

    inline void setObject(CCObject* pObj)
    {
        if (pObj != m_pObject)
        {
            CC_SAFE_RELEASE(m_pObject);
            m_pObject = pObj;
            CC_SAFE_RETAIN(m_pObject);
        }
    }

protected:
    /** object to be passed as argument */
    // 对象作为参数
    CCObject* m_pObject;
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
