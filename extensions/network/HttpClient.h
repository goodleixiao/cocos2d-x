/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 greathqy
 
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

#ifndef __CCHTTPREQUEST_H__
#define __CCHTTPREQUEST_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup Network  网络
 * @{
 */


/** @brief Singleton that handles asynchrounous http requests
 * Once the request completed, a callback will issued in main thread when it provided during make request
 */
// 单例处理异步清除；完成请求，在主线程发出回调
class CCHttpClient : public CCObject
{
public:
    /** Return the shared instance **/
    // 返回共享实例
    static CCHttpClient *getInstance();
    
    /** Relase the shared instance **/
    // 释放实例
    static void destroyInstance();
        
    /**
     * Add a get request to task queue
     * @param request a CCHttpRequest object, which includes url, response callback etc.
                      please make sure request->_requestData is clear before calling "send" here.
     * @return NULL
     */
    // 增加一个获取请求任务队列；一个请求对象，包括url,响应回调等；
    void send(CCHttpRequest* request);
  
    
    /**
     * Change the connect timeout
     * @param timeout 
     * @return NULL
     */
    // 改变链接超时
    inline void setTimeoutForConnect(int value) {_timeoutForConnect = value;};
    
    /**
     * Get connect timeout
     * @return int
     *
     */
    // 获取链接超时时间
    inline int getTimeoutForConnect() {return _timeoutForConnect;}
    
    
    /**
     * Change the download timeout
     * @param value
     * @return NULL
     */
    // 改变下载超时
    inline void setTimeoutForRead(int value) {_timeoutForRead = value;};
    

    /**
     * Get download timeout
     * @return int
     */
    // 获取下载超时
    inline int getTimeoutForRead() {return _timeoutForRead;};
        
private:
    CCHttpClient();
    virtual ~CCHttpClient();
    bool init(void);
    
    /**
     * Init pthread mutex, semaphore, and create new thread for http requests
     * @return bool
     */
    // 初始化线程互斥体，信号量，创建新的线程为http请求
    bool lazyInitThreadSemphore();
    /** Poll function called from main thread to dispatch callbacks when http requests finished **/
    // 完成请求，进行的回调
    void dispatchResponseCallbacks(float delta);
    
private:
    // 超时链接
    int _timeoutForConnect;
    // 超时读取
    int _timeoutForRead;
    
    // std::string reqId;
};

// end of Network group
/// @}

NS_CC_EXT_END

#endif //__CCHTTPREQUEST_H__
