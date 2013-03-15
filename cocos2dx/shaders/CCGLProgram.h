/****************************************************************************
Copyright 2012 cocos2d-x.org
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada

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

#ifndef __CCGLPROGRAM_H__
#define __CCGLPROGRAM_H__

#include "ccMacros.h"
#include "cocoa/CCObject.h"

#include "CCGL.h"

NS_CC_BEGIN

/**
 * @addtogroup shaders	着色
 * @{
 */

enum {
    kCCVertexAttrib_Position,
    kCCVertexAttrib_Color,
    kCCVertexAttrib_TexCoords,

    kCCVertexAttrib_MAX,
};

enum {
	kCCUniformPMatrix,
	kCCUniformMVMatrix,
	kCCUniformMVPMatrix,
	kCCUniformTime,
	kCCUniformSinTime,
	kCCUniformCosTime,
	kCCUniformRandom01,
	kCCUniformSampler,
    
	kCCUniform_MAX,
};

#define kCCShader_PositionTextureColor              "ShaderPositionTextureColor"
#define kCCShader_PositionTextureColorAlphaTest     "ShaderPositionTextureColorAlphaTest"
#define kCCShader_PositionColor                     "ShaderPositionColor"
#define kCCShader_PositionTexture                   "ShaderPositionTexture"
#define kCCShader_PositionTexture_uColor            "ShaderPositionTexture_uColor"
#define kCCShader_PositionTextureA8Color            "ShaderPositionTextureA8Color"
#define kCCShader_Position_uColor                   "ShaderPosition_uColor"
#define kCCShader_PositionLengthTexureColor         "ShaderPositionLengthTextureColor"

// uniform names	统一名称
#define kCCUniformPMatrix_s				"CC_PMatrix"
#define kCCUniformMVMatrix_s			"CC_MVMatrix"
#define kCCUniformMVPMatrix_s			"CC_MVPMatrix"
#define kCCUniformTime_s				"CC_Time"
#define kCCUniformSinTime_s				"CC_SinTime"
#define kCCUniformCosTime_s				"CC_CosTime"
#define kCCUniformRandom01_s			"CC_Random01"
#define kCCUniformSampler_s				"CC_Texture0"
#define kCCUniformAlphaTestValue		"CC_alpha_value"

// Attribute names	属性名称
#define    kCCAttributeNameColor           "a_color"
#define    kCCAttributeNamePosition        "a_position"
#define    kCCAttributeNameTexCoord        "a_texCoord"

struct _hashUniformEntry;

typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);

/** CCGLProgram
 Class that implements a glProgram
 
 
 @since v2.0.0
 */
// 着色方案
class CC_DLL CCGLProgram : public CCObject
{
public:
    CCGLProgram();
    virtual ~CCGLProgram();
    /** Initializes the CCGLProgram with a vertex and fragment with bytes array */
    // 初始化着色，使用顶点，字节数组片段为参数
    bool initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    /** Initializes the CCGLProgram with a vertex and fragment with contents of filenames */
    // 初始化着色，使用顶点和文件名称为参数
    bool initWithVertexShaderFilename(const char* vShaderFilename, const char* fShaderFilename);
    /**  It will add a new attribute to the shader */
    // 增加一个新的属性给着色，使用属性名称和序号为参数
    void addAttribute(const char* attributeName, GLuint index);
    /** links the glProgram */
    // 链接方案
    bool link();
    /** it will call glUseProgram() */
    // 调用glUseProgram()
    void use();
/** It will create 4 uniforms:
    - kCCUniformPMatrix
    - kCCUniformMVMatrix
    - kCCUniformMVPMatrix
    - kCCUniformSampler

 And it will bind "kCCUniformSampler" to 0

 */
    // 统一创建： 绑定kCCUniformSampler为0
    void updateUniforms();
    
    /** calls retrieves the named uniform location for this shader program. */
    // 调用检索名称统一位置，在此着色程序中
    GLint getUniformLocationForName(const char* name);
    
    /** calls glUniform1i only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUnifor1i()
    void setUniformLocationWith1i(GLint location, GLint i1);

    /** calls glUniform1f only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniform1f()
    void setUniformLocationWith1f(GLint location, GLfloat f1);

    /** calls glUniform2f only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniform2f()
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);

    /** calls glUniform3f only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniform3f()
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** calls glUniform4f only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniform4f()
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** calls glUniform2fv only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniform2fv()
    void setUniformLocationWith2fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform3fv only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniform3fv()
    void setUniformLocationWith3fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform4fv only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniform4fv()
    void setUniformLocationWith4fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，调用glUniformMatrix4fv()
    void setUniformLocationWithMatrix4fv(GLint location, GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** will update the builtin uniforms if they are different than the previous call for this same shader program. */
    // 当值与前一次调用不同时，更新统一
    void setUniformsForBuiltins();

    /** returns the vertexShader error log */
    // 返回顶点着色错误日志
    const char* vertexShaderLog();
    /** returns the fragmentShader error log */
    // 返回片段着色错误日志
    const char* fragmentShaderLog();
    /** returns the program error log */
    // 返回着色程序错误日志
    const char* programLog();
    
    // reload all shaders, this function is designed for android
    // when opengl context lost, so don't call it.
    // 重载所有着色，为android设计；当opengl上下文丢失，不用调用
    void reset();
    
    inline const GLuint getProgram() { return m_uProgram; }

private:
    bool updateUniformLocation(GLint location, GLvoid* data, unsigned int bytes);
    const char* description();
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
    const char* logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc);

private:
    GLuint            m_uProgram;
    GLuint            m_uVertShader;
    GLuint            m_uFragShader;
    GLint             m_uUniforms[kCCUniform_MAX];
    struct _hashUniformEntry* m_pHashForUniforms;
    bool              m_bUsesTime;
};

// end of shaders group
/// @}

NS_CC_END

#endif /* __CCGLPROGRAM_H__ */
