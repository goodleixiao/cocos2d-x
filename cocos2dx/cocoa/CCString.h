/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#ifndef __CCSTRING_H__
#define __CCSTRING_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#include <string.h>
#endif

#include <stdarg.h>
#include <string>
#include <functional>
#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures      数据结构
 * @{
 */

class CC_DLL CCString : public CCObject
{
public:
    CCString();
    CCString(const char* str);
    CCString(const std::string& str);
    CCString(const CCString& str);

    virtual ~CCString();
    
    /* override assignment operator */
    /* 重载分配操作 */
    CCString& operator= (const CCString& other);

    /** init a string with format, it's similar with the c function 'sprintf' */ 
    /** 用格式方式来初始化一个字符串，像c中的打印函数 */
    bool initWithFormat(const char* format, ...);

    /** convert to int value */
    /** 转成整数值 */
    int intValue() const;

    /** convert to unsigned int value */
    /** 转成无符号整数值 */
    unsigned int uintValue() const;

    /** convert to float value */
    /** 转成浮点值 */
    float floatValue() const;

    /** convert to double value */
    /** 转成双精度浮点值 */
    double doubleValue() const;

    /** convert to bool value */
    /** 转成布尔值 */
    bool boolValue() const;

    /** get the C string */
    /** 获取c字符串 */
    const char* getCString() const;

    /** get the length of string */
    /** 获取字符串长度 */
    unsigned int length() const;

    /** compare to a c string */
    /** 比较一个c字符串 */
    int compare(const char *) const;

    /* override functions */
    /* 重载 */
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual bool isEqual(const CCObject* pObject);

    /** create a string with std string, you can also pass a c string pointer because the default constructor of std::string can access a c string pointer. 
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    /** 创建一个字符串，使用标准字符串，可以使用c字符串的指针作为参数
     * 返回一个自动释放的指针，字符串
     * 不用手动释放
     */
    static CCString* create(const std::string& str);

    /** create a string with format, it's similar with the c function 'sprintf', the default buffer size is (1024*100) bytes,
     *  if you want to change it, you should modify the kMaxStringLen macro in CCString.cpp file.
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */ 
    /** 创建一个字符串，使用格式化方式
     * 返回一个自动释放的指针，字符串
     * 不用手动释放
     */
    static CCString* createWithFormat(const char* format, ...);

    /** create a string with binary data 
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    /** 创建一个字符串，使用字节数据
     * 返回一个自动释放的指针，字符串
     * 不用手动释放
     */
    static CCString* createWithData(const unsigned char* pData, unsigned long nLen);

    /** create a string with a file, 
     *  @return A CCString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    /** 创建一个字符串，使用一个文件
     * 返回一个自动释放的指针，字符串
     * 不用手动释放
     */
    static CCString* createWithContentsOfFile(const char* pszFileName);

private:

    /** only for internal use */
    /** 仅在内部使用 */
    bool initWithFormatAndValist(const char* format, va_list ap);

public:
    std::string m_sString;
};

struct CCStringCompare : public std::binary_function<CCString *, CCString *, bool> {
    public:
        bool operator() (CCString * a, CCString * b) const {
            return strcmp(a->getCString(), b->getCString()) < 0;
        }
};

#define CCStringMake(str) CCString::create(str)
#define ccs               CCStringMake

// end of data_structure group
/// @}

NS_CC_END

#endif //__CCSTRING_H__
