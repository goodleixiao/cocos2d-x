/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      Jason Booth

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
#ifndef __CCRENDER_TEXTURE_H__
#define __CCRENDER_TEXTURE_H__

#include "base_nodes/CCNode.h"
#include "sprite_nodes/CCSprite.h"
#include "kazmath/mat4.h"

NS_CC_BEGIN

/**
 * @addtogroup textures     纹理
 * @{
 */

typedef enum eImageFormat
{
    kCCImageFormatJPEG      = 0,
    kCCImageFormatPNG       = 1,
} tCCImageFormat;
/**
@brief CCRenderTexture is a generic rendering target. To render things into it,
simply construct a render target, call begin on it, call visit on any cocos
scenes or objects to render them, and call end. For convenience, render texture
adds a sprite as it's display child with the results, so you can simply add
the render texture to your scene and treat it like any other CocosNode.
There are also functions for saving the render texture to disk in PNG or JPG format.

@since v0.8.1
*/
// 是一个通用的渲染目标。要渲染的东西，简单构造渲染目标，调用开始，调用访问在场景或对象渲染；调用结束
// 为方便，渲染纹理增加一个精灵，作为显示子对象；你可以简单增加渲染纹理到你的场景中；保存渲染纹理到磁盘用png或jpg格式
class CC_DLL CCRenderTexture : public CCNode 
{
    /** The CCSprite being used.
    The sprite, by default, will use the following blending function: GL_ONE, GL_ONE_MINUS_SRC_ALPHA.
    The blending function can be changed in runtime by calling:
    - [[renderTexture sprite] setBlendFunc:(ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];
    */
    // 精灵被使用。 默认使用下面的混合功能： GL_ONE, GL_ONE_MINUS_SRC_ALPHA.
    // 混合功能可以被改变，在运行时：- [[renderTexture sprite] setBlendFunc:(ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];
    CC_PROPERTY(CCSprite*, m_pSprite, Sprite)
public:
    CCRenderTexture();
    virtual ~CCRenderTexture();
    
    virtual void visit();
    virtual void draw();

    /** initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format*/
    // 初始化渲染纹理对象，使用点宽，高，像素格式，位深度格式为参数
    static CCRenderTexture * create(int w ,int h, CCTexture2DPixelFormat eFormat, GLuint uDepthStencilFormat);

    /** creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    // 初始化渲染纹理对象，使用点宽，高，像素格式为参数
    static CCRenderTexture * create(int w, int h, CCTexture2DPixelFormat eFormat);

    /** creates a RenderTexture object with width and height in Points, pixel format is RGBA8888 */
    // 初始化渲染纹理对象，使用点宽，高，为参数
    static CCRenderTexture * create(int w, int h);

    /** initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    // 初始化渲染纹理对象，使用点宽，高，像素格式为参数
    bool initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat);

    /** initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format*/
    // 初始化渲染纹理对象，使用点宽，高，像素格式，位深度格式为参数
    bool initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat, GLuint uDepthStencilFormat);

    /** starts grabbing */
    // 开始方法
    void begin();

    /** starts rendering to the texture while clearing the texture first.
    This is more efficient then calling -clear first and then -begin */
    // 以颜色值开始清除方法
    void beginWithClear(float r, float g, float b, float a);

    /** starts rendering to the texture while clearing the texture first.
     This is more efficient then calling -clear first and then -begin */
    // 开始清除颜色，位深度值
    void beginWithClear(float r, float g, float b, float a, float depthValue);

    /** starts rendering to the texture while clearing the texture first.
     This is more efficient then calling -clear first and then -begin */
    // 开始清除颜色，位深度，模板值
    void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);

    /** end is key word of lua, use other name to export to lua. */
    // Lua关键字
    inline void endToLua(){ end();};

    /** ends grabbing*/
    // 结束
    void end();

    /** clears the texture with a color */
    // 清理纹理用颜色值
    void clear(float r, float g, float b, float a);

    /** clears the texture with a specified depth value */
    // 清理纹理，使用指定位深度值为参数
    void clearDepth(float depthValue);

    /** clears the texture with a specified stencil value */
    // 清除指定模板值的纹理
    void clearStencil(int stencilValue);
    /* creates a new CCImage from with the texture's data.
       Caller is responsible for releasing it by calling delete.
     */
    // 创建一个新的CCImage对象，从纹理数据中；返回值具有自动释放功能
    CCImage* newCCImage(bool flipImage = true);

    /** saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
        Returns YES if the operation is successful.
     */
    // 保存纹理到文件，指定路径名称
    bool saveToFile(const char *szFilePath);

    /** saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
        Returns YES if the operation is successful.
     */
    // 保存纹理到文件，指定名称和格式
    bool saveToFile(const char *name, tCCImageFormat format);
    
    /** Listen "come to background" message, and save render texture.
     It only has effect on Android.
     */
    // 监听进入后台消息，保存纹理；仅仅用于android平台
    void listenToBackground(CCObject *obj);
    
    /** Listen "come to foreground" message and restore the frame buffer object
     It only has effect on Android.
     */
    // 监听进入前台消息，重存纹理；仅仅用于android平台
    void listenToForeground(CCObject *obj);
    
    /** Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw is YES. */
    // 获取清理标示
    unsigned int getClearFlags() const;
    void setClearFlags(unsigned int uClearFlags);
    
    /** Clear color value. Valid only when "autoDraw" is true. */
    // 清理颜色值
    const ccColor4F& getClearColor() const;
    void setClearColor(const ccColor4F &clearColor);
    
    /** Value for clearDepth. Valid only when autoDraw is true. */
    // 清理位深度值，仅在自动绘制为true有效
    float getClearDepth() const;
    void setClearDepth(float fClearDepth);
    
    /** Value for clear Stencil. Valid only when autoDraw is true */
    // 清理模板值，仅在自动绘制为true有效
    int getClearStencil() const;
    void setClearStencil(float fClearStencil);
    
    /** When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons.
     Will be enabled in the future.
     */
    // 是否自动绘制
    bool isAutoDraw() const;
    void setAutoDraw(bool bAutoDraw);

private:
    void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags);

protected:
    GLuint       m_uFBO;
    GLuint       m_uDepthRenderBufffer;
    GLint        m_nOldFBO;
    CCTexture2D* m_pTexture;
    CCTexture2D* m_pTextureCopy;    // a copy of m_pTexture 纹理复制
    CCImage*     m_pUITextureImage;
    GLenum       m_ePixelFormat;
    
    // code for "auto" update   自动更新
    GLbitfield   m_uClearFlags;
    ccColor4F    m_sClearColor;
    GLclampf     m_fClearDepth;
    GLint        m_nClearStencil;
    bool         m_bAutoDraw;
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCRENDER_TEXTURE_H__
