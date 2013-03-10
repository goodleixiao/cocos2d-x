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
#include <QImage>
#include <QPainter>
#include <QFontDatabase>
#include <QFont>
#include <QMap>
#include "CCDirector.h"
#include "ccMacros.h"
#include "CCImage.h"
#include "CCFileUtils.h"
#include "textures/CCTexture2D.h"
#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <sstream>

typedef struct
{
    unsigned int height;
    unsigned int width;
    int         bitsPerComponent;
    bool        hasAlpha;
    bool        isPremultipliedAlpha;
    unsigned char*  data;
} tImageInfo;

static unsigned int nextPOT(unsigned int x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}

typedef enum {
    kCCTexture2DPixelFormat_Automatic = 0,
        //! 32-bit texture: RGBA8888
    kCCTexture2DPixelFormat_RGBA8888,
        //! 24-bit texture: RGBA888
    kCCTexture2DPixelFormat_RGB888,
        //! 16-bit texture without Alpha channel
    kCCTexture2DPixelFormat_RGB565,
        //! 8-bit textures used as masks
    kCCTexture2DPixelFormat_A8,
        //! 16-bit textures: RGBA4444
    kCCTexture2DPixelFormat_RGBA4444,
        //! 16-bit textures: RGB5A1
    kCCTexture2DPixelFormat_RGB5A1,    
    
        //! Default texture format: RGBA8888
    kCCTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_RGBA8888,
    
        // backward compatibility stuff
    kTexture2DPixelFormat_Automatic = kCCTexture2DPixelFormat_Automatic,
    kTexture2DPixelFormat_RGBA8888 = kCCTexture2DPixelFormat_RGBA8888,
    kTexture2DPixelFormat_RGB888 = kCCTexture2DPixelFormat_RGB888,
    kTexture2DPixelFormat_RGB565 = kCCTexture2DPixelFormat_RGB565,
    kTexture2DPixelFormat_A8 = kCCTexture2DPixelFormat_A8,
    kTexture2DPixelFormat_RGBA4444 = kCCTexture2DPixelFormat_RGBA4444,
    kTexture2DPixelFormat_RGB5A1 = kCCTexture2DPixelFormat_RGB5A1,
    kTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_Default
    
} CCTexture2DPixelFormat;

//static bool _initPremultipliedATextureWithImage(CGImageRef image, NSUInteger POTWide, NSUInteger POTHigh, tImageInfo *pImageInfo)
//{
//    NSUInteger            i;
//    CGContextRef        context = nil;
//    unsigned char*        data = nil;;
//    CGColorSpaceRef        colorSpace;
//    unsigned char*        tempData;
//    unsigned int*        inPixel32;
//    unsigned short*        outPixel16;
//    bool                hasAlpha;
//    CGImageAlphaInfo    info;
//    CGSize                imageSize;
//    CCTexture2DPixelFormat    pixelFormat;
    
//    info = CGImageGetAlphaInfo(image);
//    hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
    
//    size_t bpp = CGImageGetBitsPerComponent(image);
//    colorSpace = CGImageGetColorSpace(image);
    
//    if(colorSpace)
//    {
//        if(hasAlpha || bpp >= 8)
//        {
//            pixelFormat = kCCTexture2DPixelFormat_Default;
//        }
//        else
//        {
//            pixelFormat = kCCTexture2DPixelFormat_RGB565;
//        }
//    }
//    else
//    {
//        // NOTE: No colorspace means a mask image
//        pixelFormat = kCCTexture2DPixelFormat_A8;
//    }
    
//    imageSize.width = CGImageGetWidth(image);
//    imageSize.height = CGImageGetHeight(image);
    
//    // Create the bitmap graphics context
    
//    switch(pixelFormat)
//    {
//        case kCCTexture2DPixelFormat_RGBA8888:
//        case kCCTexture2DPixelFormat_RGBA4444:
//        case kCCTexture2DPixelFormat_RGB5A1:
//            colorSpace = CGColorSpaceCreateDeviceRGB();
//            data = new unsigned char[POTHigh * POTWide * 4];
//            info = hasAlpha ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNoneSkipLast;
//            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
//            CGColorSpaceRelease(colorSpace);
//            break;
            
//        case kCCTexture2DPixelFormat_RGB565:
//            colorSpace = CGColorSpaceCreateDeviceRGB();
//            data = new unsigned char[POTHigh * POTWide * 4];
//            info = kCGImageAlphaNoneSkipLast;
//            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
//            CGColorSpaceRelease(colorSpace);
//            break;
//        case kCCTexture2DPixelFormat_A8:
//            data = new unsigned char[POTHigh * POTWide];
//            info = kCGImageAlphaOnly;
//            context = CGBitmapContextCreate(data, POTWide, POTHigh, 8, POTWide, NULL, info);
//            break;
//        default:
//            return false;
//    }
    
//    CGRect rect;
//    rect.size.width = POTWide;
//    rect.size.height = POTHigh;
//    rect.origin.x = 0;
//    rect.origin.y = 0;
    
//    CGContextClearRect(context, rect);
//    CGContextTranslateCTM(context, 0, 0);
//    CGContextDrawImage(context, rect, image);
    
//    // Repack the pixel data into the right format
    
//    if(pixelFormat == kCCTexture2DPixelFormat_RGB565)
//    {
//        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
//        tempData = new unsigned char[POTHigh * POTWide * 2];
//        inPixel32 = (unsigned int*)data;
//        outPixel16 = (unsigned short*)tempData;
//        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
//        {
//            *outPixel16++ = ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | ((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) | ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);
//        }

//        delete[] data;
//        data = tempData;
        
//    }
//    else if (pixelFormat == kCCTexture2DPixelFormat_RGBA4444)
//    {
//        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
//        tempData = new unsigned char[POTHigh * POTWide * 2];
//        inPixel32 = (unsigned int*)data;
//        outPixel16 = (unsigned short*)tempData;
//        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
//        {
//            *outPixel16++ =
//            ((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
//            ((((*inPixel32 >> 8) & 0xFF) >> 4) << 8) | // G
//            ((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
//            ((((*inPixel32 >> 24) & 0xFF) >> 4) << 0); // A
//        }
        
//        delete[] data;
//        data = tempData;
        
//    }
//    else if (pixelFormat == kCCTexture2DPixelFormat_RGB5A1)
//    {
//        //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
//        tempData = new unsigned char[POTHigh * POTWide * 2];
//        inPixel32 = (unsigned int*)data;
//        outPixel16 = (unsigned short*)tempData;
//        for(i = 0; i < POTWide * POTHigh; ++i, ++inPixel32)
//        {
//            *outPixel16++ =
//            ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
//            ((((*inPixel32 >> 8) & 0xFF) >> 3) << 6) | // G
//            ((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
//            ((((*inPixel32 >> 24) & 0xFF) >> 7) << 0); // A
//        }
                
//        delete[] data;
//        data = tempData;
//    }
    
//    // should be after calling super init
//    pImageInfo->isPremultipliedAlpha = true;
//    pImageInfo->hasAlpha = true;
//    pImageInfo->bitsPerComponent = bpp;
//    pImageInfo->width = POTWide;
//    pImageInfo->height = POTHigh;
    
//    if (pImageInfo->data)
//    {
//        delete [] pImageInfo->data;
//    }
//    pImageInfo->data = data;
    
//    CGContextRelease(context);
//    return true;
//}
//// TODO: rename _initWithImage, it also makes a draw call.
//static bool _initWithImage(CGImageRef CGImage, tImageInfo *pImageinfo, double scaleX, double scaleY)
//{
//    NSUInteger POTWide, POTHigh;
    
//    if(CGImage == NULL)
//    {
//        return false;
//    }
    
//	//if (cocos2d::CCImage::getIsScaleEnabled())
//	if( cocos2d::CCDirector::sharedDirector()->getContentScaleFactor() > 1.0f )
//	{
//		POTWide = CGImageGetWidth(CGImage) * scaleX;
//		POTHigh = CGImageGetHeight(CGImage) * scaleY;
//	}
//	else
//	{
//		POTWide = CGImageGetWidth(CGImage);
//		POTHigh = CGImageGetHeight(CGImage);
//	}

    
//    // load and draw image
//    return _initPremultipliedATextureWithImage(CGImage, POTWide, POTHigh, pImageinfo);
//}

static bool _initWithFile(const char* path, tImageInfo *pImageinfo)
{
//    CGImageRef                CGImage;
//    NSImage                    *jpg;
    //NSImage                    *png;
    bool            ret;
    
    // convert jpg to png before loading the texture
    
//    NSString *fullPath = [NSString stringWithUTF8String:path];
//    jpg = [[NSImage alloc] initWithContentsOfFile: fullPath];
//    //png = [[NSImage alloc] initWithData:UIImagePNGRepresentation(jpg)];
//    CGImageSourceRef source = CGImageSourceCreateWithData((CFDataRef)[jpg TIFFRepresentation], NULL);
//    CGImage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
    
//    ret = _initWithImage(CGImage, pImageinfo, 1.0, 1.0);
    
//    //[png release];
//    [jpg release];
//    if (CGImage) CFRelease(CGImage);
//    if (source) CFRelease(source);
  
    return ret;
}

// TODO: rename _initWithData, it also makes a draw call.
static bool _initWithData(void * pBuffer, int length, tImageInfo *pImageinfo, double scaleX, double scaleY)
{
    bool ret = false;
    
    if (pBuffer) 
    {
//        CGImageRef CGImage;
//        NSData *data;
        
//        data = [NSData dataWithBytes:pBuffer length:length];
//		CGImageSourceRef source = CGImageSourceCreateWithData((CFDataRef)data, NULL);
//        CGImage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
        
//        ret = _initWithImage(CGImage, pImageinfo, scaleX, scaleY);
//        if (CGImage) CFRelease(CGImage);
//        if (source) CFRelease(source);
    }
    return ret;
}

static bool _isValidFontName(const char *fontName)
{
    bool ret = false;
    return ret;
}

static bool _initWithString(const char * pText, cocos2d::CCImage::ETextAlign eAlign, const char * pFontName, int nSize, tImageInfo* pInfo, cocos2d::ccColor3B* pStrokeColor)
{
    bool bRet = false;

	CCAssert(pText, "Invalid pText");
	CCAssert(pInfo, "Invalid pInfo");
	
	do {
        QString fontPath(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pFontName));

        QString fontFamily = pFontName;
        QString fontStyle = "Normal";

        bool fontLoaded = false;

        // try to load .ttf font first
        if(!fontPath.endsWith(".ttf"))
        {
            QString fontPathTTF(fontPath);
            fontPathTTF.append(".ttf");

            // font already loaded?
            QMap<QString, QString>::iterator fontIter = loadedFontMap.find(fontPathTTF);
            if(fontIter == loadedFontMap.end())
            {
                int fontID = QFontDatabase::addApplicationFont(fontPathTTF);
                if(fontID != -1)
                {
                    QStringList familyList = QFontDatabase::applicationFontFamilies(fontID);

                    if(familyList.size() > 0)
                        fontFamily = familyList.at(0);

                    loadedFontMap.insert(fontPathTTF, fontFamily);
                    fontLoaded = true;
                }

                //loadedFontMap.insert(fontPathTTF, fontFamily);
            }
        }

        if(!fontLoaded)
        {
            // font already loaded?
            QMap<QString, QString>::iterator fontIter = loadedFontMap.find(fontPath);
            if(fontIter == loadedFontMap.end())
            {
                int fontID = QFontDatabase::addApplicationFont(fontPath);
                if(fontID != -1)
                {
                    QStringList familyList = QFontDatabase::applicationFontFamilies(fontID);

                    if(familyList.size() > 0)
                        fontFamily = familyList.at(0);
                }

                loadedFontMap.insert(fontPath, fontFamily);
            }
            else
            {
                fontFamily = fontIter.value();
            }
        }

        CC_BREAK_IF(!fontFamily);

        int m_nWidth = 0;
        int m_nHeight = 0;
        bool m_bHasAlpha = true;
        bool m_bPreMulti = false;
        unsigned char * m_pData = NULL;
        int m_nBitsPerComponent = 0;

        int nWidth = pInfo->width;
        int nHeight = pInfo->height;
		
        QFontDatabase fd;
        QFont f = fd.font(fontFamily, fontStyle, nSize);
        f.setPixelSize(nSize);

        QFontMetrics fm(f);

        if (nWidth)
        {
            m_nWidth = (short)nWidth;
        }
        else
        {
            m_nWidth = fm.width(QString(pText));
        }

        if (nHeight)
        {
            m_nHeight = (short)nHeight;
        }
        else
        {
            m_nHeight = fm.height();
        }

        m_bHasAlpha = true;
        m_bPreMulti = false;
        m_pData = new unsigned char[m_nWidth * m_nHeight * 4];
        memset(m_pData, 0, m_nWidth * m_nHeight * 4);
        m_nBitsPerComponent = 8;

        QImage image(m_pData, m_nWidth, m_nHeight, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&image);
        painter.setFont(f);
        painter.setPen(Qt::white);

        int flags = 0;
        switch (eAlignMask)
        {
        case kAlignCenter: // Horizontal center and vertical center.
            flags |= Qt::AlignHCenter;
            flags |= Qt::AlignVCenter;
            break;
        case kAlignTop: // Horizontal center and vertical top.
            flags |= Qt::AlignHCenter;
            flags |= Qt::AlignTop;
            break;
        case kAlignTopRight: // Horizontal right and vertical top.
            flags |= Qt::AlignRight;
            flags |= Qt::AlignTop;
            break;
        case kAlignRight: // Horizontal right and vertical center.
            flags |= Qt::AlignRight;
            flags |= Qt::AlignVCenter;
            break;
        case kAlignBottomRight: // Horizontal right and vertical bottom.
            flags |= Qt::AlignRight;
            flags |= Qt::AlignBottom;
            break;
        case kAlignBottom: // Horizontal center and vertical bottom.
            flags |= Qt::AlignHCenter;
            flags |= Qt::AlignBottom;
            break;
        case kAlignBottomLeft: // Horizontal left and vertical bottom.
            flags |= Qt::AlignLeft;
            flags |= Qt::AlignBottom;
            break;
        case kAlignLeft: // Horizontal left and vertical center.
            flags |= Qt::AlignLeft;
            flags |= Qt::AlignVCenter;
            break;
        case kAlignTopLeft: // Horizontal left and vertical top.
            flags |= Qt::AlignLeft;
            flags |= Qt::AlignTop;
            break;
        }

        painter.drawText(QRect(0, 0, m_nWidth, m_nHeight), flags, QString(pText));
        painter.end();

		
		unsigned char* dataNew = new unsigned char[textureSize];
		if (dataNew) {
			memcpy(dataNew, data, textureSize);
			// output params
            pInfo->width = m_nWidth;
            pInfo->height = m_nHeight;
            pInfo->data = m_pData;
            pInfo->hasAlpha = m_bHasAlpha;
            pInfo->isPremultipliedAlpha = m_bPreMulti;
            pInfo->bitsPerComponent = m_nBitsPerComponent;
			bRet = true;
		}
	} while (0);
    return bRet;
}

NS_CC_BEGIN

// TODO: Get rid of this function
static int getBitsPerComponent(const QImage::Format fmt)
{
    switch(fmt)
    {
    case QImage::Format_Mono: return 1;
    case QImage::Format_MonoLSB: return 1;
    case QImage::Format_Indexed8: return 8;
    case QImage::Format_RGB32: return 8;
    case QImage::Format_ARGB32: return 8;
    case QImage::Format_ARGB32_Premultiplied: return 8;
    case QImage::Format_RGB16: return 5;
    case QImage::Format_ARGB8565_Premultiplied: return 8;
    case QImage::Format_RGB666: return 6;
    case QImage::Format_ARGB6666_Premultiplied: return 6;
    case QImage::Format_RGB555: return 5;
    case QImage::Format_ARGB8555_Premultiplied: return 5;
    case QImage::Format_RGB888: return 8;
    case QImage::Format_RGB444: return 4;
    case QImage::Format_ARGB4444_Premultiplied: return 4;
    default:
        CCLOGERROR("Unknown QImage::Format %d", fmt);
        return 0;
    }
}

static bool m_bEnabledScale = true;

bool isFileExists(const char* szFilePath);

bool isFileExists(const char* szFilePath)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//TCHAR dirpath[MAX_PATH];
	//MultiByteToWideChar(936,0,szFilePath,-1,dirpath,sizeof(dirpath));
	DWORD dwFileAttr = GetFileAttributesA(szFilePath);
	if (INVALID_FILE_ATTRIBUTES == dwFileAttr
		|| (dwFileAttr&FILE_ATTRIBUTE_DIRECTORY))	{
		return false;
	}		
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	bool bFind = true;
	do 
	{
		struct stat buf;
		int n = stat(szFilePath, &buf);
		if ((0 != n)
			|| !(buf.st_mode&S_IFMT))	
		{
			bFind = false;
		}
	} while (0);
	if (!bFind)
	{
		//std::string strFilenName = s_strRelativePath + szFilePath;
		unsigned char * pBuffer = NULL;
		unzFile pFile = NULL;
		unsigned long pSize = 0;
		
		do 
		{
			pFile = unzOpen(s_strAndroidPackagePath.c_str());
			if(!pFile)break;
			
			int nRet = unzLocateFile(pFile, szFilePath, 1);
			if(UNZ_OK != nRet)
				bFind = false;
			else
				bFind = true;
		} while (0);
		
		if (pFile)
		{
			unzClose(pFile);
		}
	}
	
	return bFind;
#else
	struct stat buf;
	int n = stat(szFilePath, &buf);
	if ((0 != n)
		|| !(buf.st_mode&S_IFMT))	{
		return false;
	}		
	
#endif
	return true;
}

CCImage::CCImage()
: m_nWidth(0)
, m_nHeight(0)
, m_nBitsPerComponent(0)
, m_pData(0)
, m_bHasAlpha(false)
, m_bPreMulti(false)
{
    
}

CCImage::~CCImage()
{
    CC_SAFE_DELETE_ARRAY(m_pData);
}

bool CCImage::initWithImageFile(const char * strPath, EImageFormat eImgFmt/* = eFmtPng*/)
{
 	std::string strTemp = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(strPath);
	if (m_bEnabledScale)
	{
		if (!isFileExists(strTemp.c_str()))
		{
			if (strTemp.rfind("@2x") == std::string::npos)
			{
				int t = strTemp.rfind(".");
				if (t != std::string::npos)
				{
					strTemp.insert(t, "@2x");
				}
/*				CCSize size = CCDirector::sharedDirector()->getWinSize();		
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				m_dScaleX = size.width/800.0f;
				m_dScaleY = size.height/480.0f;
	#else
				m_dScaleX = size.width/960.0f;
				m_dScaleY = size.height/640.0f;
				
	#endif
*/
			}
		}    
		else
		{
//			m_dScaleX = 1.0;
//			m_dScaleY = 1.0;
		}
	}
	
//	CCFileData tempData(strTemp.c_str(), "rb");			
//	return initWithImageData(tempData.getBuffer(), tempData.getSize(), eImgFmt);

	unsigned long fileSize = 0;
	unsigned char* pFileData = CCFileUtils::sharedFileUtils()->getFileData(strTemp.c_str(), "rb", &fileSize);
	bool ret = initWithImageData(pFileData, fileSize, eImgFmt);
	free(pFileData);
	return ret;
}

bool CCImage::initWithImageFileThreadSafe(const char *fullpath, EImageFormat imageType)
{
    /*
     * CCFileUtils::fullPathFromRelativePath() is not thread-safe, it use autorelease().
     */
    bool bRet = false;
    unsigned long nSize = 0;
    unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullpath, "rb", &nSize);
    if (pBuffer != NULL && nSize > 0)
    {
        bRet = initWithImageData(pBuffer, nSize, imageType);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
}



/*
// please uncomment this and integrate it somehow if you know what your doing, thanks
bool CCImage::potImageData(unsigned int POTWide, unsigned int POTHigh)
{
	unsigned char*			data = NULL;
	unsigned char*			tempData =NULL;
	unsigned int*				inPixel32 = NULL;
	unsigned short*			outPixel16 = NULL;
	bool					hasAlpha;
	CCTexture2DPixelFormat	pixelFormat;
	
	hasAlpha = this->hasAlpha();
	
	size_t bpp = this->getBitsPerComponent();
	
    // compute pixel format
	if(hasAlpha)
	{
		pixelFormat = CCTexture2D::defaultAlphaPixelFormat();
	}
	else
	{
		if (bpp >= 8)
		{
			pixelFormat = kCCTexture2DPixelFormat_RGB888;
		}
		else
		{
			CCLOG("cocos2d: CCTexture2D: Using RGB565 texture since image has no alpha");
			pixelFormat = kCCTexture2DPixelFormat_RGB565;
		}
	}
	
	switch(pixelFormat) {          
		case kCCTexture2DPixelFormat_RGBA8888:
		case kCCTexture2DPixelFormat_RGBA4444:
		case kCCTexture2DPixelFormat_RGB5A1:
		case kCCTexture2DPixelFormat_RGB565:
		case kCCTexture2DPixelFormat_A8:
			tempData = (unsigned char*)(this->getData());
			CCAssert(tempData != NULL, "NULL image data.");
			
			if(this->getWidth() == (short)POTWide && this->getHeight() == (short)POTHigh)
			{
				data = new unsigned char[POTHigh * POTWide * 4];
				memcpy(data, tempData, POTHigh * POTWide * 4);
			}
			else
			{
				data = new unsigned char[POTHigh * POTWide * 4];
				memset(data, 0, POTHigh * POTWide * 4);
				
				unsigned char* pPixelData = (unsigned char*) tempData;
				unsigned char* pTargetData = (unsigned char*) data;
				
				int imageHeight = this->getHeight();
				for(int y = 0; y < imageHeight; ++y)
				{
					memcpy(pTargetData+POTWide*4*y, pPixelData+(this->getWidth())*4*y, (this->getWidth())*4);
				}
			}
			
			break;    
		case kCCTexture2DPixelFormat_RGB888:
			tempData = (unsigned char*)(this->getData());
			CCAssert(tempData != NULL, "NULL image data.");
			if(this->getWidth() == (short)POTWide && this->getHeight() == (short)POTHigh)
			{
				data = new unsigned char[POTHigh * POTWide * 3];
				memcpy(data, tempData, POTHigh * POTWide * 3);
			}
			else
			{
				data = new unsigned char[POTHigh * POTWide * 3];
				memset(data, 0, POTHigh * POTWide * 3);
				
				unsigned char* pPixelData = (unsigned char*) tempData;
				unsigned char* pTargetData = (unsigned char*) data;
				
				int imageHeight = this->getHeight();
				for(int y = 0; y < imageHeight; ++y)
				{
					memcpy(pTargetData+POTWide*3*y, pPixelData+(this->getWidth())*3*y, (this->getWidth())*3);
				}
			}
			break;   
		default:
			CCAssert(0, "Invalid pixel format");
	}
	
	// Repack the pixel data into the right format
	
	if(pixelFormat == kCCTexture2DPixelFormat_RGB565) {
		//Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
		tempData = new unsigned char[POTHigh * POTWide * 2];
		inPixel32 = (unsigned int*)data;
		outPixel16 = (unsigned short*)tempData;
		
		unsigned int length = POTWide * POTHigh;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
			((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) |  // R
			((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) |   // G
			((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);   // B
		}
		
		delete [] data;
		data = tempData;
	}
	else if (pixelFormat == kCCTexture2DPixelFormat_RGBA4444) {
		//Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
		tempData = new unsigned char[POTHigh * POTWide * 2];
		inPixel32 = (unsigned int*)data;
		outPixel16 = (unsigned short*)tempData;
		
		unsigned int length = POTWide * POTHigh;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
			((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
			((((*inPixel32 >> 8) & 0xFF) >> 4) << 8) | // G
			((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
			((((*inPixel32 >> 24) & 0xFF) >> 4) << 0); // A
		}
		
		delete [] data;
		data = tempData;
	}
	else if (pixelFormat == kCCTexture2DPixelFormat_RGB5A1) {
		//Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
		tempData = new unsigned char[POTHigh * POTWide * 2];
		inPixel32 = (unsigned int*)data;
		outPixel16 = (unsigned short*)tempData;
		
		unsigned int length = POTWide * POTHigh;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
			((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
			((((*inPixel32 >> 8) & 0xFF) >> 3) << 6) | // G
			((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
			((((*inPixel32 >> 24) & 0xFF) >> 7) << 0); // A
		}
		
		delete []data;
		data = tempData;
	}
	else if (pixelFormat == kCCTexture2DPixelFormat_A8)
	{
		// fix me, how to convert to A8
		pixelFormat = kCCTexture2DPixelFormat_RGBA8888;
		
		//
		//The code can not work, how to convert to A8?
		//
		//tempData = new unsigned char[POTHigh * POTWide];
		//inPixel32 = (unsigned int*)data;
		//outPixel8 = tempData;
		 
		//unsigned int length = POTWide * POTHigh;
		//for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		//{
		//    *outPixel8++ = (*inPixel32 >> 24) & 0xFF;
		//}
		 
		//delete []data;
		//data = tempData;
		 
	}
	
	if (data)
	{
		CC_SAFE_DELETE_ARRAY(m_pData);
		m_pData = data;
	}
	return true;	
}
*/

//bool CCImage::initWithImageData(void * pData, int nDataLen, EImageFormat eFmt/* = eSrcFmtPng*/)
bool CCImage::initWithImageData(void * pData, 
                           int nDataLen, 
                           EImageFormat eFmt,
                           int nWidth,
                           int nHeight,
                           int nBitsPerComponent)
{
    bool bRet = false;
    tImageInfo info = {0};
    do 
    {
        CC_BREAK_IF(! pData || nDataLen <= 0);
        bRet = _initWithData(pData, nDataLen, &info, 1.0f, 1.0f);//m_dScaleX, m_dScaleY);
    } while (0);
	
    if (bRet)
    {
        m_nHeight = (short)info.height;
        m_nWidth = (short)info.width;
        m_nBitsPerComponent = info.bitsPerComponent;
		if (eFmt == kFmtJpg)
		{
			m_bHasAlpha = true;
			m_bPreMulti = false;
		}
		else
		{
			m_bHasAlpha = info.hasAlpha;
			m_bPreMulti = info.isPremultipliedAlpha;
		}
        m_pData = info.data;
    }
    return bRet;
}

bool CCImage::initWithString(
	const char *    pText, 
	int             nWidth, 
	int             nHeight,
	ETextAlign      eAlignMask,
	const char *    pFontName,
	int             nSize)
{
    tImageInfo info = {0};
    info.width = nWidth;
    info.height = nHeight;
	
    if (! _initWithString(pText, eAlignMask, pFontName, nSize, &info, NULL)) //pStrokeColor))
    {
        return false;
    }
    m_nHeight = (short)info.height;
    m_nWidth = (short)info.width;
    m_nBitsPerComponent = info.bitsPerComponent;
    m_bHasAlpha = info.hasAlpha;
    m_bPreMulti = info.isPremultipliedAlpha;
	if (m_pData) {
		CC_SAFE_DELETE_ARRAY(m_pData);
	}
    m_pData = info.data;

    return true;
}


bool CCImage::_initWithJpgData(void * data, int nSize)
{
    QImage image;

    bool bRet = image.loadFromData((const uchar*)data, nSize, "JPG");
    if (!bRet)
        return false;

    // TODO: Better/faster conversion
    QImage convertedImg = image.convertToFormat(
                QImage::Format_ARGB32_Premultiplied);
    convertedImg = convertedImg.rgbSwapped();

    m_bPreMulti = true;
    m_bHasAlpha = convertedImg.hasAlphaChannel();
    m_nBitsPerComponent = cocos2d::getBitsPerComponent(convertedImg.format());
    m_nHeight = (short)convertedImg.height();
    m_nWidth = (short)convertedImg.width();
    m_pData  = new unsigned char[convertedImg.byteCount()];
    memcpy(m_pData, convertedImg.bits(), convertedImg.byteCount());

    return bRet;
}

bool CCImage::_initWithPngData(void * pData, int nDatalen)
{
    QImage image;

    bool bRet = image.loadFromData((const uchar*)pData, nDatalen, "PNG");
    if (!bRet)
        return false;

    // TODO: Better/faster conversion
    QImage convertedImg = image.convertToFormat(
                QImage::Format_ARGB32_Premultiplied);
    convertedImg = convertedImg.rgbSwapped();

    m_bPreMulti = true;
    m_bHasAlpha = convertedImg.hasAlphaChannel();
    m_nBitsPerComponent = cocos2d::getBitsPerComponent(convertedImg.format());
    m_nHeight = (short)convertedImg.height();
    m_nWidth = (short)convertedImg.width();
    m_pData  = new unsigned char[convertedImg.byteCount()];
    memcpy(m_pData, convertedImg.bits(), convertedImg.byteCount());

    return bRet;
}

bool CCImage::_initWithTiffData(void* pData, int nDatalen)
{
    QImage image;

    bool bRet = image.loadFromData((const uchar*)pData, nDatalen, "TIFF");
    if (!bRet)
        return false;

    // TODO: Better/faster conversion
    QImage convertedImg = image.convertToFormat(
                QImage::Format_ARGB32_Premultiplied);
    convertedImg = convertedImg.rgbSwapped();

    m_bPreMulti = true;
    m_bHasAlpha = convertedImg.hasAlphaChannel();
    m_nBitsPerComponent = cocos2d::getBitsPerComponent(convertedImg.format());
    m_nHeight = (short)convertedImg.height();
    m_nWidth = (short)convertedImg.width();
    m_pData  = new unsigned char[convertedImg.byteCount()];
    memcpy(m_pData, convertedImg.bits(), convertedImg.byteCount());

    return bRet;
}

bool CCImage::saveToFile(const char *pszFilePath, bool bIsToRGB)
{
	assert(false);
	return false;
}

bool CCImage::_saveImageToPNG(const char *pszFilePath, bool bIsToRGB)
{
    QImage image(m_pData, m_nWidth, m_nHeight, QImage::Format_ARGB32);

    if(bIsToRGB)
        image = image.convertToFormat(QImage::Format_RGB32);

    image = image.rgbSwapped();

    bool bRet = image.save(pszFilePath, "PNG");

    return bRet;
}

bool CCImage::_saveImageToJPG(const char *pszFilePath)
{
    QImage image(m_pData, m_nWidth, m_nHeight, QImage::Format_ARGB32);

    image = image.rgbSwapped();

    bool bRet = image.save(pszFilePath, "JPG");

    return bRet;
}


NS_CC_END

