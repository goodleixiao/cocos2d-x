/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Ricardo Quesada
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

#ifndef __CCSHADERCACHE_H__
#define __CCSHADERCACHE_H__

#include "cocoa/CCDictionary.h"

NS_CC_BEGIN

class CCGLProgram;

/**
 * @addtogroup shaders  着色
 * @{
 */

/** CCShaderCache
 Singleton that stores manages GL shaders
 @since v2.0
 */
// 单例管理gl着色
class CC_DLL CCShaderCache : public CCObject 
{
public:
    CCShaderCache();

    virtual ~CCShaderCache();
    /** returns the shared instance */
    // 返回共享实例
    static CCShaderCache* sharedShaderCache();

    /** purges the cache. It releases the retained instance. */
    // 清除缓存，释放实例
    static void purgeSharedShaderCache();

    /** loads the default shaders */
    // 载人默认着色
    void loadDefaultShaders();
    
    /** reload the default shaders */
    // 重载默认着色
    void reloadDefaultShaders();

    /** returns a GL program for a given key */
    // 返回gl方案，给定键
    CCGLProgram * programForKey(const char* key);

    /** adds a CCGLProgram to the cache for a given name */
    // 增加方案，使用方案，和键为参数
    void addProgram(CCGLProgram* program, const char* key);

private:
    bool init();
    void loadDefaultShader(CCGLProgram *program, int type);

    CCDictionary* m_pPrograms;

};

// end of shaders group
/// @}

NS_CC_END

#endif /* __CCSHADERCACHE_H__ */
