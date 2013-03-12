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

#ifndef __CCTYPES_H__
#define __CCTYPES_H__

#include "cocoa/CCGeometry.h"
#include "CCGL.h"

NS_CC_BEGIN

/** RGB color composed of bytes 3 bytes
@since v0.8
 */
/* RGB颜色有3字节组成
 */
typedef struct _ccColor3B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
} ccColor3B;

//! helper macro that creates an ccColor3B type
//! 宏创建ccColor3B类型
static inline ccColor3B
ccc3(const GLubyte r, const GLubyte g, const GLubyte b)
{
    ccColor3B c = {r, g, b};
    return c;
}
//ccColor3B predefined colors
//! White color (255,255,255)
//ccColor3B预定义颜色值
//! 白色
static const ccColor3B ccWHITE={255,255,255};
//! Yellow color (255,255,0)
//! 黄色
static const ccColor3B ccYELLOW={255,255,0};
//! Blue color (0,0,255)
//! 蓝色
static const ccColor3B ccBLUE={0,0,255};
//! Green Color (0,255,0)
//! 绿色
static const ccColor3B ccGREEN={0,255,0};
//! Red Color (255,0,0,)
//! 红色
static const ccColor3B ccRED={255,0,0};
//! Magenta Color (255,0,255)
//! 品红色
static const ccColor3B ccMAGENTA={255,0,255};
//! Black Color (0,0,0)
//! 黑色
static const ccColor3B ccBLACK={0,0,0};
//! Orange Color (255,127,0)
//! 橙黄色
static const ccColor3B ccORANGE={255,127,0};
//! Gray Color (166,166,166)
//! 灰色
static const ccColor3B ccGRAY={166,166,166};

/** RGBA color composed of 4 bytes
@since v0.8
*/
/* RGBA颜色有4字节构成
*/
typedef struct _ccColor4B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
} ccColor4B;
//! helper macro that creates an ccColor4B type
//! 使用宏创建ccColor4B类型
static inline ccColor4B
ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
{
    ccColor4B c = {r, g, b, o};
    return c;
}


/** RGBA color composed of 4 floats
@since v0.8
*/
/* RGBA颜色有4个浮点值构成
*/
typedef struct _ccColor4F {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
} ccColor4F;


/** Returns a ccColor4F from a ccColor3B. Alpha will be 1.
 @since v0.99.1
 */
/* 从一个ccColor3B类型返回一个ccColor4F类型颜色。阿尔法的值为1
*/
static inline ccColor4F ccc4FFromccc3B(ccColor3B c)
{
    ccColor4F c4 = {c.r/255.f, c.g/255.f, c.b/255.f, 1.f};
    return c4;
}

//! helper that creates a ccColor4f type
//! 宏创建一个ccColor4F类型的值
static inline ccColor4F 
ccc4f(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a)
{
    ccColor4F c4 = {r, g, b, a};
    return c4;
}

/** Returns a ccColor4F from a ccColor4B.
 @since v0.99.1
 */
//! 从ccColor4B类型转成ccColor4F类型
static inline ccColor4F ccc4FFromccc4B(ccColor4B c)
{
    ccColor4F c4 = {c.r/255.f, c.g/255.f, c.b/255.f, c.a/255.f};
    return c4;
}

static inline ccColor4B ccc4BFromccc4F(ccColor4F c)
{
    ccColor4B ret = {(GLubyte)(c.r*255), (GLubyte)(c.g*255), (GLubyte)(c.b*255), (GLubyte)(c.a*255)};
	return ret;
}

/** returns YES if both ccColor4F are equal. Otherwise it returns NO.
 @since v0.99.1
 */
//! 判断两个ccColor4F类型的值是否相等；相等返回YES,否则返回NO
static inline bool ccc4FEqual(ccColor4F a, ccColor4F b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
//! 由两个浮点值组成的顶点
typedef struct _ccVertex2F
{
    GLfloat x;
    GLfloat y;
} ccVertex2F;

static inline ccVertex2F vertex2(const float x, const float y)
{
    ccVertex2F c = {x, y};
    return c;
}


/** A vertex composed of 3 floats: x, y, z
 @since v0.8
 */
//! 三个浮点值组成的顶点
typedef struct _ccVertex3F
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} ccVertex3F;

static inline ccVertex3F vertex3(const float x, const float y, const float z)
{
    ccVertex3F c = {x, y, z};
    return c;
}
        
/** A texcoord composed of 2 floats: u, y
 @since v0.8
 */
//! 两个浮点值组成的纹理坐标
typedef struct _ccTex2F {
     GLfloat u;
     GLfloat v;
} ccTex2F;

static inline ccTex2F tex2(const float u, const float v)
{
    ccTex2F t = {u , v};
    return t;
}

 
//! Point Sprite component
//! 精灵组件点
typedef struct _ccPointSprite
{
    ccVertex2F    pos;        // 8 bytes	8字节
    ccColor4B    color;        // 4 bytes	4字节
    GLfloat        size;        // 4 bytes	4字节
} ccPointSprite;

//!    A 2D Quad. 4 * 2 floats
//! 一个2D的quad 8个浮点值
typedef struct _ccQuad2 {
    ccVertex2F        tl;
    ccVertex2F        tr;
    ccVertex2F        bl;
    ccVertex2F        br;
} ccQuad2;


//!    A 3D Quad. 4 * 3 floats
//! 一个3D的quad 12个浮点值
typedef struct _ccQuad3 {
    ccVertex3F        bl;
    ccVertex3F        br;
    ccVertex3F        tl;
    ccVertex3F        tr;
} ccQuad3;

//! a Point with a vertex point, a tex coord point and a color 4B
//! 由顶点，坐标点和4B的颜色值组成的点
typedef struct _ccV2F_C4B_T2F
{
    //! vertices (2F)		顶点
    ccVertex2F        vertices;
    //! colors (4B)		颜色
    ccColor4B        colors;
    //! tex coords (2F)		坐标
    ccTex2F            texCoords;
} ccV2F_C4B_T2F;

//! a Point with a vertex point, a tex coord point and a color 4F
//! 由顶点，坐标点和4F的颜色值组成的点
typedef struct _ccV2F_C4F_T2F
{
    //! vertices (2F)		顶点
    ccVertex2F        vertices;
    //! colors (4F)		颜色
    ccColor4F        colors;
    //! tex coords (2F)		坐标
    ccTex2F            texCoords;
} ccV2F_C4F_T2F;

//! a Point with a vertex point, a tex coord point and a color 4B
//! 由顶点，坐标点和4B的颜色值组成的点
typedef struct _ccV3F_C4B_T2F
{
    //! vertices (3F)
    ccVertex3F        vertices;            // 12 bytes		12字节
//    char __padding__[4];

    //! colors (4B)
    ccColor4B        colors;                // 4 bytes		4字节
//    char __padding2__[4];

    // tex coords (2F)
    ccTex2F            texCoords;            // 8 bytes		8字节
} ccV3F_C4B_T2F;

//! A Triangle of ccV2F_C4B_T2F
//! 由ccV2F_C4B_T2F构成的三角形
typedef struct _ccV2F_C4B_T2F_Triangle
{
	//! Point A		点A
	ccV2F_C4B_T2F a;
	//! Point B		点B
	ccV2F_C4B_T2F b;
	//! Point C		点C
	ccV2F_C4B_T2F c;
} ccV2F_C4B_T2F_Triangle;

//! A Quad of ccV2F_C4B_T2F
//! 由ccV2F_C4B_T2F构成的四边形
typedef struct _ccV2F_C4B_T2F_Quad
{
    //! bottom left		左下点
    ccV2F_C4B_T2F    bl;
    //! bottom right		右下点
    ccV2F_C4B_T2F    br;
    //! top left		左上点
    ccV2F_C4B_T2F    tl;
    //! top right		右上点
    ccV2F_C4B_T2F    tr;
} ccV2F_C4B_T2F_Quad;

//! 4 ccVertex3FTex2FColor4B
//! 由ccV3F_C4B_T2F构成的四边形
typedef struct _ccV3F_C4B_T2F_Quad
{
    //! top left		左上点
    ccV3F_C4B_T2F    tl;
    //! bottom left		左下点
    ccV3F_C4B_T2F    bl;
    //! top right		右上点
    ccV3F_C4B_T2F    tr;
    //! bottom right		右下点
    ccV3F_C4B_T2F    br;
} ccV3F_C4B_T2F_Quad;

//! 4 ccVertex2FTex2FColor4F Quad
//! 由ccV2F_C4F_T2F构成的四边形
typedef struct _ccV2F_C4F_T2F_Quad
{
    //! bottom left		左下点
    ccV2F_C4F_T2F    bl;
    //! bottom right		右下点
    ccV2F_C4F_T2F    br;
    //! top left		左上点
    ccV2F_C4F_T2F    tl;
    //! top right		右上点
    ccV2F_C4F_T2F    tr;
} ccV2F_C4F_T2F_Quad;

//! Blend Function used for textures
//! 用于纹理的混合功能
typedef struct _ccBlendFunc
{
    //! source blend function 		原混合
    GLenum src;
    //! destination blend function	目标混合
    GLenum dst;
} ccBlendFunc;

static const ccBlendFunc kCCBlendFuncDisable = {GL_ONE, GL_ZERO};

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Vertical text alignment type
//! 垂直文本对齐类型，可以在CCTexture2D.m文件中进行编辑更新
typedef enum
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
} CCVerticalTextAlignment;

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Horizontal text alignment type
//! 水平文本对齐类型，可以在CCTexture2D.m文件中进行编辑更新
typedef enum
{
    kCCTextAlignmentLeft,
    kCCTextAlignmentCenter,
    kCCTextAlignmentRight,
} CCTextAlignment;

// types for animation in particle systems
// 粒子系统中的动画类型
// texture coordinates for a quad
// 四边形的纹理坐标
typedef struct _ccT2F_Quad
{
    //! bottom left	左下
    ccTex2F    bl;
    //! bottom right	右下
    ccTex2F    br;
    //! top left	左上
    ccTex2F    tl;
    //! top right	右上
    ccTex2F    tr;
} ccT2F_Quad;

// struct that holds the size in pixels, texture coordinates and delays for animated CCParticleSystemQuad
// 该结构体还有以像素为单位的大小，纹理坐标，延时
typedef struct
{
    ccT2F_Quad texCoords;
    float delay;
    CCSize size; 
} ccAnimationFrameData;

NS_CC_END

#endif //__CCTYPES_H__
