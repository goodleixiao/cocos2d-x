/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
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
#ifndef __CC_PARTICLE_SYSTEM_QUAD_H__
#define __CC_PARTICLE_SYSTEM_QUAD_H__

#include  "CCParticleSystem.h"

NS_CC_BEGIN

class CCSpriteFrame;

/**
 * @addtogroup particle_nodes
 * @{
 */

/** @brief CCParticleSystemQuad is a subclass of CCParticleSystem

It includes all the features of ParticleSystem.

Special features and Limitations:    
- Particle size can be any float number.
- The system can be scaled
- The particles can be rotated
- It supports subrects
- It supports batched rendering since 1.1
@since v0.8
*/
// 是粒子系统子类，具有所有粒子系统的特性；特殊和限制为：粒子为任意浮点数；可以缩放，粒子可以旋转，支持渲染
class CC_DLL CCParticleSystemQuad : public CCParticleSystem
{
protected:
    ccV3F_C4B_T2F_Quad    *m_pQuads;        // quads to be rendered
    GLushort            *m_pIndices;    // indices      指数

#if CC_TEXTURE_ATLAS_USE_VAO
    GLuint                m_uVAOname;
#endif

    GLuint                m_pBuffersVBO[2]; //0: vertex  1: indices

public:
    CCParticleSystemQuad();
    virtual ~CCParticleSystemQuad();

    /** creates an initializes a CCParticleSystemQuad from a plist file.
    This plist files can be created manually or with Particle Designer:  
    */
    // 使用文件创建；文件可以手动创建或粒子设计
    static CCParticleSystemQuad * create(const char *plistFile);

    /** initializes the indices for the vertices*/
    // 初始化指数，为顶点
    void initIndices();

    /** initializes the texture with a rectangle measured Points */
    // 初始化纹理，使用矩形为参数
    void initTexCoordsWithRect(const CCRect& rect);

    /** Sets a new CCSpriteFrame as particle.
    WARNING: this method is experimental. Use setTexture:withRect instead.
    @since v0.99.4
    */
    // 设置新的精灵帧，作为粒子；用于测试； 使用setTexture:withRect替换
    void setDisplayFrame(CCSpriteFrame *spriteFrame);

    /** Sets a new texture with a rect. The rect is in Points.
    @since v0.99.4
    */
    // 设置新的纹理，使用矩形，以点为单位
    void setTextureWithRect(CCTexture2D *texture, const CCRect& rect);
    // super methods
    // 父类方法
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    virtual void setTexture(CCTexture2D* texture);
    virtual void updateQuadWithParticle(tCCParticle* particle, const CCPoint& newPosition);
    virtual void postStep();
    virtual void draw();
    virtual void setBatchNode(CCParticleBatchNode* batchNode);
    virtual void setTotalParticles(unsigned int tp);
    
    /** listen the event that coming to foreground on Android
     */
    // android平台监听事件，进入后台
    void listenBackToForeground(CCObject *obj);

    static CCParticleSystemQuad * create();
    static CCParticleSystemQuad * createWithTotalParticles(unsigned int numberOfParticles);
private:
#if CC_TEXTURE_ATLAS_USE_VAO
    void setupVBOandVAO();
#else
    void setupVBO();
#endif
    bool allocMemory();
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CC_PARTICLE_SYSTEM_QUAD_H__

