/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
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

#include <string>
#include <stack>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "cocoa/CCString.h"
#include "CCFileUtils.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "CCSAXParser.h"
#include "cocoa/CCDictionary.h"
#include "support/zip_support/unzip.h"

#include <QFile>

#define __CC_PLATFORM_FILEUTILS_CPP__
#include "CCFileUtilsCommon_cpp.h"

#define MAX_PATH 260

USING_NS_CC;

NS_CC_BEGIN

CCDictionary* ccFileUtils_dictionaryWithContentsOfFileThreadSafe(const char *pFileName);
CCArray* ccFileUtils_arrayWithContentsOfFileThreadSafe(const char* pFileName);

static CCFileUtils* s_pFileUtils = NULL;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_pFileUtils == NULL)
    {
        s_pFileUtils = new CCFileUtils();
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
    }
    
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{
    
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    CCAssert(pszRelativePath != NULL, "CCFileUtils: Invalid path");
    
    //TODO:判断是否是绝对路径

    CCString  *pRet = new CCString();

    const std::string& resourceRootPath = CCApplication::sharedApplication()->getResourceRootPath();

    if (strstr(pszRelativePath, m_obDirectory.c_str()) == pszRelativePath)
    {
        pRet->autorelease();
        pRet->m_sString = resourceRootPath + pszRelativePath;
    }
    else
    {
        pRet->autorelease();
        pRet->m_sString = resourceRootPath + m_obDirectory + pszRelativePath;
    }

    //CCLOG("fullPathFromRelativePath: %s",pRet->m_sString.c_str());
    return pRet->m_sString.c_str();

}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
    CCString *pRet = new CCString();
    pRet->autorelease();
    pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
    pRet->m_sString += pszFilename;
    return pRet->m_sString.c_str();
}


unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    CCAssert(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invaild parameters.");

    Q_UNUSED(pszMode);
    QString fullPath(pszFileName);

    QFile file(fullPath);
    if (!file.open(QIODevice::ReadOnly))
    {

        if (isPopupNotify())
        {
            std::string title = "Notification";
            std::string msg = "Get data from file(";
            msg.append(fullPath.toLatin1()).append(") failed!");
            CCMessageBox(msg.c_str(), title.c_str());
        }

        return NULL;
    }

    *pSize = file.size();
    pBuffer = new unsigned char[*pSize];
    *pSize = file.read((char*)pBuffer, *pSize);
    file.close();

    return pBuffer;

    //    *pSize = 0;
//    do
//    {
//        // read the file from hardware
//        FILE *fp = fopen(pszFileName, pszMode);
//        CC_BREAK_IF(!fp);
        
//        fseek(fp,0,SEEK_END);
//        *pSize = ftell(fp);
//        fseek(fp,0,SEEK_SET);
//        pBuffer = new unsigned char[*pSize];
//        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
//        fclose(fp);
//    } while (0);
    
//    if (! pBuffer && isPopupNotify())
//    {
//        std::string title = "Notification";
//        std::string msg = "Get data from file(";
//        msg.append(pszFileName).append(") failed!");
        
//        CCMessageBox(msg.c_str(), title.c_str());
//    }
//    return pBuffer;
}


std::string CCFileUtils::getWriteablePath()
{
    // save to document folder
//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentsDirectory = [paths objectAtIndex:0];
//    std::string strRet = [documentsDirectory UTF8String];
//    strRet.append("/");
//    return strRet;

//    // Return current resource path.
//    // TODO: this will not work when using Qt resources
//    return s_strResourcePath;
    return m_obDirectory;
}



NS_CC_END

