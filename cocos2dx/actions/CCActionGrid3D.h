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
#ifndef __ACTION_CCGRID3D_ACTION_H__
#define __ACTION_CCGRID3D_ACTION_H__

#include "CCActionGrid.h"

NS_CC_BEGIN

/**
 * @addtogroup actions  动作
 * @{
 */

/** 
@brief CCWaves3D action 
*/
// 3D波动作
class CC_DLL CCWaves3D : public CCGrid3DAction
{
public:
    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes an action with duration, grid size, waves and amplitude */
    // 初始化动作，使用间隔，大小，波，幅度参数
    bool initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude);

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates an action with duration, grid size, waves and amplitude */
    // 创建一个动作，间隔，大小，波，幅度
    static CCWaves3D* create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude);
protected:
    unsigned int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;
};

/** @brief CCFlipX3D action */
// x轴翻动动作
class CC_DLL CCFlipX3D : public CCGrid3DAction
{
public:
    /** initializes the action with duration */
    // 用间隔初始化动作
    virtual bool initWithDuration(float duration);
    virtual bool initWithSize(const CCSize& gridSize, float duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates the action with duration */
    // 使用间隔初始化动作
    static CCFlipX3D* create(float duration);
};

/** @brief CCFlipY3D action */
// y轴翻动
class CC_DLL CCFlipY3D : public CCFlipX3D
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action with duration */
    // 使用间隔创建动作
    static CCFlipY3D* create(float duration);
};

/** @brief CCLens3D action */
// 3D镜像动作
class CC_DLL CCLens3D : public CCGrid3DAction
{
public:
    /** Get lens center position */
    // 获取镜像中心位置
    inline float getLensEffect(void) { return m_fLensEffect; }
    /** Set lens center position */
    // 设置镜像位置
    inline void setLensEffect(float fLensEffect) { m_fLensEffect = fLensEffect; }
    /** Set whether lens is concave */
    // 设置镜像为凸
    inline void setConcave(bool bConcave) { m_bConcave = bConcave; }
  
    inline const CCPoint& getPosition(void) { return m_position; }
    void setPosition(const CCPoint& position);

    /** initializes the action with center position, radius, a grid size and duration */
    // 使用中心位置，半径，大小和间隔初始化动作
    bool initWithDuration(float duration, const CCSize& gridSize, const CCPoint& position, float radius);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates the action with center position, radius, a grid size and duration */
    // 创建一个动作，使用位置，半径，大小，间隔
    static CCLens3D* create(float duration, const CCSize& gridSize, const CCPoint& position, float radius);
protected:
    /* lens center position */
    // 镜像中心位置
    CCPoint m_position;
    float m_fRadius;
    /** lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect */
    // 镜像效果；默认为0.7；0没有效果，1为强烈效果
    float m_fLensEffect;
    /** lens is concave. (true = concave, false = convex) default is convex i.e. false */
    // 镜像是凸
    bool m_bConcave;

    bool    m_bDirty;
};

/** @brief CCRipple3D action */
// 波纹动作
class CC_DLL CCRipple3D : public CCGrid3DAction
{
public:
    /** get center position */
    // 获取中心位置
    inline const CCPoint& getPosition(void) { return m_position; }
    /** set center position */
    // 设置中心位置
    void setPosition(const CCPoint& position);

    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with radius, number of waves, amplitude, a grid size and duration */
    // 初始化动作，使用半径，波数量，幅度，大小，间隔
    bool initWithDuration(float duration, const CCSize& gridSize, const CCPoint& position, float radius, unsigned int waves, float amplitude);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates the action with radius, number of waves, amplitude, a grid size and duration */
    // 创建一个动作，使用半径，波个数，幅度，大小，间隔参数
    static CCRipple3D* create(float duration, const CCSize& gridSize, const CCPoint& position, float radius, unsigned int waves, float amplitude);
protected:
    /* center position */
    // 中心位置
    CCPoint m_position;
    float m_fRadius;
    unsigned int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;
};

/** @brief CCShaky3D action */
// 摇动
class CC_DLL CCShaky3D : public CCGrid3DAction
{
public:
    /** initializes the action with a range, shake Z vertices, a grid and duration */
    // 初始化动作，使用范围，z顶点，大小，间隔
    bool initWithDuration(float duration, const CCSize& gridSize, int range, bool shakeZ);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates the action with a range, shake Z vertices, a grid and duration */
    // 创建动作，使用范围，z顶点，网格大小，间隔
    static CCShaky3D* create(float duration, const CCSize& gridSize, int range, bool shakeZ);
protected:
    int m_nRandrange;
    bool m_bShakeZ;
};

/** @brief CCLiquid action */
// 液体动作
class CC_DLL CCLiquid : public CCGrid3DAction
{
public:
    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with amplitude, a grid and duration */
    // 初始化动作使用幅度，网格大小，间隔参数
    bool initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates the action with amplitude, a grid and duration */
    // 创建动作，使用幅度，网格，间隔作为参数
    static CCLiquid* create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude);
protected:
    unsigned int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;
};

/** @brief CCWaves action */
// 波动作
class CC_DLL CCWaves : public CCGrid3DAction
{
public:
    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
    // 初始化动作，使用幅度，水平和垂直sin，大小和间隔
    bool initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:

    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
    // 初始化动作，使用幅度，水平和垂直sin，大小和间隔
    static CCWaves* create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);
protected:
    unsigned int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;
    bool m_bVertical;
    bool m_bHorizontal;
};

/** @brief CCTwirl action */
// 捏动作
class CC_DLL CCTwirl : public CCGrid3DAction
{
public:
    /** get twirl center */
    // 获取捏的中心位置
    inline const CCPoint& getPosition(void) { return m_position; }
    /** set twirl center */
    // 设置捏的中心位置
    void setPosition(const CCPoint& position);

    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with center position, number of twirls, amplitude, a grid size and duration */
    // 初始化捏动作，使用中心位置，捏的数目，幅度，网格大小，间隔参数
    bool initWithDuration(float duration, const CCSize& gridSize, CCPoint position, unsigned int twirls, float amplitude);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates the action with center position, number of twirls, amplitude, a grid size and duration */
    // 创建捏动作，使用中心位置，捏的数目，幅度，网格大小，间隔参数
    static CCTwirl* create(float duration, const CCSize& gridSize, CCPoint position, unsigned int twirls, float amplitude);
protected:
    /* twirl center */
    // 捏的中心位置
    CCPoint m_position;
    unsigned int m_nTwirls;
    float m_fAmplitude;
    float m_fAmplitudeRate;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID3D_ACTION_H__
