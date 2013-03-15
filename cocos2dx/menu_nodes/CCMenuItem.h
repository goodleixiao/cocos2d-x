/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2011 Ricardo Quesada
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

#ifndef __CCMENU_ITEM_H__
#define __CCMENU_ITEM_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN
    
class CCLabelTTF;
class CCLabelAtlas;
class CCSprite;
class CCSpriteFrame;
#define kCCItemSize 32
    
/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu     菜单
 * @{
 */

/** @brief CCMenuItem base class
 *
 *  Subclass CCMenuItem (or any subclass) to create your custom CCMenuItem objects.
 */
// 创建自定义的菜单项对象
class CC_DLL CCMenuItem : public CCNodeRGBA
{
protected:
    /** whether or not the item is selected
     @since v0.8.2
     */
    // 是否被选中
    bool m_bSelected;
    bool m_bEnabled;

public:
    CCMenuItem()
    : m_bSelected(false)
    , m_bEnabled(false)            
    , m_pListener(NULL)            
    , m_pfnSelector(NULL)
    , m_nScriptTapHandler(0)
    {}
    virtual ~CCMenuItem();

    /** Creates a CCMenuItem with no target/selector */
    // 创建菜单项，没有参数
    static CCMenuItem* create();
    /** Creates a CCMenuItem with a target/selector */
    // 创建菜单项，使用目标，选择器为参数
    static CCMenuItem* create(CCObject *rec, SEL_MenuHandler selector);
    /** Initializes a CCMenuItem with a target/selector */
    // 初始化菜单项，使用目标，选择器为参数
    bool initWithTarget(CCObject *rec, SEL_MenuHandler selector);
    /** Returns the outside box */
    // 返回边界
    CCRect rect();
    /** Activate the item */
    // 激活菜单项
    virtual void activate();
    /** The item was selected (not activated), similar to "mouse-over" */
    // 选中菜单项
    virtual void selected();
    /** The item was unselected */
    // 未选中
    virtual void unselected();
    
    /** Register menu handler script function */
    // 注册菜单处理脚本功能
    virtual void registerScriptTapHandler(int nHandler);
    virtual void unregisterScriptTapHandler(void);
    int getScriptTapHandler() { return m_nScriptTapHandler; };

    virtual bool isEnabled();
    //@note: It's 'setIsEnable' in cocos2d-iphone. 
    // 注意在cocos2d-iphone中是使用setIsEnable
    virtual void setEnabled(bool value);
    virtual bool isSelected();
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    /** set the target/selector of the menu item*/
    // 设置菜单项的目标，选择器
    void setTarget(CCObject *rec, SEL_MenuHandler selector);

protected:
    CCObject*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    int             m_nScriptTapHandler;
};

/** @brief An abstract class for "label" CCMenuItemLabel items 
 Any CCNode that supports the CCLabelProtocol protocol can be added.
 Supported nodes:
 - CCBitmapFontAtlas
 - CCLabelAtlas
 - CCLabelTTF
 */
// 菜单项标签：任何节点都支持标签协议：支持的节点为 - CCBitmapFontAtlas - CCLabelAtlas - CCLabelTTF
class CC_DLL CCMenuItemLabel : public CCMenuItem
{
    /** the color that will be used to disable the item */
    // 菜单不在使用的颜色
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tDisabledColor, DisabledColor);
    /** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol */
    // 呈现标签
    CC_PROPERTY(CCNode*, m_pLabel, Label);
public:
    CCMenuItemLabel()
    : m_pLabel(NULL)
    , m_fOriginalScale(0.0)
    {}
    virtual ~CCMenuItemLabel();

    /** creates a CCMenuItemLabel with a Label, target and selector */
    // 使用标签，目标，选择器为参数创建
    static CCMenuItemLabel * create(CCNode*label, CCObject* target, SEL_MenuHandler selector);
    /** creates a CCMenuItemLabel with a Label. Target and selector will be nil */
    // 只使用标签来创建
    static CCMenuItemLabel* create(CCNode *label);

    /** initializes a CCMenuItemLabel with a Label, target and selector */
    // 使用标签，目标，选择器初始化
    bool initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector);
    /** sets a new string to the inner label */
    // 设置标签字符串
    void setString(const char * label);
    // super methods
    // 父类方法
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    /** Enable or disabled the CCMenuItemFont
     @warning setEnabled changes the RGB color of the font
     */
    // 开启；可能会改变字体颜色
    virtual void setEnabled(bool enabled);
    
protected:
    ccColor3B    m_tColorBackup;
    float        m_fOriginalScale;
};


/** @brief A CCMenuItemAtlasFont
 Helper class that creates a MenuItemLabel class with a LabelAtlas
 */
// 使用LabelAtlas场景菜单项
class CC_DLL CCMenuItemAtlasFont : public CCMenuItemLabel
{
public:
    CCMenuItemAtlasFont(){}
    virtual ~CCMenuItemAtlasFont(){}
    
    /** creates a menu item from a string and atlas with a target/selector */
    // 创建菜单项，使用字符串和目标，选择器为参数
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** creates a menu item from a string and atlas. Use it with MenuItemToggle */
    // 创建菜单项，使用字符串，atlas为参数
    static CCMenuItemAtlasFont* create(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
    /** initializes a menu item from a string and atlas with a target/selector */
    // 初始化菜单项，使用字符串和目标，选择器为参数
    bool initWithString(const char *value, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap, CCObject* target, SEL_MenuHandler selector);
};


/** @brief A CCMenuItemFont
 Helper class that creates a CCMenuItemLabel class with a Label
 */
// 菜单项字体
class CC_DLL CCMenuItemFont : public CCMenuItemLabel
{
public:
    CCMenuItemFont() : m_uFontSize(0), m_strFontName(""){}
    virtual ~CCMenuItemFont(){}
    /** set default font size */
    // 设置默认字体大小
    static void setFontSize(unsigned int s);
    /** get default font size */
    // 获取字体大小
    static unsigned int fontSize();
    /** set the default font name */
    // 设置默认字体名称
    static void setFontName(const char *name);
    /** get the default font name */
    // 获取字体名称
    static const char *fontName();

    /** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle */
    // 创建菜单项，使用字符串为参数
    static CCMenuItemFont * create(const char *value);
    /** creates a menu item from a string with a target/selector */
    // 创建菜单项使用字符串，目标，选择器为参数
    static CCMenuItemFont * create(const char *value, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item from a string with a target/selector */
    // 初始化菜单项，使用字符串，目标，选择器为参数
    bool initWithString(const char *value, CCObject* target, SEL_MenuHandler selector);
    
    /** set font size
     * c++ can not overload static and non-static member functions with the same parameter types
     * so change the name to setFontSizeObj
     */
    // 设置字体大小，c++不能重装静态非静态成员函数；相同参数类型时，使用setFontSizeObj方法
    void setFontSizeObj(unsigned int s);
    
    /** get font size */
    // 获取字体大小
    unsigned int fontSizeObj();
    
    /** set the font name 
     * c++ can not overload static and non-static member functions with the same parameter types
     * so change the name to setFontNameObj
     */
    // 设置字体名称
    void setFontNameObj(const char* name);
    
    const char* fontNameObj();
    
protected:
    void recreateLabel();
    
    unsigned int m_uFontSize;
    std::string m_strFontName;
};


/** @brief CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 @since v0.8.0
 */
// 接受颜色协议对象作为条目；图片有三种状态：未选中，选中，不可编辑
class CC_DLL CCMenuItemSprite : public CCMenuItem
{
    /** the image used when the item is not selected */
    // 图片使用，未选中
    CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
    /** the image used when the item is selected */
    // 图片被选中
    CC_PROPERTY(CCNode*, m_pSelectedImage, SelectedImage);
    /** the image used when the item is disabled */
    // 条目不可编辑
    CC_PROPERTY(CCNode*, m_pDisabledImage, DisabledImage);
public:
    CCMenuItemSprite()
    :m_pNormalImage(NULL)
    ,m_pSelectedImage(NULL)
    ,m_pDisabledImage(NULL)
    {}

    /** creates a menu item with a normal, selected and disabled image*/
    // 创建一个菜单项，使用正常，选中，不可编辑图片为参数
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector */
    // 创建菜单项，使用正常，选中，目标，选择器为参数
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    // 创建菜单项，使用正常，选中，不能编辑图片，目标，选择器为参数
    static CCMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    // 初始化菜单项，使用正常，选中，不能编辑图片，目标，选择器为参数
    bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    
    /**
     @since v0.99.5
     */
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled);
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
protected:
    virtual void updateImagesVisibility();
};


/** @brief CCMenuItemImage accepts images as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
 
 For best results try that all images are of the same size
 */
// 接收图片为条目的菜单项：图片有三种状态：未选中，选中，不可编辑； 最好所有图片具有相同大小
class CC_DLL CCMenuItemImage : public CCMenuItemSprite
{
public:
    CCMenuItemImage(){}
    virtual ~CCMenuItemImage(){}
    
    /** creates a menu item with a normal and selected image*/
    // 创建菜单项，使用正常，选中图片为参数
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    // 创建菜单项，使用正常，选中，不能编辑图片为参数
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector */
    // 创建菜单项，使用正常，选中图片，目标，选择器为参数
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    // 创建菜单项，使用正常，选中，不能编辑图片，目标，选择器为参数
    static CCMenuItemImage* create(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    
    bool init();
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    // 初始化菜单项，使用正常，选中，不能编辑图片，目标，选择器为参数
    bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    /** sets the sprite frame for the normal image */
    // 设置正常图片
    void setNormalSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the selected image */
    // 设置选中图片
    void setSelectedSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the disabled image */
    // 设置不可编辑图片
    void setDisabledSpriteFrame(CCSpriteFrame* frame);

    /** Creates an CCMenuItemImage.
     */
    // 创建方法
    static CCMenuItemImage* create();
};


/** @brief A CCMenuItemToggle
 A simple container class that "toggles" it's inner items
 The inner items can be any MenuItem
 */
// 切换菜单项
class CC_DLL CCMenuItemToggle : public CCMenuItem
{
    /** returns the selected item */
    // 返回选中项
    CC_PROPERTY(unsigned int, m_uSelectedIndex, SelectedIndex);
    /** CCMutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
     @since v0.7.2
     */
    // 数组中含有子项，可以增加，删除，在运行时；也可以替换
    CC_PROPERTY(CCArray*, m_pSubItems, SubItems);
public:
    CCMenuItemToggle()
    : m_uSelectedIndex(0)
    , m_pSubItems(NULL)            
    {}
    virtual ~CCMenuItemToggle();

    /** creates a menu item from a list of items with a target/selector */
    // 创建菜单项，使用链表项，目标，选择器为参数
    static CCMenuItemToggle* createWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, ...);  

    /** creates a menu item with no target/selector and no items */
    // 创建方法
    static CCMenuItemToggle* create();

    /** initializes a menu item from a list of items with a target selector */
    // 初始化菜单项，使用链表条目，目标，选择器为参数
    bool initWithTarget(CCObject* target, SEL_MenuHandler selector, CCMenuItem* item, va_list args);

    /** creates a menu item with a item */
    // 使用一个条目创建菜单项
    static CCMenuItemToggle* create(CCMenuItem *item);

    /** initializes a menu item with a item */
    // 使用一个条目初始化菜单项
    bool initWithItem(CCMenuItem *item);
    /** add more menu item */
    // 增加方法
    void addSubItem(CCMenuItem *item);
    
    /** return the selected item */
    // 返回选中项
    CCMenuItem* selectedItem();
    // super methods
    // 父类方法
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool var);
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCMENU_ITEM_H__
