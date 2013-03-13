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
#include "CCNS.h"
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

NS_CC_BEGIN

typedef std::vector<std::string> strArray;

// string toolkit
// 字符串工具包
static inline void split(std::string src, const char* token, strArray& vect)
{
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

// first, judge whether the form of the string like this: {x,y}
// if the form is right,the string will be split into the parameter strs;
// or the parameter strs will be empty.
// if the form is right return true,else return false.
// 首先，判断表格的字符串是否为{x,y}
// 是，则使用分裂字符串到参数strs
// 否则参数strs为空；
// 表格是对的，则返回true
static bool splitWithForm(const char* pStr, strArray& strs)
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(!pStr);

        // string is empty
        // 字符串为空
        std::string content = pStr;
        CC_BREAK_IF(content.length() == 0);

        int nPosLeft  = content.find('{');
        int nPosRight = content.find('}');

        // don't have '{' and '}'
        // 不含有{}
        CC_BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);
        // '}' is before '{'
        // }在{前
        CC_BREAK_IF(nPosLeft > nPosRight);

        std::string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        // nothing between '{' and '}'
        // 在{}之前没有任何参数
        CC_BREAK_IF(pointStr.length() == 0);

        int nPos1 = pointStr.find('{');
        int nPos2 = pointStr.find('}');
        // contain '{' or '}' 
        // 包含{}
        CC_BREAK_IF(nPos1 != (int)std::string::npos || nPos2 != (int)std::string::npos);

        split(pointStr, ",", strs);
        if (strs.size() != 2 || strs[0].length() == 0 || strs[1].length() == 0)
        {
            strs.clear();
            break;
        }

        bRet = true;
    } while (0);

    return bRet;
}

// implement the functions
// 实现功能
CCRect CCRectFromString(const char* pszContent)
{
    CCRect result = CCRectZero;

    do 
    {
        CC_BREAK_IF(!pszContent);
        std::string content = pszContent;

        // find the first '{' and the third '}'
        // 找到第一个{和第三个}
        int nPosLeft  = content.find('{');
        int nPosRight = content.find('}');
        for (int i = 1; i < 3; ++i)
        {
            if (nPosRight == (int)std::string::npos)
            {
                break;
            }
            nPosRight = content.find('}', nPosRight + 1);
        }
        CC_BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);

        content = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        int nPointEnd = content.find('}');
        CC_BREAK_IF(nPointEnd == (int)std::string::npos);
        nPointEnd = content.find(',', nPointEnd);
        CC_BREAK_IF(nPointEnd == (int)std::string::npos);

        // get the point string and size string
        // 获取点字符串和大小字符串
        std::string pointStr = content.substr(0, nPointEnd);
        std::string sizeStr  = content.substr(nPointEnd + 1, content.length() - nPointEnd);

        // split the string with ','
        // 分离字符串用逗号
        strArray pointInfo;
        CC_BREAK_IF(!splitWithForm(pointStr.c_str(), pointInfo));
        strArray sizeInfo;
        CC_BREAK_IF(!splitWithForm(sizeStr.c_str(), sizeInfo));

        float x = (float) atof(pointInfo[0].c_str());
        float y = (float) atof(pointInfo[1].c_str());
        float width  = (float) atof(sizeInfo[0].c_str());
        float height = (float) atof(sizeInfo[1].c_str());

        result = CCRectMake(x, y, width, height);
    } while (0);

    return result;
}

CCPoint CCPointFromString(const char* pszContent)
{
    CCPoint ret = CCPointZero;

    do 
    {
        strArray strs;
        CC_BREAK_IF(!splitWithForm(pszContent, strs));

        float x = (float) atof(strs[0].c_str());
        float y = (float) atof(strs[1].c_str());

        ret = CCPointMake(x, y);
    } while (0);

    return ret;
}

CCSize CCSizeFromString(const char* pszContent)
{
    CCSize ret = CCSizeZero;

    do 
    {
        strArray strs;
        CC_BREAK_IF(!splitWithForm(pszContent, strs));

        float width  = (float) atof(strs[0].c_str());
        float height = (float) atof(strs[1].c_str());

        ret = CCSizeMake(width, height);
    } while (0);

    return ret;
}

NS_CC_END
