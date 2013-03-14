/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
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

#ifndef __PLATFORM_CCNODE_H__
#define __PLATFORM_CCNODE_H__

#include "ccMacros.h"
#include "cocoa/CCAffineTransform.h"
#include "cocoa/CCArray.h"
#include "CCGL.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCGLProgram.h"
#include "kazmath/kazmath.h"
#include "script_support/CCScriptSupport.h"
#include "CCProtocols.h"

NS_CC_BEGIN

class CCCamera;
class CCGridBase;
class CCPoint;
class CCTouch;
class CCAction;
class CCRGBAProtocol;
class CCLabelProtocol;
class CCScheduler;
class CCActionManager;

/**
 * @addtogroup base_nodes	基本节点
 * @{
 */

enum {
    kCCNodeTagInvalid = -1,
};

enum {
    kCCNodeOnEnter,
    kCCNodeOnExit,
    kCCNodeOnEnterTransitionDidFinish,
    kCCNodeOnExitTransitionDidStart,
    kCCNodeOnCleanup
};

/** @brief CCNode is the main element. Anything that gets drawn or contains things that get drawn is a CCNode.
 The most popular CCNodes are: CCScene, CCLayer, CCSprite, CCMenu.

 The main features of a CCNode are:
 - They can contain other CCNode nodes (addChild, getChildByTag, removeChild, etc)
 - They can schedule periodic callback (schedule, unschedule, etc)
 - They can execute actions (runAction, stopAction, etc)

 Some CCNode nodes provide extra functionality for them or their children.

 Subclassing a CCNode usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding draw to render the node

 Features of CCNode:
 - position
 - scale (x, y)
 - rotation (in degrees, clockwise)
 - CCCamera (an interface to gluLookAt )
 - CCGridBase (to do mesh transformations)
 - anchor point
 - size
 - visible
 - z-order
 - openGL z position

 Default values:
 - rotation: 0
 - position: (x=0,y=0)
 - scale: (x=1,y=1)
 - contentSize: (x=0,y=0)
 - anchorPoint: (x=0,y=0)

 Limitations:
 - A CCNode is a "void" object. It doesn't have a texture

 Order in transformations with grid disabled
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be scaled (scale)
 -# The node will be moved according to the camera values (camera)

 Order in transformations with grid enabled
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be scaled (scale)
 -# The grid will capture the screen
 -# The node will be moved according to the camera values (camera)
 -# The grid will render the captured screen

 Camera:
 - Each node has a camera. By default it points to the center of the CCNode.
 */
/**
 * 节点是主要元素。任何对象都可以是一个节点。主要或常用的场景类，层类，精灵，菜单类都是从节点继承而来
 * 节点的主要特征：可以还有其他节点（增加子类或删除）；可以进行定期回调;可以执行动作(如运行,停止等)
 * 一些节点可以提供附加功能. 如子类可以具有重载初始化资源和回调,可以回调处理时间,重画;
 * 节点的特征:位置,缩放比例,旋转,摄像,网格,锚点,大小,可见性,z轴次序,opengl z轴位置
 * 限制:节点可以是任意对象。不具有纹理;不可编辑的网格转换：节点可以具有转换，旋转，倾斜，缩放，摄像
 * 可编辑网格中时：节点具有转换，旋转，倾斜，缩放，摄像，捕捉屏幕，呈现
 * 每个节点都有一个摄像。默认为节点的中心位置
 */

class CC_DLL CCNode : public CCObject
{
public:
    //////////////////////////////
    /// @{
    /// @name Constructor, Distructor and Initializers
    
    /**
     * Default constructor
     */
    // 默认构造
    CCNode(void);
    
    /**
     * Default destructor
     */
    // 析构
    virtual ~CCNode(void);
    
    /**
     *  Initializes the instance of CCNode
     *  @return Whether the initialization was successful.
     */
    // 初始化
    virtual bool init();
	/**
     * Allocates and initializes a node.
     * @return A initialized node which is marked as "autorelease".
     */
    // 分配和初始化一个节点，返回值具有自动释放
    static CCNode * create(void);
    
    /**
     * Gets the description string. It makes debugging easier.
     * @return A string terminated with '\0'
     */
    // 描述方法
    const char* description(void);
    
    /// @} end of initializers
    /// 结束初始化
    
    
    
    ///////////////////////////////////////////////////////
    /// @{
    /// @name Setters & Getters for Graphic Peroperties
    
    /**
     * Sets the Z order which stands for the drawing order, and reorder this node in its parent's children array.
     *
     * The Z order of node is relative to its "brothers": children of the same parent.
     * It's nothing to do with OpenGL's z vertex. This one only affects the draw order of nodes in cocos2d.
     * The larger number it is, the later this node will be drawn in each message loop.
     * Please refer to setVertexZ(float) for the difference.
     *
     * @param nZOrder   Z order of this node.
     */
    // 设置z次序：相对于父类，兄弟之间的次序
    virtual void setZOrder(int zOrder);
    /**
     * Sets the z order which stands for the drawing order
     *
     * This is an internal method. Don't call it outside the framework.
     * The difference between setZOrder(int) and _setOrder(int) is:
     * - _setZOrder(int) is a pure setter for m_nZOrder memeber variable
     * - setZOrder(int) firstly changes m_nZOrder, then recorder this node in its parent's chilren array.
     */
    // 设置z次序，就是绘制循序
    virtual void _setZOrder(int z);
    /**
     * Gets the Z order of this node.
     *
     * @see setZOrder(int)
     *
     * @return The Z order.
     */
    // 获取z次序
    virtual int getZOrder();


    /**
     * Sets the real OpenGL Z vertex.
     *
     * Differences between openGL Z vertex and cocos2d Z order:
     * - OpenGL Z modifies the Z vertex, and not the Z order in the relation between parent-children
     * - OpenGL Z might require to set 2D projection
     * - cocos2d Z order works OK if all the nodes uses the same openGL Z vertex. eg: vertexZ = 0
     *
     * @warning Use it at your own risk since it might break the cocos2d parent-children z order
     *
     * @param fVertexZ  OpenGL Z vertex of this node.
     */
    // 设置真实opengl z顶点：
    /* opengl z顶点与 cocos2d的z次序不同
    opengl修改z 顶点，而z 次序没有影响；opengl的z 可能要求设置2d投影。 
    如果所有节点都设置相同的opengl的z 顶点，如vertexZ = 0;可以正常工作
    注意：使用此，可能打破cocos2d父子的z次序
    */
    virtual void setVertexZ(float vertexZ);
    /**
     * Gets OpenGL Z vertex of this node.
     *
     * @see setVertexZ(float)
     *
     * @return OpenGL Z vertex of this node
     */
    // 获取opengl的z 顶点
    virtual float getVertexZ();


    /**
     * Changes the scale factor on X axis of this node
     *
     * The deafult value is 1.0 if you haven't changed it before
     *
     * @param fScaleX   The scale factor on X axis.
     */
    // 改变这个节点X轴的比例因子
    virtual void setScaleX(float fScaleX);
    /**
     * Returns the scale factor on X axis of this node
     *
     * @see setScaleX(float)
     *
     * @return The scale factor on X axis.
     */
    // 获取这个节点X轴的比例因子
    virtual float getScaleX();

    
    /**
     * Changes the scale factor on Y axis of this node
     *
     * The Default value is 1.0 if you haven't changed it before.
     *
     * @param fScaleY   The scale factor on Y axis.
     */
    // 改变这个节点Y轴的比例因子
    virtual void setScaleY(float fScaleY);
    /**
     * Returns the scale factor on Y axis of this node
     *
     * @see setScaleY(float)
     *
     * @return The scale factor on Y axis. 
     */
    // 获取这个节点Y轴的比例因子
    virtual float getScaleY();

    
    /**
     * Changes both X and Y scale factor of the node.
     *
     * 1.0 is the default scale factor. It modifies the X and Y scale at the same time.
     *
     * @param scale     The scale factor for both X and Y axis.
     */
    // 改变这个节点X,Y轴的比例因子
    virtual void setScale(float scale);
    /**
     * Gets the scale factor of the node,  when X and Y have the same scale factor.
     *
     * @warning Assert when m_fScaleX != m_fScaleY.
     * @see setScale(float)
     *
     * @return The scale factor of the node.
     */
    // 获取这个节点X,y轴的比例因子,x,y具有相同的比例
    virtual float getScale();
    
    
    /**
     * Changes the position (x,y) of the node in OpenGL coordinates
     *
     * Usually we use ccp(x,y) to compose CCPoint object.
     * The original point (0,0) is at the left-bottom corner of screen.
     * For example, this codesnip sets the node in the center of screen.
     * @code
     * CCSize size = CCDirector::sharedDirector()->getWinSize();
     * node->setPosition( ccp(size.width/2, size.height/2) )
     * @endcode
     *
     * @param position  The position (x,y) of the node in OpenGL coordinates
     */
    // 设置位置，在opengl的坐标系中
    virtual void setPosition(const CCPoint &position);
    /**
     * Gets the position (x,y) of the node in OpenGL coordinates
     * 
     * @see setPosition(const CCPoint&)
     *
     * @return The position (x,y) of the node in OpenGL coordinates
     */
    // 获取节点的位置，在opengl坐标系
    virtual const CCPoint& getPosition();
    /**
     * Sets position in a more efficient way.
     *
     * Passing two numbers (x,y) is much efficient than passing CCPoint object.
     * This method is binded to lua and javascript. 
     * Passing a number is 10 times faster than passing a object from lua to c++
     *
     * @code
     * // sample code in lua
     * local pos  = node::getPosition()  -- returns CCPoint object from C++
     * node:setPosition(x, y)            -- pass x, y coordinate to C++
     * @endcode
     *
     * @param x     X coordinate for position
     * @param y     Y coordinate for position
     */
    // 使用x,y来设置节点位置
    void setPosition(float x, float y);
    /**
     * Gets position in a more efficient way, returns two number instead of a CCPoint object
     *
     * @see setPosition(float, float)
     */
    // 获取节点的位置，参数为x,y
    void getPosition(float* x, float* y);
    /**
     * Gets/Sets x or y coordinate individually for position.
     * These methods are used in Lua and Javascript Bindings
     */
    // 设置，获取x,y位置，用在lua和javascript绑定中
    void  setPositionX(float x);
    float getPositionX(void);
    void  setPositionY(float y);
    float getPositionY(void);
    
    
    /**
     * Changes the X skew angle of the node in degrees.
     *
     * This angle describes the shear distortion in the X direction.
     * Thus, it is the angle between the Y axis and the left edge of the shape
     * The default skewX angle is 0. Positive values distort the node in a CW direction.
     *
     * @param fSkewX The X skew angle of the node in degrees.
     */
    // 设置节点x轴倾斜的角度，以角度为单位
    virtual void setSkewX(float fSkewX);
    /**
     * Returns the X skew angle of the node in degrees.
     *
     * @see setSkewX(float)
     *
     * @return The X skew angle of the node in degrees.
     */
    // 获取节点x轴倾斜的角度，以角度为单位
    virtual float getSkewX();

    
    /**
     * Changes the Y skew angle of the node in degrees.
     *
     * This angle describes the shear distortion in the Y direction.
     * Thus, it is the angle between the X axis and the bottom edge of the shape
     * The default skewY angle is 0. Positive values distort the node in a CCW direction.
     *
     * @param fSkewY    The Y skew angle of the node in degrees.
     */
    // 设置节点y轴倾斜的角度，以角度为单位
    virtual void setSkewY(float fSkewY);
    /**
     * Returns the Y skew angle of the node in degrees.
     *
     * @see setSkewY(float)
     *
     * @return The Y skew angle of the node in degrees.
     */
    // 获取节点y轴倾斜的角度，以角度为单位
    virtual float getSkewY();

    
    /**
     * Sets the anchor point in percent.
     *
     * anchorPoint is the point around which all transformations and positioning manipulations take place.
     * It's like a pin in the node where it is "attached" to its parent.
     * The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
     * But you can use values higher than (1,1) and lower than (0,0) too.
     * The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
     *
     * @param anchorPoint   The anchor point of node.
     */
    // 设置锚点，以百分数为单位。 通常锚点为几何图形的中心点
    virtual void setAnchorPoint(const CCPoint& anchorPoint);
    /** 
     * Returns the anchor point in percent.
     *
     * @see setAnchorPoint(const CCPoint&)
     *
     * @return The anchor point of node.
     */
    // 获取锚点，以百分数为单位
    virtual const CCPoint& getAnchorPoint();
    /**
     * Returns the anchorPoint in absolute pixels.
     * 
     * @warning You can only read it. If you wish to modify it, use anchorPoint instead.
     * @see getAnchorPoint()
     *
     * @return The anchor point in absolute pixels.
     */
    // 获取锚点，以像素为单位
    virtual const CCPoint& getAnchorPointInPoints();
    
    
    /**
     * Sets the untransformed size of the node.
     *
     * The contentSize remains the same no matter the node is scaled or rotated.
     * All nodes has a size. Layer and Scene has the same size of the screen.
     *
     * @param contentSize   The untransformed size of the node.
     */
    // 设置节点大小。未转化参数
    virtual void setContentSize(const CCSize& contentSize);
    /**
     * Returns the untransformed size of the node.
     *
     * @see setContentSize(const CCSize&)
     *
     * @return The untransformed size of the node.
     */
    // 获取节点大小
    virtual const CCSize& getContentSize();

    
    /**
     * Sets whether the node is visible
     *
     * The default value is true, a node is default to visible
     *
     * @param visible   true if the node is visible, false if the node is hidden.
     */
    // 设置可见性
    virtual void setVisible(bool visible);
    /**
     * Determines if the node is visible
     *
     * @see setVisible(bool)
     *
     * @return true if the node is visible, false if the node is hidden.
     */
    // 是否可见，节点
    virtual bool isVisible();

    
    /** 
     * Sets the rotation (angle) of the node in degrees. 
     * 
     * 0 is the default rotation angle. 
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * 
     * @param fRotation     The roration of the node in degrees.
     */
    // 设置节点旋转角度，以角度为单位
    virtual void setRotation(float fRotation);
    /**
     * Returns the rotation of the node in degrees.
     *
     * @see setRotation(float)
     *
     * @return The rotation of the node in degrees.
     */
    // 获取旋转角度
    virtual float getRotation();

    
    /** 
     * Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.
     * 
     * 0 is the default rotation angle. 
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * 
     * @param fRotationX    The X rotation in degrees which performs a horizontal rotational skew.
     */
    // 设置节点x轴旋转角度，以角度为单位
    virtual void setRotationX(float fRotaionX);
    /**
     * Gets the X rotation (angle) of the node in degrees which performs a horizontal rotation skew.
     *
     * @see setRotationX(float)
     *
     * @return The X rotation in degrees.
     */
    // 获取节点x轴旋转角度
    virtual float getRotationX();

    
    /** 
     * Sets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     * 
     * 0 is the default rotation angle. 
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     *
     * @param fRotationY    The Y rotation in degrees.
     */
    // 设置节点y轴旋转角度，以角度为单位
    virtual void setRotationY(float fRotationY);
    /**
     * Gets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     *
     * @see setRotationY(float)
     *
     * @return The Y rotation in degrees.
     */
    // 获取节点y轴旋转角度
    virtual float getRotationY();

    
    /**
     * Sets the arrival order when this node has a same ZOrder with other children.
     *
     * A node which called addChild subsequently will take a larger arrival order,
     * If two children have the same Z order, the child with larger arrival order will be drawn later.
     *
     * @warning This method is used internally for zOrder sorting, don't change this manually
     *
     * @param uOrderOfArrival   The arrival order.
     */
    // 设置到达节点顺序，当节点具有相同的z次序时。不用手动管理
    virtual void setOrderOfArrival(unsigned int uOrderOfArrival);
    /**
     * Returns the arrival order, indecates which children is added previously.
     *
     * @see setOrderOfArrival(unsigned int)
     *
     * @return The arrival order.
     */
    // 获取节点到达顺序
    virtual unsigned int getOrderOfArrival();
    
    
    /**
     * Sets the state of OpenGL server side.
     *
     * @param glServerState     The state of OpenGL server side.
     */
    // 设置gl服务端状态
    virtual void setGLServerState(ccGLServerState glServerState);
    /**
     * Returns the state of OpenGL server side.
     *
     * @return The state of OpenGL server side.
     */
    // 返回服务端服务状态
    virtual ccGLServerState getGLServerState();
    
    
    /**
     * Sets whether the anchor point will be (0,0) when you position this node.
     *
     * This is an internal method, only used by CCLayer and CCScene. Don't call it outside framework.
     * The default value is false, while in CCLayer and CCScene are true
     *
     * @param ignore    true if anchor point will be (0,0) when you position this node
     * @todo This method shoud be renamed as setIgnoreAnchorPointForPosition(bool) or something with "set"
     */
    // 忽视锚点设置，则锚点为默认设置为(0,0)
    virtual void ignoreAnchorPointForPosition(bool ignore);
    /**
     * Gets whether the anchor point will be (0,0) when you position this node.
     *
     * @see ignoreAnchorPointForPosition(bool)
     *
     * @return true if the anchor point will be (0,0) when you position this node.
     */
    // 是否忽视锚点设置
    virtual bool isIgnoreAnchorPointForPosition();
    
    /// @}  end of Setters & Getters for Graphic Peroperties
    /// 设置和获取绘制相关属性
    
    
    ///////////////////////////////////////////////////////
    /// @{
    /// @name Children and Parent
    
    /** 
     * Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child A child node
     */
    // 增加一个子对象，而z次序为0
    virtual void addChild(CCNode * child);
    /** 
     * Adds a child to the container with a z-order
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     */
    // 增加一个带有z次序的对象
    virtual void addChild(CCNode * child, int zOrder);
    /** 
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
     */
    // 增加一个带有z次序和标志的对象
    virtual void addChild(CCNode* child, int zOrder, int tag);
    /**
     * Gets a child from the container with its tag
     *
     * @param tag   An identifier to find the child node.
     *
     * @return a CCNode object whose tag equals to the input parameter
     */
    // 返回一个子对象，使用标志
    CCNode * getChildByTag(int tag);
    /**
     * Return an array of children
     *
     * Composing a "tree" structure is a very important feature of CCNode
     * Here's a sample code of traversing children array:
     * @code
     * CCNode* node = NULL;
     * CCARRAY_FOREACH(parent->getChildren(), node)
     * {
     *     node->setPosition(0,0);
     * }
     * @endcode
     * This sample code traverses all children nodes, and set theie position to (0,0)
     *
     * @return An array of children
     */
    // 返回一组子对象
    virtual CCArray* getChildren();
    
    /** 
     * Get the amount of children.
     *
     * @return The amount of children.
     */
    // 获取子对象的个数
    unsigned int getChildrenCount(void);
    
    /**
     * Sets the parent node
     *
     * @param parent    A pointer to the parnet node
     */
    // 设置父类节点
    virtual void setParent(CCNode* parent);
    /**
     * Returns a pointer to the parent node
     * 
     * @see setParent(CCNode*)
     *
     * @returns A pointer to the parnet node
     */
    // 获取父类节点
    virtual CCNode* getParent();
    
    
    ////// REMOVES //////
    
    /** 
     * Removes this node itself from its parent node with a cleanup.
     * If the node orphan, then nothing happens.
     * @see removeFromParentAndCleanup(bool)
     */
    // 从父类删除节点
    virtual void removeFromParent();
    /** 
     * Removes this node itself from its parent node. 
     * If the node orphan, then nothing happens.
     * @param cleanup   true if all actions and callbacks on this node should be removed, false otherwise.
     */
    // 从父类删除，并清理节点
    virtual void removeFromParentAndCleanup(bool cleanup);
    /** 
     * Removes a child from the container with a cleanup
     *
     * @see removeChild(CCNode, bool)
     *
     * @param child     The child node which will be removed.
     */
    // 删除一个子节点
    virtual void removeChild(CCNode* child);
    /** 
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     * 
     * @param child     The child node which will be removed.
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    // 删除一个子节点，并清理
    virtual void removeChild(CCNode* child, bool cleanup);
    /** 
     * Removes a child from the container by tag value with a cleanup.
     *
     * @see removeChildByTag(int, bool)
     *
     * @param tag       An interger number that identifies a child node
     */
    // 删除一个子节点，使用标志参数
    virtual void removeChildByTag(int tag);
    /** 
     * Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter
     * 
     * @param tag       An interger number that identifies a child node
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise. 
     */
    // 删除一个子节点并清理，使用标志参数
    virtual void removeChildByTag(int tag, bool cleanup);
    /** 
     * Removes all children from the container with a cleanup.
     *
     * @see removeAllChildrenWithCleanup(bool)
     */
    // 删除所有子节点
    virtual void removeAllChildren();
    /** 
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.
     */
    // 删除所有子节点，带有清理参数
    virtual void removeAllChildrenWithCleanup(bool cleanup);
    
    /** 
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     */
    // 用新的z值，重新排序子节点
    virtual void reorderChild(CCNode * child, int zOrder);
    
    /** 
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This appraoch can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame 
     */
    // 对所有子节点排序，在绘制之前
    virtual void sortAllChildren();

    /// @} end of Children and Parent
    /// 结束子与父
    

    
    ////////////////////////////////////
    /// @{
    /// @name Grid object for effects
    
    /**
     * Returns a grid object that is used when applying effects
     * 
     * @return A CCGrid object that is used when applying effects
     */
    // 网格对象； 获取一个网格对象
    virtual CCGridBase* getGrid();
    /**
     * Changes a grid object that is used when applying effects
     *
     * @param A CCGrid object that is used when applying effects
     */
    // 设置一个网格对象，当应用效果时
    virtual void setGrid(CCGridBase *pGrid);
    
    /// @} end of Grid
    /// 结束网格
    
    
    /////////////////////////////////////
    /// @{
    /// @name Tag & User data
    
    /**
     * Returns a tag that is used to identify the node easily.
     *
     * You can set tags to node then identify them easily.
     * @code
     * #define TAG_PLAYER  1
     * #define TAG_MONSTER 2
     * #define TAG_BOSS    3
     * // set tags
     * node1->setTag(TAG_PLAYER);
     * node2->setTag(TAG_MONSTER);
     * node3->setTag(TAG_BOSS);
     * parent->addChild(node1);
     * parent->addChild(node2);
     * parent->addChild(node3);
     * // identify by tags
     * CCNode* node = NULL;
     * CCARRAY_FOREACH(parent->getChildren(), node)
     * {
     *     switch(node->getTag())
     *     {
     *         case TAG_PLAYER:
     *             break;
     *         case TAG_MONSTER:
     *             break;
     *         case TAG_BOSS:
     *             break;
     *     }
     * }
     * @endcode
     *
     * @return A interger that identifies the node.
     */
    // 标志和数据： 获取一个整数标志，来确定节点
    virtual int getTag();
    /**
     * Changes the tag that is used to identify the node easily.
     *
     * Please refer to getTag for the sample code.
     *
     * @param A interger that indentifies the node.
     */
    // 设置标志,确定节点容易
    virtual void setTag(int nTag);
    
    /**
     * Returns a custom user data pointer
     *
     * You can set everything in UserData pointer, a data block, a structure or an object.
     * 
     * @return A custom user data pointer
     */
    // 获取自定义的用户数据，可以是数据指针，数据块，结构体或一个对象
    virtual void* getUserData();
    /**
     * Sets a custom user data pointer
     *
     * You can set everything in UserData pointer, a data block, a structure or an object, etc.
     * @warning Don't forget to release the memroy manually, 
     *          especially before you change this data pointer, and before this node is autoreleased.
     *
     * @return A custom user data pointer
     */
    // 设置一个自定义的用户数据；要手动释放内存
    virtual void setUserData(void *pUserData);
    
    /** 
     * Returns a user assigned CCObject
     * 
     * Similar to userData, but instead of holding a void* it holds an object
     *
     * @return A user assigned CCObject
     */
    // 获取一个对象，与获取数据类似
    virtual CCObject* getUserObject();
    /**
     * Returns a user assigned CCObject
     *
     * Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method,
     * and the previous UserObject (if existed) will be relese.
     * The UserObject will be released in CCNode's destructure.
     *
     * @param A user assigned CCObject
     */
    // 设置一个对象
    virtual void setUserObject(CCObject *pUserObject);
    
    /// @} end of Tag & User Data
    /// 结束标志和用户数据
    
    
    ///////////////////////////////
    /// @{
    /// @name Shader Program
    /**
     * Return the shader program currently used for this node
     * 
     * @return The shader program currelty used for this node
     */
    // 着色方案；获取当前着色
    virtual CCGLProgram* getShaderProgram();
    /**
     * Sets the shader program for this node
     *
     * Since v2.0, each rendering node must set its shader program.
     * It should be set in initialize phase.
     * @code
     * node->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
     * @endcode
     * 
     * @param The shader program which fetchs from CCShaderCache.
     */
    // 设置节点的着色方案
    virtual void setShaderProgram(CCGLProgram *pShaderProgram);
    /// @} end of Shader Program
    /// 结束着色方案
    ///////////////////////////////////////
    ///////////////////////////////////////
    
    /**
     * Returns a camera object that lets you move the node using a gluLookAt
     *
     * @code
     * CCCamera* camera = node->getCamera();
     * camera->setEyeXYZ(0, 0, 415/2);
     * camera->setCenterXYZ(0, 0, 0);
     * @endcode
     *
     * @return A CCCamera object that lets you move the node using a gluLookAt
     */
    // 返回一个摄像对象，而已使用gluLookAt来移动
    virtual CCCamera* getCamera();
    
    /** 
     * Returns whether or not the node accepts event callbacks.
     * 
     * Running means the node accept event callbacks like onEnter(), onExit(), update()
     *
     * @return Whether or not the node is running.
     */
    // 是否在运行中，接收事件回调
    virtual bool isRunning();

    
    /////////////////////////////////
    /// @{
    /// @name Script Bindings for lua

    /**
     * Registers a script function that will be called in onEnter() & onExit() seires functions.
     * 
     * This handler will be removed automatically after onExit() called.
     * @code
     * -- lua sample
     * local function sceneEventHandler(eventType)
     *     if eventType == kCCNodeOnEnter then
     *         -- do something
     *     elseif evetType == kCCNodeOnExit then
     *         -- do something
     *     end
     * end
     * scene::registerScriptHandler(sceneEventHandler)
     * @endcode
     *
     * @warning This method is for internal usage, don't call it manually.
     * @todo Perhaps we should rename it to get/set/removeScriptHandler acoording to the function name style.
     *
     * @param handler   A number that indicates a lua function. 
     */
    // 注册脚本处理，用于lua
    virtual void registerScriptHandler(int handler);
    /**
     * Unregisters a script function that will be called in onEnter() & onExit() series functions.
     *
     * @see registerScriptHandler(int)
     */
    // 取消注册
    virtual void unregisterScriptHandler(void);
    /**
     * Gets script handler for onEnter/onExit event.
     * This is an internal method. g
     * @see registerScriptHandler(int)
     *
     * @return A number that indicates a lua function.
     */
    // 获取脚本处理为onEnter/onExit事件
    inline int getScriptHandler() { return m_nScriptHandler; };
    
    /** 
     * Schedules for lua script. 
     */
    // 附表为lua脚本
    void scheduleUpdateWithPriorityLua(int nHandler, int priority);
    
    /// @}  end Script Bindings
    /// 结束脚本绑定


    //////////////////////////
    /// @{
    /// @name Event Callbacks
    
    /** 
     * Event callback that is invoked every time when CCNode enters the 'stage'.
     * If the CCNode enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., CCNode::onEnter().
     */
    // 事件回调； 节点每次进入的舞台，调用此方法
    virtual void onEnter();

    /** Event callback that is invoked when the CCNode enters in the 'stage'.
     * If the CCNode enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. CCNode::onEnterTransitionDidFinish()
     */
    // 节点回调此方法，使用一个过渡参数
    virtual void onEnterTransitionDidFinish();

    /** 
     * Event callback that is invoked every time the CCNode leaves the 'stage'.
     * If the CCNode leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., CCNode::onExit().
     */
    // 当节点离开舞台时
    virtual void onExit();

    /** 
     * Event callback that is called every time the CCNode leaves the 'stage'.
     * If the CCNode leaves the 'stage' with a transition, this callback is called when the transition starts.
     */
    // 节点离开舞台时，每次都调用
    virtual void onExitTransitionDidStart();

    /// @} end of event callbacks.
    /// 结束事件回调


    /** 
     * Stops all running actions and schedulers
     */
    // 停止所有运行动作和调度
    virtual void cleanup(void);

    /** 
     * Override this method to draw your own node.
     * The following GL states will be enabled by default:
     * - glEnableClientState(GL_VERTEX_ARRAY);
     * - glEnableClientState(GL_COLOR_ARRAY);
     * - glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     * - glEnable(GL_TEXTURE_2D);
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     */
    // 重载此方法来绘制自己
    virtual void draw(void);

    /** 
     * Visits this node's children and draw them recursively.
     */
    // 访问节点子对象，并递归绘制
    virtual void visit(void);

    
    /** 
     * Returns a "local" axis aligned bounding box of the node.
     * The returned box is relative only to its parent.
     *
     * @note This method returns a temporaty variable, so it can't returns const CCRect&
     * @todo Rename to getBoundingBox() in the future versions.
     * 
     * @return A "local" axis aligned boudning box of the node.
     */
    // 返回节点边界
    CCRect boundingBox(void);

    /////////////////////////////////////////
    /// @{
    /// @name Actions

    /**
     * Sets the CCActionManager object that is used by all actions.
     *
     * @warning If you set a new CCActionManager, then previously created actions will be removed.
     *
     * @param actionManager     A CCActionManager object that is used by all actions.
     */
    // 设置运动管理对象，用于管理所有运动
    virtual void setActionManager(CCActionManager* actionManager);
    /**
     * Gets the CCActionManager object that is used by all actions.
     * @see setActionManager(CCActionManager*)
     * @return A CCActionManager object.
     */
    // 获取运动管理对象
    virtual CCActionManager* getActionManager();
    
    /** 
     * Executes an action, and returns the action that is executed.
     *
     * This node becomes the action's target. Refer to CCAction::getTarget()
     * @warning Actions don't retain their target.
     *
     * @return An Action pointer
     */
    // 返回执行的运行
    CCAction* runAction(CCAction* action);

    /** 
     * Stops and removes all actions from the running action list .
     */
    // 从运行链表中停止和移除所有动作
    void stopAllActions(void);

    /** 
     * Stops and removes an action from the running action list.
     *
     * @param An action object to be removed.
     */
    // 停止和移除一个动作
    void stopAction(CCAction* action);

    /** 
     * Removes an action from the running action list by its tag.
     *
     * @param A tag that indicates the action to be removed.
     */
    // 停止指定标志的动作，从链表中
    void stopActionByTag(int tag);

    /** 
     * Gets an action from the running action list by its tag.
     *
     * @see setTag(int), getTag().
     *
     * @return The action object with the given tag.
     */
    // 获取带有标志的动作
    CCAction* getActionByTag(int tag);

    /** 
     * Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).
     *
     * Composable actions are counted as 1 action. Example:
     *    If you are running 1 Sequence of 7 actions, it will return 1.
     *    If you are running 7 Sequences of 2 actions, it will return 7.
     * @todo Rename to getNumberOfRunningActions()
     *
     * @return The number of actions that are running plus the ones that are schedule to run
     */
    // 运行中的动作数目
    unsigned int numberOfRunningActions(void);

    /// @} end of Actions
    /// 结束动作
    
    
    //////////////////
    /// @{
    /// @name Scheduler and Timer

    /**
     * Sets a CCScheduler object that is used to schedule all "updates" and timers.
     *
     * @warning If you set a new CCScheduler, then previously created timers/update are going to be removed.
     * @param scheduler     A CCShdeduler object that is used to schedule all "update" and timers.
     */
    // 调度和计数器; 设置调度
    virtual void setScheduler(CCScheduler* scheduler);
    /**
     * Gets a CCSheduler object.
     *
     * @see setScheduler(CCScheduler*)
     * @return A CCScheduler object.
     */
    // 获取调度对象
    virtual CCScheduler* getScheduler();
    
    /** 
     * Checks whether a selector is scheduled.
     *
     * @param selector      A function selector
     * @return Whether the funcion selector is scheduled.
     */
    // 选择器是否被调度
    bool isScheduled(SEL_SCHEDULE selector);

    /** 
     * Schedules the "update" method. 
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     */
    // 调用更新方法；每帧都会调用
    void scheduleUpdate(void);

    /** 
     * Schedules the "update" method with a custom priority. 
     *
     * This selector will be called every frame.
     * Scheduled methods with a lower priority will be called before the ones that have a higher value.
     * Only one "update" selector could be scheduled per node (You can't have 2 'update' selectors).
     */
    // 使用优先级调用更新方法
    void scheduleUpdateWithPriority(int priority);

    /* 
     * Unschedules the "update" method.
     * @see scheduleUpdate();
     */
    // 取消更新
    void unscheduleUpdate(void);

    /**
     * Schedules a custom selector.
     *
     * If the selector is already scheduled, then the interval parameter will be updated without scheduling it again.
     * @code
     * // firstly, implement a schedule function
     * void MyNode::TickMe(float dt);
     * // wrap this function into a selector via schedule_selector marco.
     * this->schedule(schedule_selector(MyNode::TickMe), 0, 0, 0);
     * @endcode
     *
     * @param interval  Tick interval in seconds. 0 means tick every frame. If interval = 0, it's recommended to use scheduleUpdate() instead.
     * @param repeat    The selector will be excuted (repeat + 1) times, you can use kCCRepeatForever for tick infinitely.
     * @param delay     The amount of time that the first tick will wait before execution.
     */
    // 注册一个自定义选择器：选择器，时间间隔，重复次数，延时为参数
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);
    
    /**
     * Schedules a custom selector with an interval time in seconds.
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     * @param interval      Callback interval time in seconds. 0 means tick every frame,
     */
    // 注册一个选择器，使用时间间隔
    void schedule(SEL_SCHEDULE selector, float interval);
    
    /**
     * Schedules a selector that runs only once, with a delay of 0 or larger
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     * @param delay         The amount of time that the first tick will wait before execution.
     */
    // 注册一个只运行一次的选择器，用延时参数
    void scheduleOnce(SEL_SCHEDULE selector, float delay);
    
    /**
     * Schedules a custom selector, the scheduled selector will be ticked every frame
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     */
    // 注册一个自定义选择器
    void schedule(SEL_SCHEDULE selector);
    
    /** 
     * Unschedules a custom selector.
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     */
    // 取消注册
    void unschedule(SEL_SCHEDULE selector);

    /** 
     * Unschedule all scheduled selectors: custom selectors, and the 'update' selector.
     * Actions are not affected by this method.
     */
    // 取消所有选择器
    void unscheduleAllSelectors(void);

    /** 
     * Resumes all scheduled selectors and actions.
     * This method is called internally by onEnter
     */
    // 恢复所有注册选择器和动作
    void resumeSchedulerAndActions(void);
    /** 
     * Pauses all scheduled selectors and actions.
     * This method is called internally by onExit
     */
    // 暂停所有选择器和动作
    void pauseSchedulerAndActions(void);
    
    /* 
     * Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
     */
    // 更新方法，会被每帧自动调用
    virtual void update(float delta);
    

    ////////////////////////////
    /// @{
    /// @name Transformations
    
    /**
     * Performs OpenGL view-matrix transformation based on position, scale, rotation and other attributes.
     */
    // 转换；基于位置，比例，旋转和其他属性
    void transform(void);
    /**
     * Performs OpenGL view-matrix transformation of it's ancestors.
     * Generally the ancestors are already transformed, but in certain cases (eg: attaching a FBO)
     * It's necessary to transform the ancestors again.
     */
    // 从祖先那里执行opengl矩阵转换
    void transformAncestors(void);
    /**
     * Calls children's updateTransform() method recursively.
     *
     * This method is moved from CCSprite, so it's no longer specific to CCSprite.
     * As the result, you apply CCSpriteBatchNode's optimization on your customed CCNode.
     * e.g., batchNode->addChild(myCustomNode), while you can only addChild(sprite) before.
     */
    // 更新转换，是调用子对象的方法
    virtual void updateTransform(void);
    
    /** 
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     */
    // 返回的矩阵：从节点空间坐标转换父类空间坐标； 矩阵是以像素为单位
    virtual CCAffineTransform nodeToParentTransform(void);

    /** 
     * Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     */
    // 从父类到子类转换
    virtual CCAffineTransform parentToNodeTransform(void);

    /** 
     * Returns the world affine transform matrix. The matrix is in Pixels.
     */
    // 返回一个世界放射转换矩阵；矩阵以像素为单位
    virtual CCAffineTransform nodeToWorldTransform(void);

    /** 
     * Returns the inverse world affine transform matrix. The matrix is in Pixels.
     */
    // 返回一个反向的矩形
    virtual CCAffineTransform worldToNodeTransform(void);

    /// @} end of Transformations
    /// 结束转换
    
    
    ///////////////////
    /// @{
    /// @name Coordinate Converters
    
    /** 
     * Converts a Point to node (local) space coordinates. The result is in Points.
     */
    //坐标系转换； 从点到节点空间坐标
    CCPoint convertToNodeSpace(const CCPoint& worldPoint);
    
    /** 
     * Converts a Point to world space coordinates. The result is in Points.
     */
    // 从点到世界空间坐标。结果以点为单位
    CCPoint convertToWorldSpace(const CCPoint& nodePoint);
    
    /** 
     * Converts a Point to node (local) space coordinates. The result is in Points.
     * treating the returned/received node point as anchor relative.
     */
    // 点到节点本地空间坐标系 作为锚点
    CCPoint convertToNodeSpaceAR(const CCPoint& worldPoint);
    
    /** 
     * Converts a local Point to world space coordinates.The result is in Points.
     * treating the returned/received node point as anchor relative.
     */
    // 本地点到世界空间坐标系。 该点作为一个锚点相对来说
    CCPoint convertToWorldSpaceAR(const CCPoint& nodePoint);

    /** 
     * convenience methods which take a CCTouch instead of CCPoint
     */
    // 从touch坐标系到节点坐标系
    CCPoint convertTouchToNodeSpace(CCTouch * touch);

    /** 
     * converts a CCTouch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
     */
    // 从touch世界坐标系到本地坐标系。 锚点
    CCPoint convertTouchToNodeSpaceAR(CCTouch * touch);
    
	/**
     *  Sets the additional transform.
     *
     *  @note The additional transform will be concatenated at the end of nodeToParentTransform.
     *        It could be used to simulate `parent-child` relationship between two nodes (e.g. one is in BatchNode, another isn't).
     *  @code
        // create a batchNode
        CCSpriteBatchNode* batch= CCSpriteBatchNode::create("Icon-114.png");
        this->addChild(batch);
     
        // create two sprites, spriteA will be added to batchNode, they are using different textures.
        CCSprite* spriteA = CCSprite::createWithTexture(batch->getTexture());
        CCSprite* spriteB = CCSprite::create("Icon-72.png");

        batch->addChild(spriteA); 
     
        // We can't make spriteB as spriteA's child since they use different textures. So just add it to layer.
        // But we want to simulate `parent-child` relationship for these two node.
        this->addChild(spriteB); 

        //position
        spriteA->setPosition(ccp(200, 200));
     
        // Gets the spriteA's transform.
        CCAffineTransform t = spriteA->nodeToParentTransform();
     
        // Sets the additional transform to spriteB, spriteB's postion will based on its pseudo parent i.e. spriteA.
        spriteB->setAdditionalTransform(t);

        //scale
        spriteA->setScale(2);
     
        // Gets the spriteA's transform.
        t = spriteA->nodeToParentTransform();
     
        // Sets the additional transform to spriteB, spriteB's scale will based on its pseudo parent i.e. spriteA.
        spriteB->setAdditionalTransform(t);

        //rotation
        spriteA->setRotation(20);
     
        // Gets the spriteA's transform.
        t = spriteA->nodeToParentTransform();
     
        // Sets the additional transform to spriteB, spriteB's rotation will based on its pseudo parent i.e. spriteA.
        spriteB->setAdditionalTransform(t);
     *  @endcode
     */
    // 附加转换：位置，旋转，缩放
    void setAdditionalTransform(const CCAffineTransform& additionalTransform);
    /// @} end of Coordinate Converters

private:
    /// lazy allocs
    /// 懒分配
    void childrenAlloc(void);
    
    /// helper that reorder a child
    /// 插入一个子节点
    void insertChild(CCNode* child, int z);
    
    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    /// 删除一个子节点，调用子节点的onExit()方法，并清理，移除从子对象数组中
    void detachChild(CCNode *child, bool doCleanup);
    
    /// Convert cocos2d coordinates to UI windows coordinate.
    // UI世界坐标与cocos2d坐标系的转换
    CCPoint convertToWindowSpace(const CCPoint& nodePoint);

protected:
    float m_fRotationX;                 ///< rotation angle on x-axis		旋转角度，x轴
    float m_fRotationY;                 ///< rotation angle on y-axis		旋转角度，y轴
    
    float m_fScaleX;                    ///< scaling factor on x-axis		缩放比例，x轴
    float m_fScaleY;                    ///< scaling factor on y-axis		缩放比例，y轴
    
    float m_fVertexZ;                   ///< OpenGL real Z vertex		真实z顶点
    
    CCPoint m_obPosition;               ///< position of the node		节点位置
    
    float m_fSkewX;                     ///< skew angle on x-axis		倾斜角度，x轴
    float m_fSkewY;                     ///< skew angle on y-axis		倾斜角度，y轴
    
    CCPoint m_obAnchorPointInPoints;    ///< anchor point in points		锚点，以点为单位
    CCPoint m_obAnchorPoint;            ///< anchor point normalized (NOT in points)	非转换锚点
    
    CCSize m_obContentSize;             ///< untransformed size of the node		非转化尺寸
    
    
    CCAffineTransform m_sAdditionalTransform; ///< transform				转换
    CCAffineTransform m_sTransform;     ///< transform
    CCAffineTransform m_sInverse;       ///< transform
    
    CCCamera *m_pCamera;                ///< a camera				摄像
    
    CCGridBase *m_pGrid;                ///< a grid				网格
    
    int m_nZOrder;                      ///< z-order value that affects the draw order	z次序，影响绘制顺序
    
    CCArray *m_pChildren;               ///< array of children nodes			子节点数组
    CCNode *m_pParent;                  ///< weak reference to parent node		父类引用
    
    int m_nTag;                         ///< a tag. Can be any number you assigned just to identify this node	标志
    
    void *m_pUserData;                  ///< A user assingned void pointer, Can be point to any cpp object	用户数据
    CCObject *m_pUserObject;            ///< A user assigned CCObject		用户数据对象
    
    CCGLProgram *m_pShaderProgram;      ///< OpenGL shader			着色方案
    
    ccGLServerState m_eGLServerState;   ///< OpenGL servier side state		opengl服务端状态
    
    unsigned int m_uOrderOfArrival;     ///< used to preserve sequence while sorting children with the same zOrder	到达次序
    
    CCScheduler *m_pScheduler;          ///< scheduler used to schedule timers and updates	注册计数器和更新
    
    CCActionManager *m_pActionManager;  ///< a pointer to ActionManager singleton, which is used to handle all the actions	动作管理
    
    bool m_bRunning;                    ///< is running				是否运行中
    
    bool m_bTransformDirty;             ///< transform dirty flag		转换旧的的标示
    bool m_bInverseDirty;               ///< transform dirty flag		同上
    bool m_bAdditionalTransformDirty;   ///< The flag to check whether the additional transform is dirty	检测是否旧的的转换
    bool m_bVisible;                    ///< is this node visible		是否可见
    
    bool m_bIgnoreAnchorPointForPosition; ///< true if the Anchor Point will be (0,0) when you position the CCNode, false otherwise. 是否忽视锚点
                                          ///< Used by CCLayer and CCScene.	
    
    bool m_bReorderChildDirty;          ///< children order dirty flag		是否子对象旧的次序标示
    
    int m_nScriptHandler;               ///< script handler for onEnter() & onExit(), used in Javascript binding and Lua binding.	绑定lua处理
    int m_nUpdateScriptHandler;         ///< script handler for update() callback per frame, which is invoked from lua & javascript.	处理更新
    ccScriptType m_eScriptType;         ///< type of script binding, lua or javascript	绑定脚本类型
};

//#pragma mark - CCNodeRGBA

/** CCNodeRGBA is a subclass of CCNode that implements the CCRGBAProtocol protocol.
 
 All features from CCNode are valid, plus the following new features:
 - opacity
 - RGB colors
 
 Opacity/Color propagates into children that conform to the CCRGBAProtocol if cascadeOpacity/cascadeColor is enabled.
 @since v2.1
 */
// RGBA节点是节点的子类，为实现CCRGBAProtocol协议
// 增加了透明度和颜色值
class CC_DLL CCNodeRGBA : public CCNode, public CCRGBAProtocol
{
public:
    CCNodeRGBA();
    virtual ~CCNodeRGBA();
    
    virtual bool init();
    
    virtual GLubyte getOpacity();
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
    
    virtual void setOpacityModifyRGB(bool bValue) {};
    virtual bool isOpacityModifyRGB() { return false; };

protected:
	GLubyte		_displayedOpacity;
    GLubyte     _realOpacity;
	ccColor3B	_displayedColor;
    ccColor3B   _realColor;
	bool		_cascadeColorEnabled;
    bool        _cascadeOpacityEnabled;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __PLATFORM_CCNODE_H__
