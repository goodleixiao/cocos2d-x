/*
 * Copyright (c) 2012 cocos2d-x.org
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008 Radu Gruian
 *
 * Copyright (c) 2011 Vit Valentin
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Original code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So
 *
 * Adapted to cocos2d-x by Vit Valentin
 *
 * Adapted from cocos2d-x to cocos2d-iphone by Ricardo Quesada
 */


#ifndef __CCACTION_CATMULLROM_H__
#define __CCACTION_CATMULLROM_H__

#include <vector>

#include "CCActionInterval.h"
#include "base_nodes/CCNode.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN;

/**
 * @addtogroup actions  动作
 * @{
 */

/** An Array that contain control points.
 Used by CCCardinalSplineTo and (By) and CCCatmullRomTo (and By) actions.
@ingroup Actions
 */
// 数组控制点，被CCCardinalSplineTo或CCCatmullRomTo使用
class CC_DLL CCPointArray : public CCObject
{
public:
    
    /** creates and initializes a Points array with capacity */
    // 创建一定容量的点
    static CCPointArray* create(unsigned int capacity);

    virtual ~CCPointArray();
    CCPointArray();
    
    /** initializes a Catmull Rom config with a capacity hint */
    // 使用容量参数初始化
    bool initWithCapacity(unsigned int capacity);
    
    /** appends a control point */
    // 增加一个控制点
    void addControlPoint(CCPoint controlPoint);
    
    /** inserts a controlPoint at index */
    // 在指定位置插入一个控制点
    void insertControlPoint(CCPoint &controlPoint, unsigned int index);
    
    /** replaces an existing controlPoint at index */
    // 取代指定位置的控制点
    void replaceControlPoint(CCPoint &controlPoint, unsigned int index);
    
    /** get the value of a controlPoint at a given index */
    // 获取给定序号的点
    CCPoint getControlPointAtIndex(unsigned int index);
    
    /** deletes a control point at a given index */
    // 删除给定序号的控制点
    void removeControlPointAtIndex(unsigned int index);
    
    /** returns the number of objects of the control point array */
    // 返回控制点数组的个数
    unsigned int count();
    
    /** returns a new copy of the array reversed. User is responsible for releasing this copy */
    // 控制点反向
    CCPointArray* reverse();
    
    /** reverse the current control point array inline, without generating a new one */
    // 内联反向，不产生新的数组
    void reverseInline();
    
    virtual CCObject* copyWithZone(CCZone *zone);
    
    const std::vector<CCPoint*>* getControlPoints();

    void setControlPoints(std::vector<CCPoint*> *controlPoints);
private:
    /** Array that contains the control points */
    // 向量数组控制点
    std::vector<CCPoint*> *m_pControlPoints;
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
@ingroup Actions
 */
// 样条路径
class CC_DLL CCCardinalSplineTo : public CCActionInterval
{
public:

    /** creates an action with a Cardinal Spline array of points and tension */
    // 创建一个路径动作使用控制点
    static CCCardinalSplineTo* create(float duration, CCPointArray* points, float tension);

    virtual ~CCCardinalSplineTo();
    CCCardinalSplineTo();
    
    /** initializes the action with a duration and an array of points */
    // 初始化动作，参数：时间间隔，数组点，张力
    bool initWithDuration(float duration, CCPointArray* points, float tension);
    
    // super virtual functions
    // 虚函数
    virtual CCCardinalSplineTo* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse();
    
    virtual void updatePosition(CCPoint &newPos);
    
    inline CCPointArray* getPoints() { return m_pPoints; }
    inline void  setPoints(CCPointArray* points) 
    {
        CC_SAFE_RETAIN(points);
        CC_SAFE_RELEASE(m_pPoints);
        m_pPoints = points;
    }
    
protected:
    /** Array of control points */
    // 控制点数组
    CCPointArray *m_pPoints;
    float m_fDeltaT;
    float m_fTension;
    CCPoint	m_previousPosition;
    CCPoint	m_accumulatedDiff;
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 @ingroup Actions
 */
// 样条路径by
class CC_DLL CCCardinalSplineBy : public CCCardinalSplineTo 
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension */
    // 创建路径动作，使用间隔，数组，张力
    static CCCardinalSplineBy* create(float duration, CCPointArray* points, float tension);

    CCCardinalSplineBy();
    
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse();
    virtual void updatePosition(CCPoint &newPos);
protected:
    CCPoint m_startPosition;
};

/** An action that moves the target with a CatmullRom curve to a destination point.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
// CatmullRom曲线动作
class CC_DLL CCCatmullRomTo : public CCCardinalSplineTo
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension */
    // 创建CatmullRom曲线动作，使用数组和张力
    static CCCatmullRomTo* create(float dt, CCPointArray* points);

    /** initializes the action with a duration and an array of points */
    // 初始化CatmullRom曲线动作
    bool initWithDuration(float dt, CCPointArray* points);
};

/** An action that moves the target with a CatmullRom curve by a certain distance.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
// CatmullRom曲线，有指定距离
class CC_DLL CCCatmullRomBy : public CCCardinalSplineBy
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension */
    // 创建CatmullRom曲线动作
    static CCCatmullRomBy* create(float dt, CCPointArray* points);

    /** initializes the action with a duration and an array of points */
    // 初始化CatmullRom曲线动作，使用控制点数组和张力值
    bool initWithDuration(float dt, CCPointArray* points);
};

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
// 返回控制点位置，给定控制点和张力和间隔
extern CC_DLL CCPoint ccCardinalSplineAt(CCPoint &p0, CCPoint &p1, CCPoint &p2, CCPoint &p3, float tension, float t);

// end of actions group
/// @}

NS_CC_END;

#endif // __CCACTION_CATMULLROM_H__
