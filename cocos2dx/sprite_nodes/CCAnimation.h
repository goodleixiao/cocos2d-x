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
#ifndef __CC_ANIMATION_H__
#define __CC_ANIMATION_H__

#include "platform/CCPlatformConfig.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCGeometry.h"
#include "CCSpriteFrame.h"
#include <string>

NS_CC_BEGIN

class CCTexture2D;
class CCSpriteFrame;

/**
 * @addtogroup sprite_nodes  精灵节点
 * @{
 */

/** CCAnimationFrame
 A frame of the animation. It contains information like:
    - sprite frame name
    - # of delay units.
    - offset
 
 @since v2.0
 */
// 动画帧。是动画的一帧；包括：精灵帧，延时单元，偏移量
class CC_DLL CCAnimationFrame : public CCObject
{
public:
    CCAnimationFrame();
    virtual ~CCAnimationFrame();
    virtual CCObject* copyWithZone(CCZone* pZone);
    /** initializes the animation frame with a spriteframe, number of delay units and a notification user info */
    // 初始化动画帧，使用精灵帧，延时，一个通知用户信息为参数
    bool initWithSpriteFrame(CCSpriteFrame* spriteFrame, float delayUnits, CCDictionary* userInfo);
    
    /** CCSpriteFrameName to be used */
    // 精灵帧
    CC_SYNTHESIZE_RETAIN(CCSpriteFrame*, m_pSpriteFrame, SpriteFrame)

    /**  how many units of time the frame takes */
    // 帧占用的时间
    CC_SYNTHESIZE(float, m_fDelayUnits, DelayUnits)

    /**  A CCAnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast. */
    // 通知信息会广播，当帧显示时；以字典形式
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_pUserInfo, UserInfo)
};




/** A CCAnimation object is used to perform animations on the CCSprite objects.

The CCAnimation object contains CCAnimationFrame objects, and a possible delay between the frames.
You can animate a CCAnimation object by using the CCAnimate action. Example:

[sprite runAction:[CCAnimate actionWithAnimation:animation]];

*/
// 动画对象，呈现精灵对象动画的过程
// 一个动画对象包括：动画帧对象，二帧之间的延时；可以执行此动画对象，使用CCAnimate动作如：
// [sprite runAction:[CCAnimate actionWithAnimation:animation]];
class CC_DLL CCAnimation : public CCObject
{
public:
    CCAnimation();
    ~CCAnimation(void);
public:
    /** Creates an animation
    @since v0.99.5
    */
    // 创建动画
    static CCAnimation* create(void);

    /* Creates an animation with an array of CCSpriteFrame and a delay between frames in seconds.
     The frames will be added with one "delay unit".
     @since v0.99.5
    */
    // 创建动画，使用动画帧数组和延时为参数
    static CCAnimation* createWithSpriteFrames(CCArray* arrayOfSpriteFrameNames, float delay = 0.0f);

    /* Creates an animation with an array of CCAnimationFrame, the delay per units in seconds and and how many times it should be executed.
     @since v2.0
     */
    // 创建动画，使用动画帧数组，延时，循环次数
    static CCAnimation* create(CCArray *arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops);
    static CCAnimation* create(CCArray *arrayOfAnimationFrameNames, float delayPerUnit) {
        return CCAnimation::create(arrayOfAnimationFrameNames, delayPerUnit, 1);
    }

    /** Adds a CCSpriteFrame to a CCAnimation.
     The frame will be added with one "delay unit".
    */
    // 增加一个精灵帧到动画
    void addSpriteFrame(CCSpriteFrame *pFrame);

    /** Adds a frame with an image filename. Internally it will create a CCSpriteFrame and it will add it.
     The frame will be added with one "delay unit".
     Added to facilitate the migration from v0.8 to v0.9.
     */  
    // 增加精灵帧，使用图片文件名称为参数
    void addSpriteFrameWithFileName(const char *pszFileName);

    /** Adds a frame with a texture and a rect. Internally it will create a CCSpriteFrame and it will add it.
     The frame will be added with one "delay unit".
     Added to facilitate the migration from v0.8 to v0.9.
     */
    // 增加帧使用纹理和大小为参数； 内部创建精灵帧被添加。 使用一个延时单元
    void addSpriteFrameWithTexture(CCTexture2D* pobTexture, const CCRect& rect);

    bool init();

    /** Initializes a CCAnimation with frames and a delay between frames
    @since v0.99.5
    */
    // 初始化动画，使用帧数组，延时为参数
    bool initWithSpriteFrames(CCArray *pFrames, float delay = 0.0f);

    /** Initializes a CCAnimation with CCAnimationFrame
    @since v2.0
    */
    // 初始化动画，使用动画帧，延时，次数为参数
    bool initWithAnimationFrames(CCArray* arrayOfAnimationFrames, float delayPerUnit, unsigned int loops);

    virtual CCObject* copyWithZone(CCZone* pZone);

    /** total Delay units of the CCAnimation. */
    // 动画的总延时单元
    CC_SYNTHESIZE_READONLY(float, m_fTotalDelayUnits, TotalDelayUnits)

    /** Delay in seconds of the "delay unit" */
    // 延时单元时间
    CC_SYNTHESIZE(float, m_fDelayPerUnit, DelayPerUnit)

    /** duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit */
    // 间隔，为整个动画过程
    CC_PROPERTY_READONLY(float, m_fDuration, Duration)

    /** array of CCAnimationFrames */
    // 动画帧数组
    CC_SYNTHESIZE_RETAIN(CCArray*, m_pFrames, Frames)

    /** whether or not it shall restore the original frame when the animation finishes */
    // 当动画完成后是否恢复原帧
    CC_SYNTHESIZE(bool, m_bRestoreOriginalFrame, RestoreOriginalFrame)

    /** how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... */
    // 动画循环多少次。 0为没有动画，1为执行了1次
    CC_SYNTHESIZE(unsigned int, m_uLoops, Loops)
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_ANIMATION_H__
