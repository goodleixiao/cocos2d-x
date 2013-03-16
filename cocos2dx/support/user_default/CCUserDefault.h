/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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
#ifndef __SUPPORT_CCUSERDEFAULT_H__
#define __SUPPORT_CCUSERDEFAULT_H__

#include "platform/CCPlatformMacros.h"
#include <string>

NS_CC_BEGIN

/**
 * @addtogroup data_storage     数据储存
 * @{
 */

/**
 * CCUserDefault acts as a tiny database. You can save and get base type values by it.
 * For example, setBoolForKey("played", true) will add a bool value true into the database.
 * Its key is "played". You can get the value of the key by getBoolForKey("played").
 * 
 * It supports the following base types:
 * bool, int, float, double, string
 */
// 作为小的数据库。保存和获取基本类型的值。
// 支持的类型有：bool, int, float, double, string
class CC_DLL CCUserDefault
{
public:
    ~CCUserDefault();

    // get value methods

    /**
    @brief Get bool value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is false.
    */
    // 获取方法； 获取布尔值，用键；若不存在，返回默认值；可以设置默认值，否则返回false
    bool    getBoolForKey(const char* pKey);
    bool    getBoolForKey(const char* pKey, bool defaultValue);
    /**
    @brief Get integer value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is 0.
    */
    // 获取整数值
    int     getIntegerForKey(const char* pKey);
    int     getIntegerForKey(const char* pKey, int defaultValue);
    /**
    @brief Get float value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is 0.0f.
    */
    // 获取浮点数值
    float    getFloatForKey(const char* pKey);
    float    getFloatForKey(const char* pKey, float defaultValue);
    /**
    @brief Get double value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is 0.0.
    */
    // 获取double值
    double  getDoubleForKey(const char* pKey);
    double  getDoubleForKey(const char* pKey, double defaultValue);
    /**
    @brief Get string value by key, if the key doesn't exist, a default value will return.
    You can set the default value, or it is "".
    */
    // 获取字符串的值
    std::string getStringForKey(const char* pKey);
    std::string getStringForKey(const char* pKey, const std::string & defaultValue);

    // set value methods

    /**
    @brief Set bool value by key.
    */
    // 设置方法，设置布尔值，使用键为参数
    void    setBoolForKey(const char* pKey, bool value);
    /**
    @brief Set integer value by key.
    */
    // 设置整数值
    void    setIntegerForKey(const char* pKey, int value);
    /**
    @brief Set float value by key.
    */
    // 设置浮点值
    void    setFloatForKey(const char* pKey, float value);
    /**
    @brief Set double value by key.
    */
    // 设置double值
    void    setDoubleForKey(const char* pKey, double value);
    /**
    @brief Set string value by key.
    */
    // 设置字符串
    void    setStringForKey(const char* pKey, const std::string & value);
    /**
     @brief Save content to xml file
     */
    // 保存方法，到xml文件中
    void    flush();

    static CCUserDefault* sharedUserDefault();
    static void purgeSharedUserDefault();
    const static std::string& getXMLFilePath();

private:
    CCUserDefault();
    static bool createXMLFile();
    static bool isXMLFileExist();
    static void initXMLFilePath();
    
    static CCUserDefault* m_spUserDefault;
    static std::string m_sFilePath;
    static bool m_sbIsFilePathInitialized;
};

// end of data_storage group
/// @}

NS_CC_END

#endif // __SUPPORT_CCUSERDEFAULT_H__
