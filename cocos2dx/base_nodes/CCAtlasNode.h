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

#ifndef __CCATLAS_NODE_H__
#define __CCATLAS_NODE_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes	基本节点
 * @{
 */

class CCTextureAtlas;

/** @brief CCAtlasNode is a subclass of CCNode that implements the CCRGBAProtocol and CCTextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing CCAtlasNode (or a subclass of CCAtlasNode)

All features from CCNode are valid, plus the following features:
- opacity and RGB colors
*/
/** 是节点的子类，实现CCRGBAProtocol和纹理协议的
 * 如何程序纹理地图对象
 * 如何你要程序纹理地图，使用该类或者是其子类
 * 所有节点特征都是有效地，增加了透明度和颜色值
 */
class CC_DLL CCAtlasNode : public CCNodeRGBA, public CCTextureProtocol
{
protected:

    //! chars per row
    //! 每行字符
    unsigned int m_uItemsPerRow;
    //! chars per column
    //! 每列字符
    unsigned int m_uItemsPerColumn;

    //! width of each char
    //! 每个字符宽
    unsigned int    m_uItemWidth;
    //! height of each char
    //! 每个字符高
    unsigned int    m_uItemHeight;

    ccColor3B    m_tColorUnmodified;

    CC_PROPERTY(CCTextureAtlas*, m_pTextureAtlas, TextureAtlas);

    // protocol variables
    // 协议变量
    bool m_bIsOpacityModifyRGB;
    
    CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc);

    // quads to draw ？？
    CC_PROPERTY(unsigned int, m_uQuadsToDraw, QuadsToDraw);
    // color uniform
    // 颜色均匀
    GLint    m_nUniformColor;
public:
    CCAtlasNode();
    virtual ~CCAtlasNode();

	/** creates a CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	// 创建一个节点集，用文件，宽，高，参数
	static CCAtlasNode * create(const char* tile,unsigned int tileWidth, unsigned int tileHeight, 
		unsigned int itemsToRender);

    /** initializes an CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
    // 初始化使用宽，高，数目等参数
    bool initWithTileFile(const char* tile, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender);

    /** initializes an CCAtlasNode  with a texture the width and height of each item measured in points and the quantity of items to render*/
    // 使用纹理，宽，高，数目参数初始化方法
    bool initWithTexture(CCTexture2D* texture, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender);
    
    /** updates the Atlas (indexed vertex array).
    * Shall be overridden in subclasses
    */
    // 更新数组方法
    virtual void updateAtlasValues();

    virtual void draw(void);

    // CC Texture protocol

    /** returns the used texture*/
    // 纹理协议，返回纹理
    virtual CCTexture2D* getTexture(void);

    /** sets a new texture. it will be retained*/
    // 设置一个新的纹理
    virtual void setTexture(CCTexture2D *texture);
    
    virtual bool isOpacityModifyRGB();
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);
    virtual const ccColor3B& getColor(void);
    virtual void setColor(const ccColor3B& color);
    virtual void setOpacity(GLubyte opacity);

private :
    void calculateMaxItems();
    void updateBlendFunc();
    void updateOpacityModifyRGB();

};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCATLAS_NODE_H__


