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

#ifndef __CCTRANSITION_H__
#define __CCTRANSITION_H__

#include "CCScene.h"
#include "ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup transition	过渡
 * @{
 */

//static creation function macro
//c/c++ don't support object creation of using class name
//so, all classes need creation method.
// 静态函数宏，所有类需要创建方法；c/c++不支持使用类名创建对象
class CCActionInterval;
class CCNode;

/** @brief CCTransitionEaseScene can ease the actions of the scene protocol.
@since v0.8.2
*/
// 缓解动作
class CC_DLL CCTransitionEaseScene// : public CCObject
{
public:
    /** returns the Ease action that will be performed on a linear action.
    @since v0.8.2
    */
    // 返回缓解动作
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action) = 0;
};

/** Orientation Type used by some transitions
*/
// 过渡使用的方向类型
typedef enum {
    	/// An horizontal orientation where the Left is nearer
    	/// 水平方向的左边
	kCCTransitionOrientationLeftOver = 0,
	/// An horizontal orientation where the Right is nearer
	/// 水平方向的右边
	kCCTransitionOrientationRightOver = 1,
	/// A vertical orientation where the Up is nearer
	/// 垂直方向的上方
	kCCTransitionOrientationUpOver = 0,
	/// A vertical orientation where the Bottom is nearer
	/// 垂直方向的底部
	kCCTransitionOrientationDownOver = 1,
    
	// Deprecated	弃用
    //	kOrientationLeftOver = kCCTransitionOrientationLeftOver,
    //	kOrientationRightOver = kCCTransitionOrientationRightOver,
    //	kOrientationUpOver = kCCTransitionOrientationUpOver,
    //	kOrientationDownOver = kCCTransitionOrientationDownOver,
} tOrientation;

/** @brief Base class for CCTransition scenes
*/
// 过渡场景
class CC_DLL CCTransitionScene : public CCScene
{

protected:
    CCScene    * m_pInScene;
    CCScene    * m_pOutScene;
    float    m_fDuration;
    bool    m_bIsInSceneOnTop;
    bool    m_bIsSendCleanupToScene;

public:

    CCTransitionScene();
    virtual ~CCTransitionScene();
    virtual void draw();
    virtual void onEnter();
    virtual void onExit();
    virtual void cleanup();

    /** creates a base transition with duration and incoming scene */
    // 创建一个过渡，使用间隔，和输入场景为参数
    static CCTransitionScene * create(float t, CCScene *scene);

    /** initializes a transition with duration and incoming scene */
    // 初始化一个过渡，使用间隔，和输入场景为参数
    virtual bool initWithDuration(float t,CCScene* scene);

    /** called after the transition finishes */
    // 过渡完成时调用
    void finish(void);

    /** used by some transitions to hide the outer scene */
    // 一些过渡隐藏外部创建使用
    void hideOutShowIn(void);

protected:
    virtual void sceneOrder();
private:
    void setNewScene(float dt);

};

/** @brief A CCTransition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
// 过渡支持的方向：可能的方向为左右，上下
class CC_DLL CCTransitionSceneOriented : public CCTransitionScene
{
protected:
    tOrientation m_eOrientation;

public:
    CCTransitionSceneOriented();
    virtual ~CCTransitionSceneOriented();

    /** creates a base transition with duration and incoming scene */
    // 创建一个过渡，使用间隔和输入场景为惨
    static CCTransitionSceneOriented * create(float t,CCScene* scene, tOrientation orientation);

    /** initializes a transition with duration and incoming scene */
    // 初始化一个过渡，使用间隔，输入场景为参数
    virtual bool initWithDuration(float t,CCScene* scene,tOrientation orientation);
};

/** @brief CCTransitionRotoZoom:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
// 缩放过渡
class CC_DLL CCTransitionRotoZoom : public CCTransitionScene
{
public:
    CCTransitionRotoZoom();
    virtual ~CCTransitionRotoZoom();
    virtual void onEnter();

    static CCTransitionRotoZoom* create(float t, CCScene* scene);
};

/** @brief CCTransitionJumpZoom:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
// 跳跃
class CC_DLL CCTransitionJumpZoom : public CCTransitionScene
{
public:
    CCTransitionJumpZoom();
    virtual ~CCTransitionJumpZoom();
    virtual void onEnter();

    static CCTransitionJumpZoom* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInL:
Move in from to the left the incoming scene.
*/
// 从左方移动过渡
class CC_DLL CCTransitionMoveInL : public CCTransitionScene, public CCTransitionEaseScene
{
public:
    CCTransitionMoveInL();
    virtual ~CCTransitionMoveInL();
    /** initializes the scenes */
    // 初始化场景
    virtual void initScenes(void);
    /** returns the action that will be performed */
    // 返回间隔动作
    virtual CCActionInterval* action(void);

    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    virtual void onEnter();

    static CCTransitionMoveInL* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInR:
Move in from to the right the incoming scene.
*/
// 从右方移动过渡
class CC_DLL CCTransitionMoveInR : public CCTransitionMoveInL
{
public:
    CCTransitionMoveInR();
    virtual ~CCTransitionMoveInR();
    virtual void initScenes();

    static CCTransitionMoveInR* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInT:
Move in from to the top the incoming scene.
*/
// 从上方移动过渡
class CC_DLL CCTransitionMoveInT : public CCTransitionMoveInL 
{
public:
    CCTransitionMoveInT();
    virtual ~CCTransitionMoveInT();
    virtual void initScenes();

    static CCTransitionMoveInT* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInB:
Move in from to the bottom the incoming scene.
*/
// 从底部移动过渡
class CC_DLL CCTransitionMoveInB : public CCTransitionMoveInL
{
public:
    CCTransitionMoveInB();
    virtual ~CCTransitionMoveInB();
    virtual void initScenes();

    static CCTransitionMoveInB* create(float t, CCScene* scene);
};

/** @brief CCTransitionSlideInL:
Slide in the incoming scene from the left border.
*/
// 从左方滑动过渡
class CC_DLL CCTransitionSlideInL : public CCTransitionScene, public CCTransitionEaseScene
{
public:
    CCTransitionSlideInL();
    virtual ~CCTransitionSlideInL();

    /** initializes the scenes */
    // 初始化场景
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    // 返回间隔动作
    virtual CCActionInterval* action(void);

    virtual void onEnter();
    
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static CCTransitionSlideInL* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInR:
Slide in the incoming scene from the right border.
*/
// 从右方滑动过渡
class CC_DLL CCTransitionSlideInR : public CCTransitionSlideInL 
{
public:
    CCTransitionSlideInR();
    virtual ~CCTransitionSlideInR();

    /** initializes the scenes */
    // 初始化场景
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    // 返回间隔动作
    virtual CCActionInterval* action(void);

    static CCTransitionSlideInR* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInB:
Slide in the incoming scene from the bottom border.
*/
// 从底部滑动过渡
class CC_DLL CCTransitionSlideInB : public CCTransitionSlideInL
{
public:
    CCTransitionSlideInB();
    virtual ~CCTransitionSlideInB();

    /** initializes the scenes */
    // 初始化场景
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    // 返回间隔动作
    virtual CCActionInterval* action(void);

    static CCTransitionSlideInB* create(float t, CCScene* scene);
protected: 
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInT:
Slide in the incoming scene from the top border.
*/
// 从上方滑动过渡
class CC_DLL CCTransitionSlideInT : public CCTransitionSlideInL
{
public:
    CCTransitionSlideInT();
    virtual ~CCTransitionSlideInT();

    /** initializes the scenes */
    // 初始化场景
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    // 返回间隔动作
    virtual CCActionInterval* action(void);

    static CCTransitionSlideInT* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/**
@brief Shrink the outgoing scene while grow the incoming scene
*/
// 收缩外部，增长内部过渡
class CC_DLL CCTransitionShrinkGrow : public CCTransitionScene , public CCTransitionEaseScene
{
public:
    CCTransitionShrinkGrow();
    virtual ~CCTransitionShrinkGrow();

    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static CCTransitionShrinkGrow* create(float t, CCScene* scene);
};

/** @brief CCTransitionFlipX:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
// x轴翻滚过渡
class CC_DLL CCTransitionFlipX : public CCTransitionSceneOriented
{
public:
    CCTransitionFlipX();
    virtual ~CCTransitionFlipX();

    virtual void onEnter();

    static CCTransitionFlipX* create(float t, CCScene* s, tOrientation o);
    static CCTransitionFlipX* create(float t, CCScene* s);
};

/** @brief CCTransitionFlipY:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
// y轴翻动过渡
class CC_DLL CCTransitionFlipY : public CCTransitionSceneOriented
{
public:
    CCTransitionFlipY();
    virtual ~CCTransitionFlipY();

    virtual void onEnter();

    static CCTransitionFlipY* create(float t, CCScene* s, tOrientation o);
    static CCTransitionFlipY* create(float t, CCScene* s);
};

/** @brief CCTransitionFlipAngular:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
// 角度翻动过渡
class CC_DLL CCTransitionFlipAngular : public CCTransitionSceneOriented
{
public:
    CCTransitionFlipAngular();
    virtual ~CCTransitionFlipAngular();

    virtual void onEnter();
    
    static CCTransitionFlipAngular* create(float t, CCScene* s, tOrientation o);
    static CCTransitionFlipAngular* create(float t, CCScene* s);
};

/** @brief CCTransitionZoomFlipX:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
// 翻动x轴加放大过渡
class CC_DLL CCTransitionZoomFlipX : public CCTransitionSceneOriented
{
public:
    CCTransitionZoomFlipX();
    virtual ~CCTransitionZoomFlipX();

    virtual void onEnter();

    static CCTransitionZoomFlipX* create(float t, CCScene* s, tOrientation o);
    static CCTransitionZoomFlipX* create(float t, CCScene* s);
};

/** @brief CCTransitionZoomFlipY:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
// 翻动y轴加放大过渡
class CC_DLL CCTransitionZoomFlipY : public CCTransitionSceneOriented
{
public:
    CCTransitionZoomFlipY();
    virtual ~CCTransitionZoomFlipY();

    virtual void onEnter();

    static CCTransitionZoomFlipY* create(float t, CCScene* s, tOrientation o);
    static CCTransitionZoomFlipY* create(float t, CCScene* s);
};

/** @brief CCTransitionZoomFlipAngular:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
// 翻动角度加放大过渡
class CC_DLL CCTransitionZoomFlipAngular : public CCTransitionSceneOriented
{
public:
    CCTransitionZoomFlipAngular();
    virtual ~CCTransitionZoomFlipAngular();

    virtual void onEnter();

    static CCTransitionZoomFlipAngular* create(float t, CCScene* s, tOrientation o);
    static CCTransitionZoomFlipAngular* create(float t, CCScene* s);
};

/** @brief CCTransitionFade:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
// 淡入淡出过渡
class CC_DLL CCTransitionFade : public CCTransitionScene
{
protected:
    ccColor4B    m_tColor;

public:

    CCTransitionFade();
    virtual ~CCTransitionFade();
    
    /** creates the transition with a duration and with an RGB color
    * Example: FadeTransition::create(2, scene, ccc3(255,0,0); // red color
    */
    // 创建一个过渡，使用间隔，颜色为参数
    static CCTransitionFade* create(float duration,CCScene* scene, const ccColor3B& color);
    static CCTransitionFade* create(float duration,CCScene* scene);

    /** initializes the transition with a duration and with an RGB color */
    // 初始化过渡，使用间隔，颜色为参数
    virtual bool initWithDuration(float t, CCScene*scene ,const ccColor3B& color);

    virtual bool initWithDuration(float t,CCScene* scene); 
    virtual void onEnter();
    virtual void onExit();
};

class CCRenderTexture;
/**
@brief CCTransitionCrossFade:
Cross fades two scenes using the CCRenderTexture object.
*/
// 交叉淡出过渡
class CC_DLL CCTransitionCrossFade : public CCTransitionScene
{
public :
    CCTransitionCrossFade();
    virtual ~CCTransitionCrossFade();

    virtual void draw();
    virtual void onEnter();
    virtual void onExit();

public:
    static CCTransitionCrossFade* create(float t, CCScene* scene);
};

/** @brief CCTransitionTurnOffTiles:
Turn off the tiles of the outgoing scene in random order
*/
// 瓦片过渡
class CC_DLL CCTransitionTurnOffTiles : public CCTransitionScene ,public CCTransitionEaseScene
{
public :
    CCTransitionTurnOffTiles();
    virtual ~CCTransitionTurnOffTiles();

    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    static CCTransitionTurnOffTiles* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSplitCols:
The odd columns goes upwards while the even columns goes downwards.
*/
// 拆分列过渡
class CC_DLL CCTransitionSplitCols : public CCTransitionScene , public CCTransitionEaseScene
{
public:
    CCTransitionSplitCols();
    virtual ~CCTransitionSplitCols();

    virtual CCActionInterval* action(void);
    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:

    static CCTransitionSplitCols* create(float t, CCScene* scene);
};

/** @brief CCTransitionSplitRows:
The odd rows goes to the left while the even rows goes to the right.
*/
// 拆分行过渡
class CC_DLL CCTransitionSplitRows : public CCTransitionSplitCols
{
public:
    CCTransitionSplitRows();
    virtual ~CCTransitionSplitRows();

    virtual CCActionInterval* action(void);

public:

    static CCTransitionSplitRows* create(float t, CCScene* scene);
};

/** @brief CCTransitionFadeTR:
 * Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
// 从左下角淡出过渡
class CC_DLL CCTransitionFadeTR : public CCTransitionScene , public CCTransitionEaseScene
{
public:
    CCTransitionFadeTR();
    virtual ~CCTransitionFadeTR();
    virtual CCActionInterval* actionWithSize(const CCSize& size);
    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

public:

    static CCTransitionFadeTR* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionFadeBL:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
// 从右下角淡出过渡
class CC_DLL CCTransitionFadeBL : public CCTransitionFadeTR
{
public:
    CCTransitionFadeBL();
    virtual ~CCTransitionFadeBL();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCTransitionFadeBL* create(float t, CCScene* scene);
};

/** @brief CCTransitionFadeUp:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
// 从上方淡出过渡
class CC_DLL CCTransitionFadeUp : public CCTransitionFadeTR
{
public:
    CCTransitionFadeUp();
    virtual ~CCTransitionFadeUp();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCTransitionFadeUp* create(float t, CCScene* scene);
};

/** @brief CCTransitionFadeDown:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
// 从下方淡出过渡
class CC_DLL CCTransitionFadeDown : public CCTransitionFadeTR
{
public:
    CCTransitionFadeDown();
    virtual ~CCTransitionFadeDown();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCTransitionFadeDown* create(float t, CCScene* scene);
};

// end of transition group
/// @}

NS_CC_END

#endif // __CCTRANSITION_H__

