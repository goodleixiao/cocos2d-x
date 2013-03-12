#ifndef __CCEVENT_TYPE_H__
#define __CCEVENT_TYPE_H__

/**
 * This header is used for defining event types using in CCNotificationCenter
 */
//! 定义在使用通知中心时使用的事件类型

// The application will come to foreground.
// This message is used for reloading resources before come to foreground on Android.
// This message is posted in main.cpp.
// 应用程序来到前景
// 在android端上，在呈现到前景时先加载
// 消息在main.cpp文件中被发布
#define EVNET_COME_TO_FOREGROUND    "event_come_to_foreground"

// The application will come to background.
// This message is used for doing something before coming to background, such as save CCRenderTexture.
// This message is posted in cocos2dx/platform/android/jni/MessageJni.cpp.
// 应用置于后台
// 用于置于后台前，做某些事情，如保存当前纹理
// 该消息由messageJni.cpp文件中发布
#define EVENT_COME_TO_BACKGROUND    "event_come_to_background"

#endif // __CCEVENT_TYPE_H__
