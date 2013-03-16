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
#ifndef __CCTMX_TILE_MAP_H__
#define __CCTMX_TILE_MAP_H__

#include "base_nodes/CCNode.h"
#include "CCTMXObjectGroup.h"

NS_CC_BEGIN

class CCTMXObjectGroup;
class CCTMXLayer;
class CCTMXLayerInfo;
class CCTMXTilesetInfo;
class CCTMXMapInfo;

/**
 * @addtogroup tilemap_parallax_nodes 瓦片地图节点
 * @{
 */

/** Possible orientations of the TMX map */
// 瓦片地图可能的方向
enum
{
    /** Orthogonal orientation */
    // 正交方向
    CCTMXOrientationOrtho,

    /** Hexagonal orientation */
    // 六角方向
    CCTMXOrientationHex,

    /** Isometric orientation */
    // 等距方向
    CCTMXOrientationIso,
};

/** @brief CCTMXTiledMap knows how to parse and render a TMX map.

It adds support for the TMX tiled map format used by http://www.mapeditor.org
It supports isometric, hexagonal and orthogonal tiles.
It also supports object groups, objects, and properties.

Features:
- Each tile will be treated as an CCSprite
- The sprites are created on demand. They will be created only when you call "layer->tileAt(position)"
- Each tile can be rotated / moved / scaled / tinted / "opaqued", since each tile is a CCSprite
- Tiles can be added/removed in runtime
- The z-order of the tiles can be modified in runtime
- Each tile has an anchorPoint of (0,0)
- The anchorPoint of the TMXTileMap is (0,0)
- The TMX layers will be added as a child
- The TMX layers will be aliased by default
- The tileset image will be loaded using the CCTextureCache
- Each tile will have a unique tag
- Each tile will have a unique z value. top-left: z=1, bottom-right: z=max z
- Each object group will be treated as an CCMutableArray
- Object class which will contain all the properties in a dictionary
- Properties can be assigned to the Map, Layer, Object Group, and Object

Limitations:
- It only supports one tileset per layer.
- Embedded images are not supported
- It only supports the XML format (the JSON format is not supported)

Technical description:
Each layer is created using an CCTMXLayer (subclass of CCSpriteBatchNode). If you have 5 layers, then 5 CCTMXLayer will be created,
unless the layer visibility is off. In that case, the layer won't be created at all.
You can obtain the layers (CCTMXLayer objects) at runtime by:
- map->getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
- map->layerNamed(name_of_the_layer);

Each object group is created using a CCTMXObjectGroup which is a subclass of CCMutableArray.
You can obtain the object groups at runtime by:
- map->objectGroupNamed(name_of_the_object_group);

Each object is a CCTMXObject.

Each property is stored as a key-value pair in an CCMutableDictionary.
You can obtain the properties at runtime by:

map->propertyNamed(name_of_the_property);
layer->propertyNamed(name_of_the_property);
objectGroup->propertyNamed(name_of_the_property);
object->propertyNamed(name_of_the_property);

@since v0.8.1
*/
/** 知道怎样显示tmx地图；
 * 增加支持tmx瓦片地图格式；支持正交，六角，等距瓦片； 特征具有：
    1，作为精灵；2，创建精灵仅仅可以调用[layer titleAt:];3，可以旋转，移动，缩放，透明度；4，可以在运行时增加移除；
    5，运行时排序；6，锚点都为(0,0);7，增加子对象；8，默认别名；9，使用纹理缓存载人图片；10，独一无二标示；
    11，独一无二z值；12，每个对象组都可以作为可变数组；13，所有属性都在字典中；14，属性可以赋值给地图，层，对象组，对象；
 *限制：每个层仅仅一个瓦片集合；不支持嵌入式图片；只支持xml格式，不支持json格式；
 * 
 * 技术描述：使用CCTMXLayer来创建每个层；如果层的可见性关了，曾不能创建；可以在运行时获取层：[map getChildByTag:tag_number]
 * 每个对象组都可以被认为是可变数组的子类；可以使用[map objectGroupNamed:name_of_object_group]获取
 * 每个对象是CCTMXObject; 每个属性都存储在可变字典里；可以在运行时获取属性；
 */
class CC_DLL CCTMXTiledMap : public CCNode
{
    /** the map's size property measured in tiles */
    // 地图大小，以瓦片为单位
    CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tMapSize, MapSize);
    /** the tiles's size property measured in pixels */
    // 瓦片大小，以像素为单位
    CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tTileSize, TileSize);
    /** map orientation */
    // 地图方向
    CC_SYNTHESIZE(int, m_nMapOrientation, MapOrientation);
    /** object groups */
    // 对象组
    CC_PROPERTY(CCArray*, m_pObjectGroups, ObjectGroups);
    /** properties */
    // 属性
    CC_PROPERTY(CCDictionary*, m_pProperties, Properties);
public:
    CCTMXTiledMap();
    virtual ~CCTMXTiledMap();

    /** creates a TMX Tiled Map with a TMX file.*/
    // 创建tmx瓦片地图，使用tmx文件为参数
    static CCTMXTiledMap* create(const char *tmxFile);

    /** initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources */
    // 创建地图，使用字符串，路径为参数
    static CCTMXTiledMap* createWithXML(const char* tmxString, const char* resourcePath);

    /** initializes a TMX Tiled Map with a TMX file */
    // 初始化地图，使用tmx文件为参数
    bool initWithTMXFile(const char *tmxFile);

    /** initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources */
    // 初始化地图，使用tmx格式的xml字符串和路径为参数
    bool initWithXML(const char* tmxString, const char* resourcePath);

    /** return the TMXLayer for the specific layer */
    // 返回指定层
    CCTMXLayer* layerNamed(const char *layerName);

    /** return the TMXObjectGroup for the specific group */
    // 返回对象组，使用组名称为参数
    CCTMXObjectGroup* objectGroupNamed(const char *groupName);

    /** return the value for the specific property name */
    // 返回指定属性值
    CCString *propertyNamed(const char *propertyName);

    /** return properties dictionary for tile GID */
    // 返回属性字典，使用gid为参数
    CCDictionary* propertiesForGID(int GID);

private:
    CCTMXLayer * parseLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);
    CCTMXTilesetInfo * tilesetForLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);
    void buildWithMapInfo(CCTMXMapInfo* mapInfo);
protected:
    //! tile properties
    //! 瓦片属性
    CCDictionary* m_pTileProperties;

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_TILE_MAP_H__


