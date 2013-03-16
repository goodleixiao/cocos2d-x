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

#ifndef __SUPPORT_DATA_SUPPORT_TGALIB_H__
#define __SUPPORT_DATA_SUPPORT_TGALIB_H__

namespace cocos2d {

enum {
    TGA_OK,
    TGA_ERROR_FILE_OPEN,
    TGA_ERROR_READING_FILE,
    TGA_ERROR_INDEXED_COLOR,
    TGA_ERROR_MEMORY,
    TGA_ERROR_COMPRESSED_FILE,
};

/** TGA format */
/**TGA图像格式最大的特点是可以做出不规则形状的图形、图像文件，一般图形、图像文件都为四方形，
 * 若需要有圆形、菱形甚至是缕空的图像文件时，TGA可就派上用场了。
 */
typedef struct sImageTGA {
    int status;
    unsigned char type, pixelDepth;
    
    /** map width */
    // 宽度
    signed short width;
    
    /** map height */
    // 高度
    signed short height;
    
    /** raw data */
    // 原始数据
    unsigned char *imageData;
    int flipped;
} tImageTGA;

/// load the image header fields. We only keep those that matter!
/// 载人图片头区域，参数缓存，大小，图片信息为参数
bool tgaLoadHeader(unsigned char *Buffer, unsigned long bufSize, tImageTGA *psInfo);

/// loads the image pixels. You shouldn't call this function directly
/// 载人图片像素，参数缓存，大小，图片信息为参数
bool tgaLoadImageData(unsigned char *Buffer, unsigned long bufSize, tImageTGA *psInfo);

/// this is the function to call when we want to load an image
// 载人图片，使用文件名称为参数
tImageTGA * tgaLoad(const char *pszFilename);

// /converts RGB to grayscale
// rgb到灰阶（灰阶代表了由最暗到最亮之间不同亮度的层次级别）
void tgaRGBtogreyscale(tImageTGA *psInfo);

/// releases the memory used for the image
/// 释放内存
void tgaDestroy(tImageTGA *psInfo);

}//namespace cocos2d 

#endif // __SUPPORT_DATA_SUPPORT_TGALIB_H__
