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

/*
 *
 * IMPORTANT       IMPORTANT        IMPORTANT        IMPORTANT
 *
 *
 * LEGACY FUNCTIONS     通用功能，使用CCDrawNode
 *
 * USE CCDrawNode instead
 *
 */


#ifndef __CCDRAWING_PRIMITIVES__
#define __CCDRAWING_PRIMITIVES__
    

#include "ccTypes.h"
#include "ccMacros.h"
#include "cocoa/CCGeometry.h"    // for CCPoint

/**
 @file
 Drawing OpenGL ES primitives.
 - ccDrawPoint, ccDrawPoints
 - ccDrawLine
 - ccDrawRect, ccDrawSolidRect
 - ccDrawPoly, ccDrawSolidPoly
 - ccDrawCircle
 - ccDrawQuadBezier
 - ccDrawCubicBezier
 - ccDrawCatmullRom
 - ccDrawCardinalSpline
 
 You can change the color, point size, width by calling:
 - ccDrawColor4B(), ccDrawColor4F()
 - ccPointSize()
 - glLineWidth()
 
 @warning These functions draws the Line, Point, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch. Instead you should use CCDrawNode
 
 */
/*
 绘制opengl es基本单元，可以在下面的函数用到：
  - ccDrawPoint, ccDrawPoints
 - ccDrawLine
 - ccDrawRect, ccDrawSolidRect
 - ccDrawPoly, ccDrawSolidPoly
 - ccDrawCircle
 - ccDrawQuadBezier
 - ccDrawCubicBezier
 - ccDrawCatmullRom
 - ccDrawCardinalSpline
 
 可以改变颜色，大小，线宽度，通过调用
 - ccDrawColor4B(), ccDrawColor4F()
 - ccPointSize()
 - glLineWidth()
 注意方法绘制点，线段，多边形立即执行的；不是批量的；游戏中通常使用批量绘制
 */

NS_CC_BEGIN

/**
 * @addtogroup global       属于全局
 * @{
 */

class CCPointArray;

/** Initializes the drawing primitives */
// 初始化绘制单元
void CC_DLL ccDrawInit();

/** Frees allocated resources by the drawing primitives */
// 释放资源
void CC_DLL ccDrawFree();

/** draws a point given x and y coordinate measured in points */
// 给定x,y坐标点，绘制点
void CC_DLL ccDrawPoint( const CCPoint& point );

/** draws an array of points.
 @since v0.7.2
 */
// 绘制点数组
void CC_DLL ccDrawPoints( const CCPoint *points, unsigned int numberOfPoints );

/** draws a line given the origin and destination point measured in points */
// 绘制线，给定原点，目标点参数
void CC_DLL ccDrawLine( const CCPoint& origin, const CCPoint& destination );

/** draws a rectangle given the origin and destination point measured in points. */
// 绘制一个矩形，使用原点，目标点为参数
void CC_DLL ccDrawRect( CCPoint origin, CCPoint destination );

/** draws a solid rectangle given the origin and destination point measured in points.
    @since 1.1
 */
// 绘制实体矩形，使用原点，目标点，颜色为参数
void CC_DLL ccDrawSolidRect( CCPoint origin, CCPoint destination, ccColor4F color );

/** draws a polygon given a pointer to CCPoint coordinates and the number of vertices measured in points.
The polygon can be closed or open
*/
// 绘制多边形，使用点，点个数，是否为封闭多边形为参数
void CC_DLL ccDrawPoly( const CCPoint *vertices, unsigned int numOfVertices, bool closePolygon );

/** draws a solid polygon given a pointer to CGPoint coordinates, the number of vertices measured in points, and a color.
 */
// 绘制实体多边形，使用点，点个数，颜色值为参数
void CC_DLL ccDrawSolidPoly( const CCPoint *poli, unsigned int numberOfPoints, ccColor4F color );

/** draws a circle given the center, radius and number of segments. */
// 绘制一个圆，使用点，半径，点位置为参数
void CC_DLL ccDrawCircle( const CCPoint& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
void CC_DLL ccDrawCircle( const CCPoint& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);

/** draws a quad bezier path
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v0.8
 */
// 绘制贝塞尔曲线，注意运行慢，用于调试
void CC_DLL ccDrawQuadBezier(const CCPoint& origin, const CCPoint& control, const CCPoint& destination, unsigned int segments);

/** draws a cubic bezier path
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v0.8
 */
// 绘制一个贝塞尔立方路径，注意该方法运行慢，使用它用于调试
void CC_DLL ccDrawCubicBezier(const CCPoint& origin, const CCPoint& control1, const CCPoint& control2, const CCPoint& destination, unsigned int segments);

/** draws a Catmull Rom path.
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v2.0
 */
// 绘制卡特莫尔罗路径，注意该方法用于调试
void CC_DLL ccDrawCatmullRom( CCPointArray *arrayOfControlPoints, unsigned int segments );

/** draws a Cardinal Spline path.
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v2.0
 */
// 绘制基数样条路径 用于调试
void CC_DLL ccDrawCardinalSpline( CCPointArray *config, float tension,  unsigned int segments );

/** set the drawing color with 4 unsigned bytes
 @since v2.0
 */
// 设置绘制颜色值，用4字节
void CC_DLL ccDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a );

/** set the drawing color with 4 floats
 @since v2.0
 */
// 设置绘制颜色用4个浮点数
void CC_DLL ccDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a );

/** set the point size in points. Default 1.
 @since v2.0
 */
// 设置点大小，以点为单位；默认为1
void CC_DLL ccPointSize( GLfloat pointSize );

// end of global group
/// @}

NS_CC_END

#endif // __CCDRAWING_PRIMITIVES__
