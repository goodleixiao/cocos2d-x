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

#ifndef __SPRITE_CCSPRITE_FRAME_H__
#define __SPRITE_CCSPRITE_FRAME_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN

class CCTexture2D;
class CCZone;

/**
 * @addtogroup sprite_nodes 精灵节点
 * @{
 */

/** @brief A CCSpriteFrame has:
    - texture: A CCTexture2D that will be used by the CCSprite
    - rectangle: A rectangle of the texture


 You can modify the frame of a CCSprite by doing:
 
    CCSpriteFrame *frame = CCSpriteFrame::frameWithTexture(texture, rect, offset);
    sprite->setDisplayFrame(frame);
 */
/** 精灵帧：纹理，矩形
 * 可以修改帧如下
 CCSpriteFrame *frame = CCSpriteFrame::frameWithTexture(texture, rect, offset);
 sprite->setDisplayFrame(frame);
 */
class CC_DLL CCSpriteFrame : public CCObject
{
public:
    // attributes
    //属性
    inline const CCRect& getRectInPixels(void) { return m_obRectInPixels; }
    void setRectInPixels(const CCRect& rectInPixels);

    inline bool isRotated(void) { return m_bRotated; }
    inline void setRotated(bool bRotated) { m_bRotated = bRotated; }

    /** get rect of the frame */
    // 获取帧矩形
    inline const CCRect& getRect(void) { return m_obRect; }
    /** set rect of the frame */
    // 设置帧矩形
    void setRect(const CCRect& rect);

    /** get offset of the frame */
    // 获取偏移量
    const CCPoint& getOffsetInPixels(void);
    /** set offset of the frame */
    // 设置偏移量
    void setOffsetInPixels(const CCPoint& offsetInPixels);

    /** get original size of the trimmed image */
    // 获取修剪图片大小
    inline const CCSize& getOriginalSizeInPixels(void) { return m_obOriginalSizeInPixels; }
    /** set original size of the trimmed image */
    // 设置修改图片大小
    inline void setOriginalSizeInPixels(const CCSize& sizeInPixels) { m_obOriginalSizeInPixels = sizeInPixels; }

    /** get original size of the trimmed image */
    // 获取修剪图片大小
    inline const CCSize& getOriginalSize(void) { return m_obOriginalSize; }
    /** set original size of the trimmed image */
    // 设置修改图片大小
    inline void setOriginalSize(const CCSize& sizeInPixels) { m_obOriginalSize = sizeInPixels; }

    /** get texture of the frame */
    // 获取纹理
    CCTexture2D* getTexture(void);
    /** set texture of the frame, the texture is retained */
    // 设置纹理
    void setTexture(CCTexture2D* pobTexture);

    const CCPoint& getOffset(void);
    void setOffset(const CCPoint& offsets);

public:
    ~CCSpriteFrame(void);
    virtual CCObject* copyWithZone(CCZone *pZone);

    /** Create a CCSpriteFrame with a texture filename, rect in points.
     It is assumed that the frame was not trimmed.
     */
    // 创建帧，使用纹理名称，矩形以点为单位
    static CCSpriteFrame* create(const char* filename, const CCRect& rect);
    
    /** Create a CCSpriteFrame with a texture filename, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.
     */
    // 创建帧，使用纹理名称，大小，旋转，偏移量，原大小以像素为单位； 原大小为，为修剪的帧
    static CCSpriteFrame* create(const char* filename, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize);
    
    /** Create a CCSpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     */
    // 创建帧，使用纹理，大小为参数
    static CCSpriteFrame* createWithTexture(CCTexture2D* pobTexture, const CCRect& rect);

    /** Create a CCSpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in points of the frame before being trimmed.
     */
    // 创建帧，使用纹理，大小，旋转，原大小以像素为单位
    static CCSpriteFrame* createWithTexture(CCTexture2D* pobTexture, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize);

public:
    /** Initializes a CCSpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     */
    // 初始化帧，使用纹理，大小为参数
    bool initWithTexture(CCTexture2D* pobTexture, const CCRect& rect);

    /** Initializes a CCSpriteFrame with a texture filename, rect in points;
     It is assumed that the frame was not trimmed.
     */
    // 初始化帧，使用纹理名称，大小为参数
    bool initWithTextureFilename(const char* filename, const CCRect& rect);

    /** Initializes a CCSpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
    The originalSize is the size in points of the frame before being trimmed.
    */
    // 初始化帧，使用纹理，大小，旋转，偏移量，原大小为参数
    bool initWithTexture(CCTexture2D* pobTexture, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize);

    /** Initializes a CCSpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.

     @since v1.1
     */
    // 初始化帧，使用文件名称，大小，旋转，偏移量，原大小为参数
    bool initWithTextureFilename(const char* filename, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize);


protected:
    CCPoint m_obOffset;
    CCSize m_obOriginalSize;
    CCRect m_obRectInPixels;
    bool   m_bRotated;
    CCRect m_obRect;
    CCPoint m_obOffsetInPixels;
    CCSize m_obOriginalSizeInPixels;
    CCTexture2D *m_pobTexture;
    std::string  m_strTextureFilename;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif //__SPRITE_CCSPRITE_FRAME_H__
