/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
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
#ifndef __CCTMX_LAYER_H__
#define __CCTMX_LAYER_H__

#include "CCTMXObjectGroup.h"
#include "base_nodes/CCAtlasNode.h"
#include "sprite_nodes/CCSpriteBatchNode.h"
#include "CCTMXXMLParser.h"
NS_CC_BEGIN

class CCTMXMapInfo;
class CCTMXLayerInfo;
class CCTMXTilesetInfo;
struct _ccCArray;

/**
 * @addtogroup tilemap_parallax_nodes   瓦片地图视差节点
 * @{
 */

/** @brief CCTMXLayer represents the TMX layer.

It is a subclass of CCSpriteBatchNode. By default the tiles are rendered using a CCTextureAtlas.
If you modify a tile on runtime, then, that tile will become a CCSprite, otherwise no CCSprite objects are created.
The benefits of using CCSprite objects as tiles are:
- tiles (CCSprite) can be rotated/scaled/moved with a nice API

If the layer contains a property named "cc_vertexz" with an integer (in can be positive or negative),
then all the tiles belonging to the layer will use that value as their OpenGL vertex Z for depth.

On the other hand, if the "cc_vertexz" property has the "automatic" value, then the tiles will use an automatic vertex Z value.
Also before drawing the tiles, GL_ALPHA_TEST will be enabled, and disabled after drawing them. The used alpha func will be:

glAlphaFunc( GL_GREATER, value )

"value" by default is 0, but you can change it from Tiled by adding the "cc_alpha_func" property to the layer.
The value 0 should work for most cases, but if you have tiles that are semi-transparent, then you might want to use a different
value, like 0.5.

For further information, please see the programming guide:

http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:tiled_maps

@since v0.8.1
Tiles can have tile flags for additional properties. At the moment only flip horizontal and flip vertical are used. These bit flags are defined in CCTMXXMLParser.h.

@since 1.1
*/
// 是批量节点的子类，默认用纹理地图渲染；运行时修改一个瓦片，
// 变为一个精灵，否则没有对象可以创建；可以使用旋转，缩放，移动方法
// 瓦片具有标志属性；某一时刻，只有垂直和水平翻转使用，在CCTMXXMLParser.h有定义

class CC_DLL CCTMXLayer : public CCSpriteBatchNode
{
    /** size of the layer in tiles */
    // 层大小以瓦片为单位
    CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tLayerSize, LayerSize);
    /** size of the map's tile (could be different from the tile's size) */
    // 瓦片大小
    CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tMapTileSize, MapTileSize);
    /** pointer to the map of tiles */
    // 瓦片指针
    CC_SYNTHESIZE(unsigned int*, m_pTiles, Tiles);
    /** Tileset information for the layer */
    // 层中瓦片集合信息
    CC_PROPERTY(CCTMXTilesetInfo*, m_pTileSet, TileSet);
    /** Layer orientation, which is the same as the map orientation */
    // 层方向
    CC_SYNTHESIZE(unsigned int, m_uLayerOrientation, LayerOrientation);
    /** properties from the layer. They can be added using Tiled */
    // 层属性
    CC_PROPERTY(CCDictionary*, m_pProperties, Properties);
public:
    CCTMXLayer();
    virtual ~CCTMXLayer();
  
    /** creates a CCTMXLayer with an tileset info, a layer info and a map info */
    // 创建瓦片层，使用瓦片集合信息，层信息，地图信息为参数
    static CCTMXLayer * create(CCTMXTilesetInfo *tilesetInfo, CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);

    /** initializes a CCTMXLayer with a tileset info, a layer info and a map info */
    // 初始化瓦片层，使用瓦片集合信息，层信息，地图信息为参数
    bool initWithTilesetInfo(CCTMXTilesetInfo *tilesetInfo, CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);

    /** dealloc the map that contains the tile position from memory.
    Unless you want to know at runtime the tiles positions, you can safely call this method.
    If you are going to call layer->tileGIDAt() then, don't release the map
    */
    // 释放地图，从内存中；触发你知道运行的位置，安全调用此方法；可以调用:layer->tileGIDAt()
    void releaseMap();

    /** returns the tile (CCSprite) at a given a tile coordinate.
    The returned CCSprite will be already added to the CCTMXLayer. Don't add it again.
    The CCSprite can be treated like any other CCSprite: rotated, scaled, translated, opacity, color, etc.
    You can remove either by calling:
    - layer->removeChild(sprite, cleanup);
    - or layer->removeTileAt(ccp(x,y));
    */
    // 给定坐标点，返回瓦片； 该瓦片已经存在； 和其他精灵一样：旋转，缩放，移动，透明度，颜色等属性
    CCSprite* tileAt(const CCPoint& tileCoordinate);

    /** returns the tile gid at a given tile coordinate.
    if it returns 0, it means that the tile is empty.
    This method requires the the tile map has not been previously released (eg. don't call layer->releaseMap())
    */
    // 返回指定的标志gid
    unsigned int  tileGIDAt(const CCPoint& tileCoordinate);

    /** returns the tile gid at a given tile coordinate. It also returns the tile flags.
     This method requires the the tile map has not been previously released (eg. don't call [layer releaseMap])
     */
    // 返回gid，使用瓦片坐标
    unsigned int tileGIDAt(const CCPoint& tileCoordinate, ccTMXTileFlags* flags);

    /** sets the tile gid (gid = tile global id) at a given tile coordinate.
    The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
    If a tile is already placed at that position, then it will be removed.
    */
    // 设置gid,在指定坐标
    void setTileGID(unsigned int gid, const CCPoint& tileCoordinate);

    /** sets the tile gid (gid = tile global id) at a given tile coordinate.
     The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
     If a tile is already placed at that position, then it will be removed.
     
     Use withFlags if the tile flags need to be changed as well
     */
    // 设置gid，在指定坐标，标志
    void setTileGID(unsigned int gid, const CCPoint& tileCoordinate, ccTMXTileFlags flags);

    /** removes a tile at given tile coordinate */
    // 移除一个瓦片，使用坐标为参数
    void removeTileAt(const CCPoint& tileCoordinate);

    /** returns the position in points of a given tile coordinate */
    // 返回位置，以点为单位，使用坐标为参数
    CCPoint positionAt(const CCPoint& tileCoordinate);

    /** return the value for the specific property name */
    // 返回指定属性的值
    CCString *propertyNamed(const char *propertyName);

    /** Creates the tiles */
    // 创建瓦片
    void setupTiles();

    /** CCTMXLayer doesn't support adding a CCSprite manually.
    @warning addchild(z, tag); is not supported on CCTMXLayer. Instead of setTileGID.
    */
    // 增加子对象，z次序，标志
    virtual void addChild(CCNode * child, int zOrder, int tag);
    // super method
    // 父类方法
    void removeChild(CCNode* child, bool cleanup);

    inline const char* getLayerName(){ return m_sLayerName.c_str(); }
    inline void setLayerName(const char *layerName){ m_sLayerName = layerName; }
private:
    CCPoint positionForIsoAt(const CCPoint& pos);
    CCPoint positionForOrthoAt(const CCPoint& pos);
    CCPoint positionForHexAt(const CCPoint& pos);

    CCPoint calculateLayerOffset(const CCPoint& offset);

    /* optimization methods */
    // 优化方法
    CCSprite* appendTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* insertTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* updateTileForGID(unsigned int gid, const CCPoint& pos);

    /* The layer recognizes some special properties, like cc_vertez */
    // 层一些指定属性
    void parseInternalProperties();
    void setupTileSprite(CCSprite* sprite, CCPoint pos, unsigned int gid);
    CCSprite* reusedTileWithRect(CCRect rect);
    int vertexZForPos(const CCPoint& pos);

    // index    序号
    unsigned int atlasIndexForExistantZ(unsigned int z);
    unsigned int atlasIndexForNewZ(int z);
protected:
    //! name of the layer
    // 层名称
    std::string m_sLayerName;
    //! TMX Layer supports opacity
    //! 瓦片层支持容量
    unsigned char        m_cOpacity;

    unsigned int        m_uMinGID;
    unsigned int        m_uMaxGID;

    //! Only used when vertexZ is used
    //! 使用的顶点
    int                    m_nVertexZvalue;
    bool                m_bUseAutomaticVertexZ;

    //! used for optimization
    //! 用于优化
    CCSprite            *m_pReusedTile;
    ccCArray            *m_pAtlasIndexArray;
    
    // used for retina display
    // 高分辨率
    float               m_fContentScaleFactor;            
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_LAYER_H__

