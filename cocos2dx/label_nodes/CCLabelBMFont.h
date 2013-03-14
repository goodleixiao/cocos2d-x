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

Use any of these editors to generate BMFonts:
  http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
  http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
  http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
  http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#ifndef __CCBITMAP_FONT_ATLAS_H__
#define __CCBITMAP_FONT_ATLAS_H__

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "support/data_support/uthash.h"
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label	标签
 * @{
 */

enum {
    kCCLabelAutomaticWidth = -1,
};

struct _FontDefHashElement;

/**
@struct ccBMFontDef
BMFont definition
*/
// BMFont定义
typedef struct _BMFontDef {
    //! ID of the character
    //! 字符的ID
    unsigned int charID;
    //! origin and size of the font
    //! 字体的原点和大小
    CCRect rect;
    //! The X amount the image should be offset when drawing the image (in pixels)
    //! 绘制图片时，x轴偏移量，以像素为单位
    short xOffset;
    //! The Y amount the image should be offset when drawing the image (in pixels)
    //! 绘制图片时，y轴偏移量，以像素为单位
    short yOffset;
    //! The amount to move the current position after drawing the character (in pixels)
    //! 绘制字符后，移动当前的位置的值，以像素为单位
    short xAdvance;
} ccBMFontDef;

/** @struct ccBMFontPadding
BMFont padding
@since v0.8.2
*/
// 填充，padding
typedef struct _BMFontPadding {
    /// padding left
    /// 左方向填充
    int    left;
    /// padding top
    /// 上方向填充
    int top;
    /// padding right
    /// 右方向填充
    int right;
    /// padding bottom
    /// 底部填充
    int bottom;
} ccBMFontPadding;

typedef struct _FontDefHashElement
{
	unsigned int	key;		// key. Font Unicode value 字体统一编码值
	ccBMFontDef		fontDef;	// font definition  字体定义声明
	UT_hash_handle	hh;
} tCCFontDefHashElement;

// Equal function for targetSet.
// 与targetSet功能相同
typedef struct _KerningHashElement
{
	int				key;		// key for the hash. 16-bit for 1st element, 16-bit for 2nd element	哈希值键
	int				amount;
	UT_hash_handle	hh;
} tCCKerningHashElement;

/** @brief CCBMFontConfiguration has parsed configuration of the the .fnt file
@since v0.8
*/
// 解析.fnt文件配置
class CC_DLL CCBMFontConfiguration : public CCObject
{
    // XXX: Creating a public interface so that the bitmapFontArray[] is accessible
public://@public
    // BMFont definitions
    // 创建一个公共接口来访问bitmapFontArray[]; 声明
    tCCFontDefHashElement *m_pFontDefDictionary;

    //! FNTConfig: Common Height Should be signed (issue #1343)
    //! 统一高度，
    int m_nCommonHeight;
    //! Padding
    //! 填充
    ccBMFontPadding    m_tPadding;
    //! atlas name
    //! 图集名称
    std::string m_sAtlasName;
    //! values for kerning
    //! 字距值
    tCCKerningHashElement *m_pKerningDictionary;
    
    // Character Set defines the letters that actually exist in the font
    // 字符集定义实际存在的字体的字母
    std::set<unsigned int> *m_pCharacterSet;
public:
    CCBMFontConfiguration();
    virtual ~CCBMFontConfiguration();
    const char * description();

    /** allocates a CCBMFontConfiguration with a FNT file */
    // 用一个fnt文件分配配置
    static CCBMFontConfiguration * create(const char *FNTfile);

    /** initializes a BitmapFontConfiguration with a FNT file */
    // 初始化配置，使用fnt文件
    bool initWithFNTfile(const char *FNTfile);
    
    inline const char* getAtlasName(){ return m_sAtlasName.c_str(); }
    inline void setAtlasName(const char* atlasName) { m_sAtlasName = atlasName; }
    
    std::set<unsigned int>* getCharacterSet() const;
private:
    std::set<unsigned int>* parseConfigFile(const char *controlFile);
    void parseCharacterDefinition(std::string line, ccBMFontDef *characterDefinition);
    void parseInfoArguments(std::string line);
    void parseCommonArguments(std::string line);
    void parseImageFileName(std::string line, const char *fntFile);
    void parseKerningEntry(std::string line);
    void purgeKerningDictionary();
    void purgeFontDefDictionary();
};

/** @brief CCLabelBMFont is a subclass of CCSpriteBatchNode.

Features:
- Treats each character like a CCSprite. This means that each individual character can be:
- rotated
- scaled
- translated
- tinted
- change the opacity
- It can be used as part of a menu item.
- anchorPoint can be used to align the "label"
- Supports AngelCode text format

Limitations:
- All inner characters are using an anchorPoint of (0.5f, 0.5f) and it is not recommend to change it
because it might affect the rendering

CCLabelBMFont implements the protocol CCLabelProtocol, like CCLabel and CCLabelAtlas.
CCLabelBMFont has the flexibility of CCLabel, the speed of CCLabelAtlas and all the features of CCSprite.
If in doubt, use CCLabelBMFont instead of CCLabelAtlas / CCLabel.

Supported editors:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

@since v0.8
*/
/** 是CCSpriteBatchNode的子类
 * 可以认为是一个精灵，具有的特征是：旋转，缩放，移动，着色，改变透明度，可以认为是菜单的一部分，锚点，支持文本格式
 * 限制：所有内部字符使用锚点为(0.5,0.5)，不推荐改变；可能会影响呈现效果
 * 实现标签协议；
 * 是更加灵活的标签，具有CCLabelAtlas的速度和精灵的所有特性；可以替换CCLabel/CCLabelAtlas使用
 * 支持链接：http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)
*/

class CC_DLL CCLabelBMFont : public CCSpriteBatchNode, public CCLabelProtocol, public CCRGBAProtocol
{
public:
    CCLabelBMFont();

    virtual ~CCLabelBMFont();
    /** Purges the cached data.
    Removes from memory the cached configurations and the atlas name dictionary.
    @since v0.99.3
    */
    // 清除缓存
    static void purgeCachedData();

    /** creates a bitmap font atlas with an initial string and the FNT file */
    // 创建一个位图字体集，使用字符串，fnt文件为参数
    static CCLabelBMFont * create(const char *str, const char *fntFile, float width, CCTextAlignment alignment, CCPoint imageOffset);
    
	static CCLabelBMFont * create(const char *str, const char *fntFile, float width, CCTextAlignment alignment);

	static CCLabelBMFont * create(const char *str, const char *fntFile, float width);

	static CCLabelBMFont * create(const char *str, const char *fntFile);

    /** Creates an label.
     */
    // 创建一个标签
    static CCLabelBMFont * create();

    bool init();
    /** init a bitmap font atlas with an initial string and the FNT file */
    // 使用字符串，fnt文件为参数来初始化一个位图字符集
    bool initWithString(const char *str, const char *fntFile, float width = kCCLabelAutomaticWidth, CCTextAlignment alignment = kCCTextAlignmentLeft, CCPoint imageOffset = CCPointZero);

    /** updates the font chars based on the string to render */
    // 更新字符
    void createFontChars();
    // super method
    // 父类方法
    virtual void setString(const char *label);
    virtual void setString(const char *label, bool fromUpdate);
    virtual void updateString(bool fromUpdate);
    virtual const char* getString(void);
    virtual void setCString(const char *label);
    virtual void setAnchorPoint(const CCPoint& var);
    virtual void updateLabel();
    virtual void setAlignment(CCTextAlignment alignment);
    virtual void setWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    virtual void setScale(float scale);
    virtual void setScaleX(float scaleX);
    virtual void setScaleY(float scaleY);
    
    // CCRGBAProtocol  颜色协议
    virtual bool isOpacityModifyRGB();
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB); virtual GLubyte getOpacity();
    virtual GLubyte getDisplayedOpacity();
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled();
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    virtual const ccColor3B& getColor(void);
    virtual const ccColor3B& getDisplayedColor();
    virtual void setColor(const ccColor3B& color);
    virtual void updateDisplayedColor(const ccColor3B& parentColor);
    virtual bool isCascadeColorEnabled();
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);

    void setFntFile(const char* fntFile);
    const char* getFntFile();
#if CC_LABELBMFONT_DEBUG_DRAW
    virtual void draw();
#endif // CC_LABELBMFONT_DEBUG_DRAW
private:
    char * atlasNameFromFntFile(const char *fntFile);
    int kerningAmountForFirst(unsigned short first, unsigned short second);
    float getLetterPosXLeft( CCSprite* characterSprite );
    float getLetterPosXRight( CCSprite* characterSprite );
    
protected:
    // string to render
    // 呈现字符串
    unsigned short* m_sString;
    
    // name of fntFile
    // fnt文件名称
    std::string m_sFntFile;
    
    // initial string without line breaks
    // 初始字符串，没有换行
    std::string m_sInitialString;
    // alignment of all lines
    // 对齐方式
    CCTextAlignment m_pAlignment;
    // max width until a line break is added
    // 行的最大宽度，直到换行
    float m_fWidth;
    
    CCBMFontConfiguration *m_pConfiguration;
    
    bool m_bLineBreakWithoutSpaces;
    // offset of the texture atlas
    // 纹理偏移量
    CCPoint    m_tImageOffset;
    
    // reused char
    // 重用字符
    CCSprite *m_pReusedChar;
    
    // texture RGBA
    // 纹理颜色值
    GLubyte m_cDisplayedOpacity;
    GLubyte m_cRealOpacity;
    ccColor3B m_tDisplayedColor;
    ccColor3B m_tRealColor;
    bool m_bCascadeColorEnabled;
    bool m_bCascadeOpacityEnabled;
    /** conforms to CCRGBAProtocol protocol */
    // 符合颜色协议
    bool        m_bIsOpacityModifyRGB;

};

/** Free function that parses a FNT file a place it on the cache
*/
// 载人fnt文件到缓存
CC_DLL CCBMFontConfiguration * FNTConfigLoadFile( const char *file );
/** Purges the FNT config cache
*/
// 清除fnt配置缓存
CC_DLL void FNTConfigRemoveCache( void );

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCBITMAP_FONT_ATLAS_H__
