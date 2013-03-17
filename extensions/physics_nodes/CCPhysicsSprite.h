/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __PHYSICSNODES_CCPHYSICSSPRITE_H__
#define __PHYSICSNODES_CCPHYSICSSPRITE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

#if CC_ENABLE_CHIPMUNK_INTEGRATION
#include "chipmunk.h"

#elif CC_ENABLE_BOX2D_INTEGRATION
class b2Body;
#endif // CC_ENABLE_BOX2D_INTEGRATION

NS_CC_EXT_BEGIN
/** A CCSprite subclass that is bound to a physics body.
 It works with:
 - Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Objective-Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Box2d: Preprocessor macro CC_ENABLE_BOX2D_INTEGRATION should be defined
 
 Features and Limitations:
 - Scale and Skew properties are ignored.
 - Position and rotation are going to updated from the physics body
 - If you update the rotation or position manually, the physics body will be updated
 - You can't enble both Chipmunk support and Box2d support at the same time. Only one can be enabled at compile time
 */
 
/** 一个节点的子类，用于物理物体；
 * 如何工作
 * Chipmunk：要设置宏CC_ENABLE_CHIPMUNK_INTEGRATION
 * Objective-Chipmunk：要设置CC_ENABLE_CHIPMUNK_INTEGRATION
 * Box2d：要设置CC_ENABLE_BOX2D_INTEGRATION
 * 
 * 特征和限制：
 * 1，缩放和倾斜属性被忽略
 * 2，位置和旋转被更新
 * 3，如果你手动更新旋转，位置，物理物体也将更新
 * 4，不能同时支持chipmunk和box2d; 只能编译一个
 */
 
class CCPhysicsSprite : public CCSprite
{
protected:
    bool    m_bIgnoreBodyRotation;
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    cpBody  *m_pCPBody;
    
#elif CC_ENABLE_BOX2D_INTEGRATION
    b2Body  *m_pB2Body;
    
    // Pixels to Meters ratio
    // 像素比
    float   m_fPTMRatio;
#endif // CC_ENABLE_CHIPMUNK_INTEGRATION
public:
    CCPhysicsSprite();

    static CCPhysicsSprite* create();
    /** Creates an sprite with a texture.
     The rect used will be the size of the texture.
     The offset will be (0,0).
     */
    // 创建精灵，使用纹理为参数；大小为纹理大小，偏移量为(0,0)
    static CCPhysicsSprite* createWithTexture(CCTexture2D *pTexture);

    /** Creates an sprite with a texture and a rect.
     The offset will be (0,0).
     */
    // 创建物理精灵，使用纹理，矩形为参数；偏移量为(0,0)
    static CCPhysicsSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);

    /** Creates an sprite with an sprite frame. */
    // 创建物理精灵，使用精灵帧为参数
    static CCPhysicsSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

    /** Creates an sprite with an sprite frame name.
     An CCSpriteFrame will be fetched from the CCSpriteFrameCache by name.
     If the CCSpriteFrame doesn't exist it will raise an exception.
     @since v0.9
     */
    // 创建物理精灵，使用精灵帧名称为参数
    static CCPhysicsSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

    /** Creates an sprite with an image filename.
     The rect used will be the size of the image.
     The offset will be (0,0).
     */
    // 创建物理精灵，使用图片文件名称为参数
    static CCPhysicsSprite* create(const char *pszFileName);

    /** Creates an sprite with an image filename and a rect.
     The offset will be (0,0).
     */
    // 创建物理精灵，使用图片名称，和矩形为参数
    static CCPhysicsSprite* create(const char *pszFileName, const CCRect& rect);

    virtual bool isDirty();
    
    /** Keep the sprite's rotation separate from the body. */
    // 是否忽视物体旋转
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);
    
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    
    virtual const CCPoint& getPosition();
    virtual void setPosition(const CCPoint &position);
    virtual float getRotation();
    virtual void setRotation(float fRotation);
    virtual CCAffineTransform nodeToParentTransform();
    
    /** Body accessor when using regular Chipmunk */
    // 物体访问，使用通用chipmunk
    cpBody* getCPBody() const;
    void setCPBody(cpBody *pBody);

#elif CC_ENABLE_BOX2D_INTEGRATION
    
    virtual const CCPoint& getPosition();
    virtual void setPosition(const CCPoint &position);
    virtual float getRotation();
    virtual void setRotation(float fRotation);
    virtual CCAffineTransform nodeToParentTransform();
    
    /** Body accessor when using box2d */
    // 用box2d访问物体
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);
    
    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);
    
#endif // CC_ENABLE_BOX2D_INTEGRATION
    
};

NS_CC_EXT_END

#endif // __PHYSICSNODES_CCPHYSICSSPRITE_H__
