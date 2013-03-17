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

#include "AssetsManager.h"
#include "cocos2d.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <vector>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#endif

#include "support/zip_support/unzip.h"

using namespace cocos2d;
using namespace std;

NS_CC_EXT_BEGIN;

#define KEY_OF_VERSION   "current-version-code"
#define KEY_OF_DOWNLOADED_VERSION    "downloaded-version-code"
#define TEMP_PACKAGE_FILE_NAME    "cocos2dx-update-temp-package.zip"
#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

AssetsManager::AssetsManager()
: _packageUrl("")
, _versionFileUrl("")
, _version("")
, _curl(NULL)
{
    _storagePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    checkStoragePath();
}

AssetsManager::AssetsManager(const char* packageUrl, const char* versionFileUrl)
: _packageUrl(packageUrl)
, _version("")
, _versionFileUrl(versionFileUrl)
, _curl(NULL)
{
    _storagePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    checkStoragePath();
}

AssetsManager::AssetsManager(const char* packageUrl, const char* versionFileUrl, const char* storagePath)
: _packageUrl(packageUrl)
, _version("")
, _versionFileUrl(versionFileUrl)
, _storagePath(storagePath)
, _curl(NULL)
{
    checkStoragePath();
}

void AssetsManager::checkStoragePath()
{
    if (_storagePath.size() > 0 && _storagePath[_storagePath.size() - 1] != '/')
    {
        _storagePath.append("/");
    }
}

static size_t getVersionCode(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *version = (string*)userdata;
    version->append((char*)ptr, size * nmemb);
    
    return (size * nmemb);
}

bool AssetsManager::checkUpdate()
{
    if (_versionFileUrl.size() == 0) return false;
    
    _curl = curl_easy_init();
    if (! _curl)
    {
        CCLOG("can not init curl");
        return false;
    }
    
    // Clear _version before assign new value.
    // 清除旧的版本
    _version.clear();
    
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, _versionFileUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getVersionCode);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_version);
    res = curl_easy_perform(_curl);
    
    if (res != 0)
    {
        CCLOG("can not get version file content, error code is %d", res);
        curl_easy_cleanup(_curl);
        return false;
    }
    
    string recordedVersion = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_OF_VERSION);
    if (recordedVersion == _version)
    {
        CCLOG("there is not new version");
        // Set resource search path.
        // 设置搜索路径
        setSearchPath();
        return false;
    }
    
    CCLOG("there is a new version: %s", _version.c_str());
    
    return true;
}

void AssetsManager::update()
{
    // 1. Urls of package and version should be valid;
    // 2. Package should be a zip file.
    // urls为有效的，包为zip文件
    if (_versionFileUrl.size() == 0 ||
        _packageUrl.size() == 0 ||
        std::string::npos == _packageUrl.find(".zip"))
    {
        CCLOG("no version file url, or no package url, or the package is not a zip file");
        return;
    }
    
    // Check if there is a new version.
    // 检测是新版本
    if (! checkUpdate()) return;
    
    // Is package already downloaded?
    // 是要下载吗
    string downloadedVersion = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_OF_DOWNLOADED_VERSION);
    if (downloadedVersion != _version)
    {
        if (! downLoad()) return;
        
        // Record downloaded version.
        // 记录下载版本
        CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_DOWNLOADED_VERSION, _version.c_str());
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    // Uncompress zip file.
    // 解压zip文件
    if (! uncompress()) return;
    
    // Record new version code.
    // 记录新版本代码
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_VERSION, _version.c_str());
    
    // Unrecord downloaded version code.
    // 取消下载版本代码
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_DOWNLOADED_VERSION, "");
    
    CCUserDefault::sharedUserDefault()->flush();
    
    // Set resource search path.
    // 设置资源搜索路径
    setSearchPath();
    
    // Delete unloaded zip file.
    // 删除未载入zip文件
    string zipfileName = _storagePath + TEMP_PACKAGE_FILE_NAME;
    if (remove(zipfileName.c_str()) != 0)
    {
        CCLOG("can not remove downloaded zip file");
    }
}

bool AssetsManager::uncompress()
{
    // Open the zip file
    // 打开zip文件
    string outFileName = _storagePath + TEMP_PACKAGE_FILE_NAME;
    unzFile zipfile = unzOpen(outFileName.c_str());
    if (! zipfile)
    {
        CCLOG("can not open downloaded zip file %s", outFileName.c_str());
        return false;
    }
    
    // Get info about the zip file
    // 获取zip 文件信息
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("can not read file global info of %s", outFileName.c_str());
        unzClose(zipfile);
    }
    
    // Buffer to hold data read from the zip file
    // 读取缓冲区
    char readBuffer[BUFFER_SIZE];
    
    CCLOG("start uncompressing");
    
    // Loop to extract all files.
    // 循环提取所有文件
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        // 获取当前文件信息
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  NULL,
                                  0,
                                  NULL,
                                  0) != UNZ_OK)
        {
            CCLOG("can not read file info");
            unzClose(zipfile);
            return false;
        }
        
        string fullPath = _storagePath + fileName;
        
        // Check if this entry is a directory or a file.
        // 检测该实体是文件夹或文件
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] == '/')
        {
            // Entry is a direcotry, so create it.
            // If the directory exists, it will failed scilently.
            // 是文件夹就创建，若文件已经存在，就放弃
            if (!createDirectory(fullPath.c_str()))
            {
                CCLOG("can not create directory %s", fullPath.c_str());
                unzClose(zipfile);
                return false;
            }
        }
        else
        {
            // Entry is a file, so extract it.
            
            // Open current file.
            // 实体是文件，就提取； 打开当前文件
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not open file %s", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            // 创建一个文件存储到当前文件
            FILE *out = fopen(fullPath.c_str(), "wb");
            if (! out)
            {
                CCLOG("can not open destination file %s", fullPath.c_str());
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }
            
            // Write current file content to destinate file.
            // 向目标文件写入当前文件内容
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
                if (error < 0)
                {
                    CCLOG("can not read zip file %s, error code is %d", fileName, error);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }
                
                if (error > 0)
                {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);
            
            fclose(out);
        }
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        // 列表中下个实体
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not read next file");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    CCLOG("end uncompressing");
    
    return true;
}

/*
 * Create a direcotry is platform depended.
 */
// 创建一个文件夹
bool AssetsManager::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    mode_t processMask = umask(0);
    int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    
    return true;
#else
    BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
    return true;
#endif
}
// 设置搜索路径
void AssetsManager::setSearchPath()
{
    vector<string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
    vector<string>::iterator iter = searchPaths.begin();
    searchPaths.insert(iter, _storagePath);
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
}
// 下载包的大小
static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

static int progressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    CCLOG("downloading... %d%%", (int)(nowDownloaded/totalToDownload*100));
    
    return 0;
}

bool AssetsManager::downLoad()
{
    // Create a file to save package.
    // 创建一个文件存储在包中
    string outFileName = _storagePath + TEMP_PACKAGE_FILE_NAME;
    FILE *fp = fopen(outFileName.c_str(), "wb");
    if (! fp)
    {
        CCLOG("can not create file %s", outFileName.c_str());
        return false;
    }
    
    // Download pacakge
    // 下载包
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, _packageUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downLoadPackage);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, progressFunc);
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res != 0)
    {
        CCLOG("error when download package");
        fclose(fp);
        return false;
    }
    
    CCLOG("succeed downloading package %s", _packageUrl.c_str());
    
    fclose(fp);
    return true;
}

const char* AssetsManager::getPackageUrl() const
{
    return _packageUrl.c_str();
}

void AssetsManager::setPackageUrl(const char *packageUrl)
{
    _packageUrl = packageUrl;
}

const char* AssetsManager::getStoragePath() const
{
    return _storagePath.c_str();
}

void AssetsManager::setStoragePath(const char *storagePath)
{
    _storagePath = storagePath;
    checkStoragePath();
}

const char* AssetsManager::getVersionFileUrl() const
{
    return _versionFileUrl.c_str();
}

void AssetsManager::setVersionFileUrl(const char *versionFileUrl)
{
    _versionFileUrl = versionFileUrl;
}

string AssetsManager::getVersion()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey(KEY_OF_VERSION);
}

void AssetsManager::deleteVersion()
{
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_VERSION, "");
}

NS_CC_EXT_END;
