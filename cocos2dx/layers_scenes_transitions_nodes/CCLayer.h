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

#ifndef __CCLAYER_H__
#define __CCLAYER_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "platform/CCAccelerometerDelegate.h"
#include "keypad_dispatcher/CCKeypadDelegate.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

typedef enum {
	kCCTouchesAllAtOnce,
	kCCTouchesOneByOne,
} ccTouchesMode;

/**
 * @addtogroup layer	层
 * @{
 */

class CCTouchScriptHandlerEntry;

//
// CCLayer
//
/** @brief CCLayer is a subclass of CCNode that implements the TouchEventsDelegate protocol.

All features from CCNode are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
/** 是节点的子类，实现触摸协议
 * 具有所有节点特性，增加了新的特性：接收触摸和加速计输入
 */
class CC_DLL CCLayer : public CCNode, public CCTouchDelegate, public CCAccelerometerDelegate, public CCKeypadDelegate
{
public:
    CCLayer();
    virtual ~CCLayer();
    virtual bool init();
    
    /** create one layer */
    // 创建一个层
    static CCLayer *create(void);

    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    // default implements are used to call script callback if exist
    // 默认实现的回调函数
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    // default implements are used to call script callback if exist
    // 默认回调
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    void registerScriptAccelerateHandler(int nHandler);
    void unregisterScriptAccelerateHandler(void);

    /** If isTouchEnabled, this method is called onEnter. Override it to change the
    way CCLayer receives touch events.
    ( Default: CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0); )
    Example:
    void CCLayer::registerWithTouchDispatcher()
    {
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,INT_MIN+1,true);
    }
    @since v0.8.0
    */
    // 是否启用触摸；启用，层接收触摸事件
    virtual void registerWithTouchDispatcher(void);
    
    /** Register script touch events handler */
    // 注册触摸事件处理脚本
    virtual void registerScriptTouchHandler(int nHandler, bool bIsMultiTouches = false, int nPriority = INT_MIN, bool bSwallowsTouches = false);
    /** Unregister script touch events handler */
    // 取消注册
    virtual void unregisterScriptTouchHandler(void);

    /** whether or not it will receive Touch events.
    You can enable / disable touch events with this property.
    Only the touches of this node will be affected. This "method" is not propagated to it's children.
    @since v0.8.1
    */
    // 是否接收触摸
    virtual bool isTouchEnabled();
    virtual void setTouchEnabled(bool value);
    
    virtual void setTouchMode(ccTouchesMode mode);
    virtual int getTouchMode();
    
    /** priority of the touch events. Default is 0 */
    // 触摸事件优先级，默认为0
    virtual void setTouchPriority(int priority);
    virtual int getTouchPriority();

    /** whether or not it will receive Accelerometer events
    You can enable / disable accelerometer events with this property.
    @since v0.8.1
    */
    // 是否接收加速计事件；可以改变其属性
    virtual bool isAccelerometerEnabled();
    virtual void setAccelerometerEnabled(bool value);
    virtual void setAccelerometerInterval(double interval);

    /** whether or not it will receive keypad events
    You can enable / disable accelerometer events with this property.
    it's new in cocos2d-x
    */
    // 是否接收键盘事件
    virtual bool isKeypadEnabled();
    virtual void setKeypadEnabled(bool value);

    /** Register keypad events handler */
    // 注册键盘处理
    void registerScriptKeypadHandler(int nHandler);
    /** Unregister keypad events handler */
    // 取消注册
    void unregisterScriptKeypadHandler(void);

    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);
    
    inline CCTouchScriptHandlerEntry* getScriptTouchHandlerEntry() { return m_pScriptTouchHandlerEntry; };
    inline CCScriptHandlerEntry* getScriptKeypadHandlerEntry() { return m_pScriptKeypadHandlerEntry; };
    inline CCScriptHandlerEntry* getScriptAccelerateHandlerEntry() { return m_pScriptAccelerateHandlerEntry; };
protected:   
    bool m_bTouchEnabled;
    bool m_bAccelerometerEnabled;
    bool m_bKeypadEnabled;
    
private:
    // Script touch events handler
    // 触摸事件处理脚本
    CCTouchScriptHandlerEntry* m_pScriptTouchHandlerEntry;
    CCScriptHandlerEntry* m_pScriptKeypadHandlerEntry;
    CCScriptHandlerEntry* m_pScriptAccelerateHandlerEntry;
    
    int m_nTouchPriority;
    ccTouchesMode m_eTouchMode;
    
    int  excuteScriptTouchHandler(int nEventType, CCTouch *pTouch);
    int  excuteScriptTouchHandler(int nEventType, CCSet *pTouches);
};

#ifdef __apple__
#pragma mark -
#pragma mark CCLayerRGBA
#endif

/** CCLayerRGBA is a subclass of CCLayer that implements the CCRGBAProtocol protocol using a solid color as the background.
 
 All features from CCLayer are valid, plus the following new features that propagate into children that conform to the CCRGBAProtocol:
 - opacity
 - RGB colors
 @since 2.1
 */
// 是层的子类，实现颜色协议；使用实心颜色作为背景色
// 具有层的所有特性，增加了：透明度，颜色值的属性
class CC_DLL CCLayerRGBA : public CCLayer, public CCRGBAProtocol
{
public:
    CREATE_FUNC(CCLayerRGBA);
    
    CCLayerRGBA();
    virtual ~CCLayerRGBA();
    
    virtual bool init();
    
    virtual GLubyte getOpacity();
    virtual GLubyte getDisplayedOpacity();
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled();
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    
    virtual const ccColor3B& getColor();
    virtual const ccColor3B& getDisplayedColor();
    virtual void setColor(const ccColor3B& color);
    virtual void updateDisplayedColor(const ccColor3B& parentColor);
    virtual bool isCascadeColorEnabled();
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    
    virtual void setOpacityModifyRGB(bool bValue) {}
    virtual bool isOpacityModifyRGB() { return false; }
protected:
	GLubyte		_displayedOpacity, _realOpacity;
	ccColor3B	_displayedColor, _realColor;
	bool		_cascadeOpacityEnabled, _cascadeColorEnabled;
};

//
// CCLayerColor
//
/** @brief CCLayerColor is a subclass of CCLayer that implements the CCRGBAProtocol protocol.

All features from CCLayer are valid, plus the following new features:
- opacity
- RGB colors
*/
// 是层的子类，实现颜色协议；具有层的所有特性，增加了：透明度和颜色值
class CC_DLL CCLayerColor : public CCLayerRGBA, public CCBlendProtocol
{
protected:
    ccVertex2F m_pSquareVertices[4];
    ccColor4F  m_pSquareColors[4];

public:
    CCLayerColor();
    virtual ~CCLayerColor();

    virtual void draw();
    virtual void setContentSize(const CCSize & var);
    
    static CCLayerColor* create();
    
    /** creates a CCLayer with color, width and height in Points */
    // 创建层，使用颜色，宽度，高度为参数
    static CCLayerColor * create(const ccColor4B& color, GLfloat width, GLfloat height);
    /** creates a CCLayer with color. Width and height are the window size. */
    // 创建层，使用颜色，窗口的宽和高为参数
    static CCLayerColor * create(const ccColor4B& color);

    virtual bool init();
    /** initializes a CCLayer with color, width and height in Points */
    // 初始化层，使用颜色，宽，高为参数
    virtual bool initWithColor(const ccColor4B& color, GLfloat width, GLfloat height);
    /** initializes a CCLayer with color. Width and height are the window size. */
    // 创建层，使用颜色，窗口的宽和高为参数
    virtual bool initWithColor(const ccColor4B& color);

    /** change width in Points*/
    // 改变宽度，以点为单位
    void changeWidth(GLfloat w);
    /** change height in Points*/
    // 改变高度，以点为单位
    void changeHeight(GLfloat h);
    /** change width and height in Points
    @since v0.8
    */
    // 改变高和宽，以点为单位
    void changeWidthAndHeight(GLfloat w ,GLfloat h);

    /** BlendFunction. Conforms to CCBlendProtocol protocol */
    // 符合混合协议
    CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)

    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    virtual void setColor(const ccColor3B &color);
    virtual void setOpacity(GLubyte opacity);

protected:
    virtual void updateColor();
};

//
// CCLayerGradient
//
/** @brief CCLayerGradient is a subclass of CCLayerColor that draws gradients across the background.

All features from CCLayerColor are valid, plus the following new features:
- direction
- final color
- interpolation mode

Color is interpolated between the startColor and endColor along the given
vector (starting at the origin, ending at the terminus).  If no vector is
supplied, it defaults to (0, -1) -- a fade from top to bottom.

If 'compressedInterpolation' is disabled, you will not see either the start or end color for
non-cardinal vectors; a smooth gradient implying both end points will be still
be drawn, however.

If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.

@since v0.99.5
*/
/** 梯度层
 * 是颜色层的子类，用于背景
 * 具有所有颜色层的特性，增加了新的特性：方向，最终颜色，插补模式
 * 
 * 颜色是插补开始颜色和结束颜色，给定一个矢量。没有矢量，默认为(0,-1)
 * 
 * 启用compressedInterpolation，你会看到颜色的渐变过程
 */
class CC_DLL CCLayerGradient : public CCLayerColor
{
public:

    /** Creates a full-screen CCLayer with a gradient between start and end. */
    // 创建层，使用开始，结束色为参数
    static CCLayerGradient* create(const ccColor4B& start, const ccColor4B& end);

    /** Creates a full-screen CCLayer with a gradient between start and end in the direction of v. */
    // 创建一个满屏层，使用一个梯度在开始和结束色，方向为参数
    static CCLayerGradient* create(const ccColor4B& start, const ccColor4B& end, const CCPoint& v);

    virtual bool init();
    /** Initializes the CCLayer with a gradient between start and end. */
    // 创建层，使用开始，结束色为参数
    virtual bool initWithColor(const ccColor4B& start, const ccColor4B& end);

    /** Initializes the CCLayer with a gradient between start and end in the direction of v. */
    // 创建一个满屏层，使用一个梯度在开始和结束色，方向为参数
    virtual bool initWithColor(const ccColor4B& start, const ccColor4B& end, const CCPoint& v);

    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_startColor, StartColor)
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_endColor, EndColor)
    CC_PROPERTY(GLubyte, m_cStartOpacity, StartOpacity)
    CC_PROPERTY(GLubyte, m_cEndOpacity, EndOpacity)
    CC_PROPERTY_PASS_BY_REF(CCPoint, m_AlongVector, Vector)

    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
    Default: YES
    */
    // 默认为启用插补
protected:
    bool m_bCompressedInterpolation;
public:
    virtual void setCompressedInterpolation(bool bCompressedInterpolation);
    virtual bool isCompressedInterpolation();
    
    static CCLayerGradient* create();

protected:
    virtual void updateColor();
};


/** @brief CCMultipleLayer is a CCLayer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
// 是层的子类，具有混合子对象的能力：支持一个或多个子对象；某一时刻只有一个子对象是激活的
class CC_DLL CCLayerMultiplex : public CCLayer
{
protected:
    unsigned int m_nEnabledLayer;
    CCArray*     m_pLayers;
public:
    CCLayerMultiplex();
    virtual ~CCLayerMultiplex();
    
    static CCLayerMultiplex* create();
    
    /** creates a CCMultiplexLayer with an array of layers.
     @since v2.1
     */
    // 创建层，使用层数组
    static CCLayerMultiplex* createWithArray(CCArray* arrayOfLayers);

    /** creates a CCLayerMultiplex with one or more layers using a variable argument list. */
    // 创建层，使用一个或多个层为参数
    static CCLayerMultiplex * create(CCLayer* layer, ... );

    /**
     * lua script can not init with undetermined number of variables
     * so add these functions to be used with lua.
     */
    // 创建层；
    static CCLayerMultiplex * createWithLayer(CCLayer* layer);

    void addLayer(CCLayer* layer);

    /** initializes a MultiplexLayer with one or more layers using a variable argument list. */
    // 初始化层，使用一个或多个层为参数
    bool initWithLayers(CCLayer* layer, va_list params);
    /** switches to a certain layer indexed by n. 
    The current (old) layer will be removed from it's parent with 'cleanup:YES'.
    */

    /** initializes a CCMultiplexLayer with an array of layers
    @since v2.1
    */
    // 使用数组来初始化
    bool initWithArray(CCArray* arrayOfLayers);

    void switchTo(unsigned int n);
    /** release the current layer and switches to another layer indexed by n.
    The current (old) layer will be removed from it's parent with 'cleanup:YES'.
    */
    // 交换替代层，使用序号为参数
    void switchToAndReleaseMe(unsigned int n);
};


// end of layer group
/// @}

NS_CC_END

#endif // __CCLAYER_H__

