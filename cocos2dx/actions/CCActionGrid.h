/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      On-Core

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
#ifndef __ACTION_CCGRID_ACTION_H__
#define __ACTION_CCGRID_ACTION_H__

#include "CCActionInterval.h"
#include "CCActionInstant.h"

NS_CC_BEGIN

class CCGridBase;

/**
 * @addtogroup actions      动作
 * @{
 */

/** @brief Base class for Grid actions */
// 网格动作
class CC_DLL CCGridAction : public CCActionInterval
{
public:
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);

    /** initializes the action with size and duration */
    // 使用大小和间隔初始化
    virtual bool initWithDuration(float duration, const CCSize& gridSize);

    /** returns the grid */
    // 返回网格
    virtual CCGridBase* getGrid(void);

public:
    /** creates the action with size and duration */
    // We can't make this create function compatible with previous version, cxx-generator will be confused since they
    // have the same function name and the same number of arguments. So sorry about that.
    //CC_DEPRECATED_ATTRIBUTE static CCGridAction* create(const CCSize& gridSize, float duration);

    /** creates the action with size and duration */
    // 创建一个动作，使用大小和间隔；以前版本没有此方法
    static CCGridAction* create(float duration, const CCSize& gridSize);
protected:
    CCSize m_sGridSize;
};

/** 
 @brief Base class for CCGrid3D actions.
 Grid3D actions can modify a non-tiled grid.
 */
// 3D网格动作，可以修改网格
class CC_DLL CCGrid3DAction : public CCGridAction
{
public:
    /** returns the grid */
    // 返回网格
    virtual CCGridBase* getGrid(void);
    /** returns the vertex than belongs to certain position in the grid */
    // 返回网格顶点
    ccVertex3F vertex(const CCPoint& position);
    /** returns the non-transformed vertex than belongs to certain position in the grid */
    // 返回非转化顶点，
    ccVertex3F originalVertex(const CCPoint& position);
    /** sets a new vertex to a certain position of the grid */
    // 设置一个新的顶点
    void setVertex(const CCPoint& position, const ccVertex3F& vertex);

public:
    /** creates the action with size and duration */
    // 创建一个动作用大小和间隔
    static CCGrid3DAction* create(float duration, const CCSize& gridSize);
};

/** @brief Base class for CCTiledGrid3D actions */
// 动作
class CC_DLL CCTiledGrid3DAction : public CCGridAction
{
public:
    /** returns the tile that belongs to a certain position of the grid */
    // 返回瓦片，属于网格指定位置
    ccQuad3 tile(const CCPoint& position);
    /** returns the non-transformed tile that belongs to a certain position of the grid */
    // 返回非转化瓦片
    ccQuad3 originalTile(const CCPoint& position);
    /** sets a new tile to a certain position of the grid */
    // 设置新的瓦片，在指定位置
    void setTile(const CCPoint& position, const ccQuad3& coords);

    /** returns the grid */
    // 返回网格
    virtual CCGridBase* getGrid(void);

public:
    /** creates the action with size and duration */
    // 创建动作，使用大小和间隔
    static CCTiledGrid3DAction* create(float duration, const CCSize& gridSize);
};

/** @brief CCAccelDeccelAmplitude action */
// 幅度 动作
class CC_DLL CCAccelDeccelAmplitude : public CCActionInterval
{
public:
    virtual ~CCAccelDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    // 初始化动作使用幅度属性和间隔
    bool initWithAction(CCAction *pAction, float duration);

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

    /** get amplitude rate */
    // 获取幅度比率
    inline float getRate(void) { return m_fRate; }
    /** set amplitude rate */
    // 设置幅度比率
    inline void setRate(float fRate) { m_fRate = fRate; }

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    // 初始化动作使用幅度属性和间隔
    static CCAccelDeccelAmplitude* create(CCAction *pAction, float duration);

protected:
    float m_fRate;
    CCActionInterval *m_pOther;
};

/** @brief CCAccelAmplitude action */
// 加速幅度动作
class CC_DLL CCAccelAmplitude : public CCActionInterval
{
public:
    ~CCAccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    // 初始化动作使用幅度属性和间隔
    bool initWithAction(CCAction *pAction, float duration);

    /** get amplitude rate */
    // 获取幅度比率
    inline float getRate(void) { return m_fRate; }
    /** set amplitude rate */
    // 设置幅度
    inline void setRate(float fRate) { m_fRate = fRate; }

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    // 初始化动作使用幅度属性和间隔
    static CCAccelAmplitude* create(CCAction *pAction, float duration);
protected:
    float m_fRate;
    CCActionInterval *m_pOther;
};

/** @brief CCDeccelAmplitude action */
// 减速幅度
class CC_DLL CCDeccelAmplitude : public CCActionInterval
{
public:
    ~CCDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    // 初始化动作使用幅度属性和间隔
    bool initWithAction(CCAction *pAction, float duration);

    /** get amplitude rate */
    // 获取幅度比率
    inline float getRate(void) { return m_fRate; }
    /** set amplitude rate */
    // 设置幅度比率
    inline void setRate(float fRate) { m_fRate = fRate; }

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    // 创建动作使用幅度属性和间隔
    static CCDeccelAmplitude* create(CCAction *pAction, float duration);

protected:
    float m_fRate;
    CCActionInterval *m_pOther;
};

/** @brief CCStopGrid action.
 @warning Don't call this action if another grid action is active.
 Call if you want to remove the the grid effect. Example:
 CCSequence::actions(Lens::action(...), CCStopGrid::action(...), NULL);
 */
// 停止网格动作，当网络激活状态不要调用动作。如果你想移除网格效果，调用；如
//  CCSequence::actions(Lens::action(...), CCStopGrid::action(...), NULL);
class CC_DLL CCStopGrid : public CCActionInstant
{
public:
    virtual void startWithTarget(CCNode *pTarget);

public:
    /** Allocates and initializes the action */
    // 分配和初始化动作
    static CCStopGrid* create(void);
};

/** @brief CCReuseGrid action */
// 重用动作网格
class CC_DLL CCReuseGrid : public CCActionInstant
{
public:
    /** initializes an action with the number of times that the current grid will be reused */
    // 初始化动作，重用次数
    bool initWithTimes(int times);

    virtual void startWithTarget(CCNode *pTarget);

public:
    /** creates an action with the number of times that the current grid will be reused */
    // 创建一个动作，使用重用次数
    static CCReuseGrid* create(int times);
protected:
    int m_nTimes;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID_ACTION_H__
