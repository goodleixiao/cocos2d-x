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


#ifndef __CC_TM_XML_PARSER__
#define __CC_TM_XML_PARSER__

#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCSAXParser.h"

#include <string>

NS_CC_BEGIN

class CCTMXObjectGroup;

/** @file
* Internal TMX parser
*
* IMPORTANT: These classed should not be documented using doxygen strings
* since the user should not use them.
*
*/

/**
 * @addtogroup tilemap_parallax_nodes 瓦片地图 视差节点
 * @{
 */

enum {
    TMXLayerAttribNone = 1 << 0,
    TMXLayerAttribBase64 = 1 << 1,
    TMXLayerAttribGzip = 1 << 2,
    TMXLayerAttribZlib = 1 << 3,
};

enum {
    TMXPropertyNone,
    TMXPropertyMap,
    TMXPropertyLayer,
    TMXPropertyObjectGroup,
    TMXPropertyObject,
    TMXPropertyTile
};

typedef enum ccTMXTileFlags_ {
    kCCTMXTileHorizontalFlag        = 0x80000000,
    kCCTMXTileVerticalFlag            = 0x40000000,
    kCCTMXTileDiagonalFlag            = 0x20000000,
    kCCFlipedAll                    = (kCCTMXTileHorizontalFlag|kCCTMXTileVerticalFlag|kCCTMXTileDiagonalFlag),
    kCCFlippedMask                    = ~(kCCFlipedAll)
} ccTMXTileFlags;

// Bits on the far end of the 32-bit global tile ID (GID's) are used for tile flags

/** @brief CCTMXLayerInfo contains the information about the layers like:
- Layer name
- Layer size
- Layer opacity at creation time (it can be modified at runtime)
- Whether the layer is visible (if it's not visible, then the CocosNode won't be created)

This information is obtained from the TMX file.
*/
/** 32比特全局瓦片id标示瓦片
 * 层信息包括：层名称，层大小，层容量（运行时），层的可见性（若不可见则不创建）
 * 可以从tmx文件获取
 */
class CC_DLL CCTMXLayerInfo : public CCObject
{
    CC_PROPERTY(CCDictionary*, m_pProperties, Properties);
public:
    std::string         m_sName;
    CCSize              m_tLayerSize;
    unsigned int        *m_pTiles;
    bool                m_bVisible;
    unsigned char       m_cOpacity;
    bool                m_bOwnTiles;
    unsigned int        m_uMinGID;
    unsigned int        m_uMaxGID;
    CCPoint             m_tOffset;
public:
    CCTMXLayerInfo();
    virtual ~CCTMXLayerInfo();
};

/** @brief CCTMXTilesetInfo contains the information about the tilesets like:
- Tileset name
- Tileset spacing
- Tileset margin
- size of the tiles
- Image used for the tiles
- Image size

This information is obtained from the TMX file. 
*/
/** tmx瓦片集合信息：包括
 * 名称，容量，余量，瓦片大小，图片（瓦片使用），图片大小
 * 可以从tmx文件中获取
 */
class CC_DLL CCTMXTilesetInfo : public CCObject
{
public:
    std::string     m_sName;
    unsigned int    m_uFirstGid;
    CCSize          m_tTileSize;
    unsigned int    m_uSpacing;
    unsigned int    m_uMargin;
    //! filename containing the tiles (should be spritesheet / texture atlas)
    // 文件名称（需要是精灵表，纹理地图）
    std::string     m_sSourceImage;
    //! size in pixels of the image
    //! 图片大小，以像素为单位
    CCSize          m_tImageSize;
public:
    CCTMXTilesetInfo();
    virtual ~CCTMXTilesetInfo();
    CCRect rectForGID(unsigned int gid);
};

/** @brief CCTMXMapInfo contains the information about the map like:
- Map orientation (hexagonal, isometric or orthogonal)
- Tile size
- Map size

And it also contains:
- Layers (an array of TMXLayerInfo objects)
- Tilesets (an array of TMXTilesetInfo objects)
- ObjectGroups (an array of TMXObjectGroupInfo objects)

This information is obtained from the TMX file.

*/
/** tmx地图信息包括：
 * 方向：正交，六角，等距
 * 瓦片大小
 * 地图大小
 * 还有：层（一组层信息对象），瓦片集合（一组瓦片信息对象),对象组（一组tmx对象组信息对象）
 * 
 * 可以从tmx文件获取这些信息
 */
class CC_DLL CCTMXMapInfo : public CCObject, public CCSAXDelegator
{    
public:    
    /// map orientation
    /// 地图方向
    CC_SYNTHESIZE(int,    m_nOrientation, Orientation);
    /// map width & height
    /// 地图宽，高
    CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tMapSize, MapSize);
    /// tiles width & height
    /// 瓦片宽，高
    CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tTileSize, TileSize);
    /// Layers
    /// 层
    CC_PROPERTY(CCArray*, m_pLayers, Layers);
    /// tilesets
    /// 瓦片集合
    CC_PROPERTY(CCArray*, m_pTilesets, Tilesets);
    /// ObjectGroups
    /// 对象组
    CC_PROPERTY(CCArray*, m_pObjectGroups, ObjectGroups);
    /// parent element
    /// 父类元素
    CC_SYNTHESIZE(int, m_nParentElement, ParentElement);
    /// parent GID
    /// 父类gid 
    CC_SYNTHESIZE(unsigned int, m_uParentGID, ParentGID);
    /// layer attribs
    /// 层属性
    CC_SYNTHESIZE(int, m_nLayerAttribs, LayerAttribs);
    /// is storing characters?
    /// 是否存储字符
    CC_SYNTHESIZE(bool, m_bStoringCharacters, StoringCharacters);
    /// properties
    /// 属性
    CC_PROPERTY(CCDictionary*, m_pProperties, Properties);
public:    
    CCTMXMapInfo();
    virtual ~CCTMXMapInfo();
    /** creates a TMX Format with a tmx file */
    // 创建tmx格式，使用tmx文件为参数
    static CCTMXMapInfo * formatWithTMXFile(const char *tmxFile);
    /** creates a TMX Format with an XML string and a TMX resource path */
    // 创建tmx格式，使用xml字符串，tmx资源路径为参数
    static CCTMXMapInfo * formatWithXML(const char* tmxString, const char* resourcePath);
    /** initializes a TMX format with a  tmx file */
    // 初始化tmx格式，使用tmx文件为参数
    bool initWithTMXFile(const char *tmxFile);
    /** initializes a TMX format with an XML string and a TMX resource path */
    // 初始化tmx格式，使用xml字符串，tmx资源路径为参数
    bool initWithXML(const char* tmxString, const char* resourcePath);
    /** initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file */
    // 初始化方法，使用xml文件，tmx文件或瓦片集合文件为参数
    bool parseXMLFile(const char *xmlFilename);
    /* initializes parsing of an XML string, either a tmx (Map) string or tsx (Tileset) string */
    bool parseXMLString(const char *xmlString);

    CCDictionary* getTileProperties();
    void setTileProperties(CCDictionary* tileProperties);

    // implement pure virtual methods of CCSAXDelegator
    // 实现虚函数
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
    inline const char* getCurrentString(){ return m_sCurrentString.c_str(); }
    inline void setCurrentString(const char *currentString){ m_sCurrentString = currentString; }
    inline const char* getTMXFileName(){ return m_sTMXFileName.c_str(); }
    inline void setTMXFileName(const char *fileName){ m_sTMXFileName = fileName; }
private:
    void internalInit(const char* tmxFileName, const char* resourcePath);
protected:
    //! tmx filename
    //! tmx 文件名称
    std::string m_sTMXFileName;
    // tmx resource path
    // tmx 资源路径
    std::string m_sResources;
    //! current string
    //! 当前字符串
    std::string m_sCurrentString;
    //! tile properties
    //! 瓦片属性
    CCDictionary* m_pTileProperties;
    unsigned int m_uCurrentFirstGID;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif

