/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __AssetsManager__
#define __AssetsManager__

#include <string>
#include <curl/curl.h>

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

/* 
 *  This class is used to auto update resources, such as pictures or scripts.
 *  The updated package should be a zip file. And there should be a file named
 *  version in the server, which contains version code.
 */
// 该类用于自动更新资源，如图片，脚本。更新包是zip文件。有一个文件是版本，包含版本代码
class AssetsManager
{
public:
    enum ErrorCode
    {
        ServerNotAvailable,    /** server address error or timeout */ // 服务地址不存在，或者超时
        TimeOut,
    };
    
    //! Default constructor. You should set server address later.
    //! 默认构造。 可以设置服务端地址
    AssetsManager();
    
    /* @brief Creates a AssetsManager with new package url and version code url.
     *        AssetsManager will use the value returned by CCFileUtils::getWritablePath() as storage path.
     *
     * @param packageUrl URL of new package, the package should be a zip file.
     * @param versionFileUrl URL of version file. It should contain version code of new package.
     */
    // 创建方法，使用新的包url和版本代码url为参数（zip文件) 可以使用CCFileUtils::getWritablePath()返回的值作为存储路径
    AssetsManager(const char* packageUrl, const char* versionFileUrl);
    
    /* @brief Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @param packageUrl URL of new package, the package should be a zip file.
     * @param versionFileUrl URL of version file. It should contain version code of new package.
     * @param storagePath The path to store downloaded resources.
     */
    // 创建方法，使用新包url,版本代码url和存储路径为参数
    AssetsManager(const char* packageUrl, const char* versionFileUrl, const char* storagePath);
    
    /* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    // 检测是否有新版本
    virtual bool checkUpdate();
    
    /* @brief Download new package if there is a new version, and uncompress downloaded zip file.
     *        Ofcourse it will set search path that stores downloaded files.
     */
    // 下载新的版本，解压下载的文件
    virtual void update();
    
    /* @brief Gets url of package.
     */
    // 获取包的url
    const char* getPackageUrl() const;
    
    /* @brief Sets package url.
     */
    // 设置包的url
    void setPackageUrl(const char* packageUrl);
    
    /* @brief Gets version file url.
     */
    // 获取版本文件url
    const char* getVersionFileUrl() const;
    
    /* @brief Sets version file url.
     */
    // 设置版本文件url
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief Gets current version code.
     */
    // 获取当前版本代码
    std::string getVersion();
    
    /* @brief Deletes recorded version code.
     */
    // 删除旧的版本代码
    void deleteVersion();
    
    /* @brief Gets storage path.
     */
    // 获取存储路径
    const char* getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    // 设置存储路径
    void setStoragePath(const char* storagePath);
    
protected:
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    bool createDirectory(const char *path);
    void setSearchPath();
    
private:
    //! The path to store downloaded resources.
    //! 存储路径
    std::string _storagePath;
    
    //! The version of downloaded resources.
    //! 下载版本资源
    std::string _version;
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    CURL *_curl;
};

NS_CC_EXT_END;

#endif /* defined(__AssetsManager__) */
