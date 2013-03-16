#ifndef __CC_APPLICATION_PROTOCOL_H__
#define __CC_APPLICATION_PROTOCOL_H__

NS_CC_BEGIN

enum TargetPlatform
{
    kTargetWindows,
    kTargetLinux,
    kTargetMacOS,
    kTargetAndroid,
    kTargetIphone,
    kTargetIpad,
    kTargetBlackBerry,
    kTargetNaCl,
};

/**
 * @addtogroup platform 平台
 * @{
 */

class CC_DLL CCApplicationProtocol
{
public:

    virtual ~CCApplicationProtocol() {}

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    // 应用程序启动：实现导演和场景在此； 初始化完成，则继续
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    // 应用程序进入后台调用
    virtual void applicationDidEnterBackground() = 0;

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    // 应用程序进入前台调用
    virtual void applicationWillEnterForeground() = 0;

    /**
    @brief    Callback by CCDirector for limit FPS.
    @interval       The time, expressed in seconds, between current frame and next. 
    */
    // 设置导演的fps值
    virtual void setAnimationInterval(double interval) = 0;

    /**
    @brief Get current language config
    @return Current language config
    */
    // 获取当前语言配置
    virtual ccLanguageType getCurrentLanguage() = 0;
    
    /**
     @brief Get target platform
     */
    // 获取目标平台
    virtual TargetPlatform getTargetPlatform() = 0;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_APPLICATION_PROTOCOL_H__
