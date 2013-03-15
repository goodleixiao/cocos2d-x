/*
 * Copyright (c) 2010-2012 cocos2d-x.org
 * Copyright (C) 2009 Matt Oswald
 * Copyright (c) 2009-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 * Copyright (c) 2011 Marco Tillemans
 *
 * http://www.cocos2d-x.org
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef __CCPARTICLEBATCHNODE_H__
#define __CCPARTICLEBATCHNODE_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"

NS_CC_BEGIN

class CCTexture2D;
class CCTextureAtlas;
class CCParticleSystem;

/**
 * @addtogroup particle_nodes       粒子节点
 * @{
 */

#define kCCParticleDefaultCapacity 500

/** CCParticleBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *
 * A CCParticleBatchNode can reference one and only one texture (one image file, one texture atlas).
 * Only the CCParticleSystems that are contained in that texture can be added to the CCSpriteBatchNode.
 * All CCParticleSystems added to a CCSpriteBatchNode are drawn in one OpenGL ES draw call.
 * If the CCParticleSystems are not added to a CCParticleBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.
 *
 *
 * Limitations:
 * - At the moment only CCParticleSystemQuad is supported
 * - All systems need to be drawn with the same parameters, blend function, aliasing, texture
 *
 * Most efficient usage
 * - Initialize the ParticleBatchNode with the texture and enough capacity for all the particle systems
 * - Initialize all particle systems and add them as child to the batch node
 * @since v1.1
 */
/** 就如批量节点；包含子对象，使用单例绘制；一次调用opengl
 * 称为批量绘制
 * 有且仅有一个纹理引用，可以是图片文件，纹理地图集； 
 * 仅支持CCParticleSystems被添加
 * 所有CCParticleSystems对象被一次调用opengl es绘制函数
 * 若CCParticleSystems没有添加，就要一个一个调用opengl绘制函数
 * 
 * 限制：某些时刻仅支持CCParticleSystemQuad；所有CCParticleSystem要具有相同参数，混合功能，纹理
 * 
 * 高效实用：初始化足够容量，所有粒子系统都可以被添加到节点上
 */
class CC_DLL CCParticleBatchNode : public CCNode, public CCTextureProtocol
{
public:
    CCParticleBatchNode();
    virtual ~CCParticleBatchNode();

    /** initializes the particle system with CCTexture2D, a capacity of particles, which particle system to use */
    // 初始化粒子系统，实用纹理，容量为参数
    static CCParticleBatchNode* createWithTexture(CCTexture2D *tex, unsigned int capacity = kCCParticleDefaultCapacity);

    /** initializes the particle system with the name of a file on disk (for a list of supported formats look at the CCTexture2D class), a capacity of particles */
    // 初始化粒子系统，实用文件，容量为参数
    static CCParticleBatchNode* create(const char* fileImage, unsigned int capacity = kCCParticleDefaultCapacity);

    /** initializes the particle system with CCTexture2D, a capacity of particles */
    // 初始化粒子系统，实用纹理，容量为参数
    bool initWithTexture(CCTexture2D *tex, unsigned int capacity);

    /** initializes the particle system with the name of a file on disk (for a list of supported formats look at the CCTexture2D class), a capacity of particles */
    // 初始化粒子系统，实用文件，容量为参数
    bool initWithFile(const char* fileImage, unsigned int capacity);

    /** Add a child into the CCParticleBatchNode */
    // 增加一个子对象到粒子系统中
    virtual void addChild(CCNode * child);
    virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode * child, int zOrder, int tag);

    /** Inserts a child into the CCParticleBatchNode */
    // 插入子对象，使用粒子系统，序号为参数
    void insertChild(CCParticleSystem* pSystem, unsigned int index);

    /** remove child from the CCParticleBatchNode */
    // 移除指定节点
    virtual void removeChild(CCNode* child, bool cleanup);
    virtual void reorderChild(CCNode * child, int zOrder);
    void removeChildAtIndex(unsigned int index, bool doCleanup);
    void removeAllChildrenWithCleanup(bool doCleanup);
    /** disables a particle by inserting a 0'd quad into the texture atlas */
    // 禁用指定序号的粒子
    void disableParticle(unsigned int particleIndex);
    virtual void draw(void);
    // returns the used texture
    // 返回使用的纹理
    virtual CCTexture2D* getTexture(void);
    // sets a new texture. it will be retained
    // 设置一个新的纹理，被保持
    virtual void setTexture(CCTexture2D *texture);
    virtual void setBlendFunc(ccBlendFunc blendFunc);
    // returns the blending function used for the texture
    // 获取混合功能，用于纹理
    virtual ccBlendFunc getBlendFunc(void);

    void visit();

private:
    void updateAllAtlasIndexes();
    void increaseAtlasCapacityTo(unsigned int quantity);
    unsigned int searchNewPositionInChildrenForZ(int z);
    void getCurrentIndex(unsigned int* oldIndex, unsigned int* newIndex, CCNode* child, int z);
    unsigned int addChildHelper(CCParticleSystem* child, int z, int aTag);
    void updateBlendFunc(void);
    /** the texture atlas used for drawing the quads */
    // 纹理地图用于绘制四边形
    CC_SYNTHESIZE(CCTextureAtlas*, m_pTextureAtlas, TextureAtlas);
private:
    /** the blend function used for drawing the quads */
    // 混合功能参数
    ccBlendFunc m_tBlendFunc;
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif /* __CCPARTICLEBATCHNODE_H__ */

