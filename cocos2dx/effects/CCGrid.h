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
#ifndef __EFFECTS_CCGRID_H__
#define __EFFECTS_CCGRID_H__

#include "cocoa/CCObject.h"
#include "base_nodes/CCNode.h"
#include "CCCamera.h"
#include "ccTypes.h"
#include "textures/CCTexture2D.h"
#include "CCDirector.h"
#include "kazmath/mat4.h"

NS_CC_BEGIN

class CCTexture2D;
class CCGrabber;
class CCGLProgram;

/**
 * @addtogroup effects 效果
 * @{
 */

/** Base class for other
*/
// 基类为其他类使用
class CC_DLL CCGridBase : public CCObject
{
public:
    virtual ~CCGridBase(void);

    /** whether or not the grid is active */
    // 网格是否激活状态
    inline bool isActive(void) { return m_bActive; }
    void setActive(bool bActive);

    /** number of times that the grid will be reused */
    // 获取网格重用的次数
    inline int getReuseGrid(void) { return m_nReuseGrid; }
    inline void setReuseGrid(int nReuseGrid) { m_nReuseGrid = nReuseGrid; }

    /** size of the grid */
    // 网格大小
    inline const CCSize& getGridSize(void) { return m_sGridSize; }
    inline void setGridSize(const CCSize& gridSize) { m_sGridSize = gridSize; }

    /** pixels between the grids */
    // 网格间像素
    inline const CCPoint& getStep(void) { return m_obStep; }
    inline void setStep(const CCPoint& step) { m_obStep = step; }

    /** is texture flipped */
    // 是纹理翻转
    inline bool isTextureFlipped(void) { return m_bIsTextureFlipped; }
    void setTextureFlipped(bool bFlipped);

    bool initWithSize(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
    bool initWithSize(const CCSize& gridSize);

    void beforeDraw(void);
    void afterDraw(CCNode *pTarget);
    virtual void blit(void);
    virtual void reuse(void);
    virtual void calculateVertexPoints(void);

public:

    /** create one Grid */
    // 创建网格， 使用大小，纹理，是否翻转为参数
    static CCGridBase* create(const CCSize& gridSize, CCTexture2D *texture, bool flipped);
    /** create one Grid */
    // 创建网格，使用大小参数
    static CCGridBase* create(const CCSize& gridSize);
    // 设置2D投影
    void set2DProjection(void);

protected:
    bool m_bActive;
    int  m_nReuseGrid;
    CCSize m_sGridSize;
    CCTexture2D *m_pTexture;
    CCPoint m_obStep;
    CCGrabber *m_pGrabber;
    bool m_bIsTextureFlipped;
    CCGLProgram* m_pShaderProgram;
    ccDirectorProjection m_directorProjection;
};

/**
 CCGrid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 */
// 3D网格，每个顶点都有3个尺寸：x,y,z
class CC_DLL CCGrid3D : public CCGridBase
{
public:
    CCGrid3D();
    ~CCGrid3D(void);

    /** returns the vertex at a given position */
    // 给定位置，返回一个顶点
    ccVertex3F vertex(const CCPoint& pos);
    /** returns the original (non-transformed) vertex at a given position */
    // 返回一个原顶点，给定位置，非转化
    ccVertex3F originalVertex(const CCPoint& pos);
    /** sets a new vertex at a given position */
    // 设置新的顶点，在给定位置
    void setVertex(const CCPoint& pos, const ccVertex3F& vertex);

    virtual void blit(void);
    virtual void reuse(void);
    virtual void calculateVertexPoints(void);

public:
    /** create one Grid */
    // 创建一个网格，使用大小，纹理，是否翻转为参数
    static CCGrid3D* create(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
    /** create one Grid */
    // 创建网格，使用大小参数
    static CCGrid3D* create(const CCSize& gridSize);
    
protected:
    GLvoid *m_pTexCoordinates;
    GLvoid *m_pVertices;
    GLvoid *m_pOriginalVertices;
    GLushort *m_pIndices;
};

/**
 CCTiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 the tiles can be separated from the grid.
*/
// 3D实现，瓦片可以从网格分离的
class CC_DLL CCTiledGrid3D : public CCGridBase
{
public:
    CCTiledGrid3D();
    ~CCTiledGrid3D(void);

    /** returns the tile at the given position */
    // 给定位置，返回瓦片
    ccQuad3 tile(const CCPoint& pos);
    /** returns the original tile (untransformed) at the given position */
    // 给定位置，返回原瓦片
    ccQuad3 originalTile(const CCPoint& pos);
    /** sets a new tile */
    // 设置一个新的瓦片
    void setTile(const CCPoint& pos, const ccQuad3& coords);

    virtual void blit(void);
    virtual void reuse(void);
    virtual void calculateVertexPoints(void);

public:

    /** create one Grid */
    // 创建一个网格，使用大小，纹理，是否翻转
    static CCTiledGrid3D* create(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
    /** create one Grid */
    // 创建一个网格，使用大小参数
    static CCTiledGrid3D* create(const CCSize& gridSize);
    
protected:
    GLvoid *m_pTexCoordinates;
    GLvoid *m_pVertices;
    GLvoid *m_pOriginalVertices;
    GLushort *m_pIndices;
};

// end of effects group
/// @}

NS_CC_END

#endif // __EFFECTS_CCGRID_H__
