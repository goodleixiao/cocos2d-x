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

#ifndef __CC_TEXT_FIELD_H__
#define __CC_TEXT_FIELD_H__

#include "label_nodes/CCLabelTTF.h"
#include "text_input_node/CCIMEDelegate.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"

NS_CC_BEGIN

class CCTextFieldTTF;

/**
 * @addtogroup input    输入
 * @{
 */

class CC_DLL CCTextFieldDelegate
{
public:
    /**
    @brief    If the sender doesn't want to attach to the IME, return true;
    */
    // 若发送者不想连接到ime，就返回true
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * sender)
    { 
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief    If the sender doesn't want to detach from the IME, return true;
    */
    // 若发送者不想连接到ime，就返回true
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief    If the sender doesn't want to insert the text, return true;
    */
    // 若发送者不想插入文本，就返回true
    virtual bool onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(text);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief    If the sender doesn't want to delete the delText, return true;
    */
    // 若发送者不想删除文本，就返回true
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(delText);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief    If the sender doesn't want to draw, return true.
    */
    // 若发送者不想绘制，就返回true
    virtual bool onDraw(CCTextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
};

/**
@brief    A simple text input field with TTF font.
*/
// 用TTF字体输入文本
class CC_DLL CCTextFieldTTF : public CCLabelTTF, public CCIMEDelegate
{
public:
    CCTextFieldTTF();
    virtual ~CCTextFieldTTF();

    //char * description();

    /** creates a CCTextFieldTTF from a fontname, alignment, dimension and font size */
    // 创建一个文本输入框，使用字体名称，对齐方式，字距，字体大小为参数
    static CCTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** creates a CCLabelTTF from a fontname and font size */
    // 创建文本输入框，使用字体名称，大小为参数
    static CCTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    /** initializes the CCTextFieldTTF with a font name, alignment, dimension and font size */
    // 初始化输入框，使用字体名称，对齐方式，字距，字体大小
    bool initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** initializes the CCTextFieldTTF with a font name and font size */
    // 初始化文本输入框，使用字体名称，和字体大小
    bool initWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);

    /**
    @brief    Open keyboard and receive input text.
    */
    // 打开键盘接收输入文本
    virtual bool attachWithIME();

    /**
    @brief    End text input and close keyboard.
    */
    // 结束输入，关闭键盘
    virtual bool detachWithIME();

    //////////////////////////////////////////////////////////////////////////
    // properties   属性
    //////////////////////////////////////////////////////////////////////////
    
    CC_SYNTHESIZE(CCTextFieldDelegate *, m_pDelegate, Delegate);
    CC_SYNTHESIZE_READONLY(int, m_nCharCount, CharCount);
    virtual const ccColor3B& getColorSpaceHolder();
    virtual void setColorSpaceHolder(const ccColor3B& color);

    // input text property
    // 输入文本属性
public:
    virtual void setString(const char *text);
    virtual const char* getString(void);
protected:
    std::string * m_pInputText;

    // place holder text property
    // place holder text displayed when there is no text in the text field.
    // 占位符文本属性
public:
    virtual void setPlaceHolder(const char * text);
    virtual const char * getPlaceHolder(void);
protected:
    std::string * m_pPlaceHolder;
    ccColor3B m_ColorSpaceHolder;
protected:

    virtual void draw();

    //////////////////////////////////////////////////////////////////////////
    // CCIMEDelegate interface  接口
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME();
    virtual bool canDetachWithIME();
    virtual void insertText(const char * text, int len);
    virtual void deleteBackward();
    virtual const char * getContentText();
private:
    class LengthStack;
    LengthStack * m_pLens;
};

// end of input group
/// @}

NS_CC_END

#endif    // __CC_TEXT_FIELD_H__
