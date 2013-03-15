/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#ifndef __CCLABELTTF_H__
#define __CCLABELTTF_H__

#include "sprite_nodes/CCSprite.h"
#include "textures/CCTexture2D.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label    标签
 * @{
 */

/** @brief CCLabelTTF is a subclass of CCTextureNode that knows how to render text labels
*
* All features from CCTextureNode are valid in CCLabelTTF
*
* CCLabelTTF objects are slow. Consider using CCLabelAtlas or CCLabelBMFont instead.
*/
/** 是CCTextureNode的子类，知道怎么呈现文本标签
 * 具有CCTextureNode的所有特性
 * 对象运行慢，使用CCLabelAtlas或CCLabelBMFont替换
 */
class CC_DLL CCLabelTTF : public CCSprite, public CCLabelProtocol
{
public:
    CCLabelTTF();
    virtual ~CCLabelTTF();
    const char* description();    
    
    /** creates a CCLabelTTF with a font name and font size in points
     @since v2.0.1
     */
    // 创建标签，使用字体名称，字体大小以点为单位 作为参数
    static CCLabelTTF * create(const char *string, const char *fontName, float fontSize);
    
    /** creates a CCLabelTTF from a fontname, horizontal alignment, dimension in points,  and font size in points.
     @since v2.0.1
     */
    // 创建标签，使用字体名称，水平对齐，字距，大小为参数
    static CCLabelTTF * create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment);
  
    /** creates a CCLabel from a fontname, alignment, dimension in points and font size in points
     @since v2.0.1
     */
    // 创建标签，使用字体名称，对齐方式，字距，大小为参数
    static CCLabelTTF * create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment);
    
    /** initializes the CCLabelTTF with a font name and font size */
    // 初始化标签，使用字体名称，字体大小为参数
    bool initWithString(const char *string, const char *fontName, float fontSize);
    
    /** initializes the CCLabelTTF with a font name, alignment, dimension and font size */
    // 初始化标签，使用字体名称，对齐方式，字距，字体大小为参数
    bool initWithString(const char *string, const char *fontName, float fontSize,
                        const CCSize& dimensions, CCTextAlignment hAlignment);

    /** initializes the CCLabelTTF with a font name, alignment, dimension and font size */
    // 初始化标签，使用字体名称，对齐方式，字距，字体大小
    bool initWithString(const char *string, const char *fontName, float fontSize,
                        const CCSize& dimensions, CCTextAlignment hAlignment, 
                        CCVerticalTextAlignment vAlignment);
    
    /** initializes the CCLabelTTF */
    // 初始化方法 
    bool init();

    /** Creates an label.
     */
    // 创建一个标签
    static CCLabelTTF * create();

    /** changes the string to render
    * @warning Changing the string is as expensive as creating a new CCLabelTTF. To obtain better performance use CCLabelAtlas
    */
    // 呈现改变的字符串
    virtual void setString(const char *label);
    virtual const char* getString(void);
    
    CCTextAlignment getHorizontalAlignment();
    void setHorizontalAlignment(CCTextAlignment alignment);
    
    CCVerticalTextAlignment getVerticalAlignment();
    void setVerticalAlignment(CCVerticalTextAlignment verticalAlignment);
    
    CCSize getDimensions();
    void setDimensions(const CCSize &dim);
    
    float getFontSize();
    void setFontSize(float fontSize);
    
    const char* getFontName();
    void setFontName(const char *fontName);

private:
    bool updateTexture();
protected:
    /** Dimensions of the label in Points */
    // 字距
    CCSize m_tDimensions;
    /** The alignment of the label */
    CCTextAlignment         m_hAlignment;
    /** The vertical alignment of the label */
    // 标签的垂直对齐
    CCVerticalTextAlignment m_vAlignment;
    /** Font name used in the label */
    // 字体名称
    std::string * m_pFontName;
    /** Font size of the label */
    // 字体大小
    float m_fFontSize;
    
    std::string m_string;
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

