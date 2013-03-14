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
#ifndef __CCLABEL_ATLAS_H__
#define __CCLABEL_ATLAS_H__

#include "base_nodes/CCAtlasNode.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label    标签
 * @{
 */

/** @brief CCLabelAtlas is a subclass of CCAtlasNode.

It can be as a replacement of CCLabel since it is MUCH faster.

CCLabelAtlas versus CCLabel:
- CCLabelAtlas is MUCH faster than CCLabel
- CCLabelAtlas "characters" have a fixed height and width
- CCLabelAtlas "characters" can be anything you want since they are taken from an image file

A more flexible class is CCLabelBMFont. It supports variable width characters and it also has a nice editor.
*/
/**
 * 是CCAtlasNode的子类
 * 取代CCLabel，因为使用这个更快
 * CCLabelAtlas 与 CCLabel比较：1，前者更快；2，前者具有高和宽；3，前者可以是任何对象，因为可以从图片文件中获取
 * 
 * 一个更加灵活的类是CCLabelBMFont. 支持宽字符，具有良好的编辑器
 */
class CC_DLL CCLabelAtlas : public CCAtlasNode, public CCLabelProtocol
{
public:
    CCLabelAtlas()
        :m_sString("")
    {}
    virtual ~CCLabelAtlas()
    { 
        m_sString.clear(); 
    }

    /** creates the CCLabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas */
    // 创建标签，使用字符串，字符文件，每个元素的宽，高，以及开始字符为参数
    static CCLabelAtlas * create(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    
    /** creates the CCLabelAtlas with a string and a configuration file
     @since v2.0
     */
    // 使用字符串和配置文件来创建
    static CCLabelAtlas* create(const char *string, const char *fntFile);

    /** initializes the CCLabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas */
   // 初始化标签，使用字符串，字符文件，每个元素的宽，高，以及开始字符为参数
   bool initWithString(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    
    /** initializes the CCLabelAtlas with a string and a configuration file
     @since v2.0
     */
    // 使用字符串和配置文件为参数，来创建标签
    bool initWithString(const char *string, const char *fntFile);
    
    /** initializes the CCLabelAtlas with a string, a texture, the width and height in points of each element and the starting char of the atlas */
    // 创建标签，使用字符串，纹理，每个元素的宽，高，以及开始字符为参数
    bool initWithString(const char* string, CCTexture2D* texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    
    // super methods
    // 父类方法
    virtual void updateAtlasValues();
    virtual void setString(const char *label);
    virtual const char* getString(void);
    
#if CC_LABELATLAS_DEBUG_DRAW
    virtual void draw();
#endif

protected:
    // string to render
    // 显示字符串
    std::string m_sString;
    // the first char in the charmap
    // 首字符
    unsigned int m_uMapStartChar;
};

// end of GUI group
/// @}
/// @}


NS_CC_END

#endif //__CCLABEL_ATLAS_H__
