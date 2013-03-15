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
#ifndef __CCMENU_H_
#define __CCMENU_H_

#include "CCMenuItem.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu     菜单
 * @{
 */
typedef enum  
{
    kCCMenuStateWaiting,
    kCCMenuStateTrackingTouch
} tCCMenuState;

enum {
    //* priority used by the menu for the event handler
    // 菜单使用优先级
    kCCMenuHandlerPriority = -128,
};

/** @brief A CCMenu
* 
* Features and Limitation:
*  - You can add MenuItem objects in runtime using addChild:
*  - But the only accepted children are MenuItem objects
*/
// 菜单，特征和限制：可以增加菜单项，在运行时；只能接受MenuItem对象
class CC_DLL CCMenu : public CCLayerRGBA
{
    /** whether or not the menu will receive events */
    // 是否接收事件
    bool m_bEnabled;
    
public:
    CCMenu() : m_pSelectedItem(NULL) {}
    virtual ~CCMenu(){}

    /** creates an empty CCMenu */
    // 创建一个空菜单
    static CCMenu* create();

    /** creates a CCMenu with CCMenuItem objects */
    // 使用菜单项创建菜单
    static CCMenu* create(CCMenuItem* item, ...);

    /** creates a CCMenu with a CCArray of CCMenuItem objects */
    // 创建菜单，使用菜单项数组为参数
    static CCMenu* createWithArray(CCArray* pArrayOfItems);

    /** creates a CCMenu with it's item, then use addChild() to add 
      * other items. It is used for script, it can't init with undetermined
      * number of variables.
    */
    // 创建菜单，使用菜单项为参数
    static CCMenu* createWithItem(CCMenuItem* item);
    
    /** creates a CCMenu with CCMenuItem objects */
    // 创建菜单，使用菜单项对象为参数
    static CCMenu* createWithItems(CCMenuItem *firstItem, va_list args);

    /** initializes an empty CCMenu */
    // 初始化空菜单
    bool init();

    /** initializes a CCMenu with a NSArray of CCMenuItem objects */
    // 初始化菜单，使用菜单项数组为参数
    bool initWithArray(CCArray* pArrayOfItems);

    /** align items vertically */
    // 对齐方式为垂直
    void alignItemsVertically();
    /** align items vertically with padding
    @since v0.7.2
    */
    // 垂直对齐，填充
    void alignItemsVerticallyWithPadding(float padding);

    /** align items horizontally */
    // 水平对齐项
    void alignItemsHorizontally();
    /** align items horizontally with padding
    @since v0.7.2
    */
    // 水平对齐，填充
    void alignItemsHorizontallyWithPadding(float padding);

    /** align items in rows of columns */
    // 对齐以行
    void alignItemsInColumns(unsigned int columns, ...);
    void alignItemsInColumns(unsigned int columns, va_list args);
    void alignItemsInColumnsWithArray(CCArray* rows);

    /** align items in columns of rows */
    // 对齐项以列为方式
    void alignItemsInRows(unsigned int rows, ...);
    void alignItemsInRows(unsigned int rows, va_list args);
    void alignItemsInRowsWithArray(CCArray* columns);

    /** set event handler priority. By default it is: kCCMenuTouchPriority */
    // 设置事件处理优先级
    void setHandlerPriority(int newPriority);

    //super methods
    // 父类方法
    virtual void addChild(CCNode * child);
    virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode * child, int zOrder, int tag);
    virtual void registerWithTouchDispatcher();
    virtual void removeChild(CCNode* child, bool cleanup);

    /**
    @brief For phone event handle functions
    */
    // 触摸处理
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

    /**
    @since v0.99.5
    override onExit
    */
    // 重载退出
    virtual void onExit();

    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    virtual bool isEnabled() { return m_bEnabled; }
    virtual void setEnabled(bool value) { m_bEnabled = value; };

protected:
    CCMenuItem* itemForTouch(CCTouch * touch);
    tCCMenuState m_eState;
    CCMenuItem *m_pSelectedItem;
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif//__CCMENU_H_
