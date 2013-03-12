/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
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

#ifndef __COCOS2D_H__
#define __COCOS2D_H__

// 0x00 HI ME LO
// 00   02 01 00
// cocos2d的版本
#define COCOS2D_VERSION 0x00020100

//
// all cocos2d include files
// cocos2d所有文件
#include "ccConfig.h"

// actions
// 动作
#include "actions/CCAction.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionCamera.h"
#include "actions/CCActionManager.h"
#include "actions/CCActionEase.h"
#include "actions/CCActionPageTurn3D.h"
#include "actions/CCActionGrid.h"
#include "actions/CCActionProgressTimer.h"
#include "actions/CCActionGrid3D.h"
#include "actions/CCActionTiledGrid.h"
#include "actions/CCActionInstant.h"
#include "actions/CCActionTween.h"
#include "actions/CCActionCatmullRom.h"

// base_nodes
// 基本节点
#include "base_nodes/CCNode.h"
#include "base_nodes/CCAtlasNode.h"

// cocoa
// cocoa基础类
#include "cocoa/CCAffineTransform.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCGeometry.h"
#include "cocoa/CCSet.h"
#include "cocoa/CCAutoreleasePool.h"
#include "cocoa/CCInteger.h"
#include "cocoa/CCFloat.h"
#include "cocoa/CCDouble.h"
#include "cocoa/CCBool.h"
#include "cocoa/CCString.h"
#include "cocoa/CCNS.h"
#include "cocoa/CCZone.h"

// draw nodes
// 绘制节点
#include "draw_nodes/CCDrawingPrimitives.h"
#include "draw_nodes/CCDrawNode.h"

// effects
// 效果
#include "effects/CCGrabber.h"
#include "effects/CCGrid.h"

// include
// 基本头文件：配置，事件类型，宏，协议
#include "CCEventType.h"
#include "CCProtocols.h"
#include "ccConfig.h"
#include "ccMacros.h"
#include "ccTypes.h"

// kazmath
// kazmath数学库
#include "kazmath/include/kazmath/kazmath.h"
#include "kazmath/include/kazmath/GL/matrix.h"

// keypad_dispatcher
// 键盘调用
#include "keypad_dispatcher/CCKeypadDelegate.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

// label_nodes
// 标签节点
#include "label_nodes/CCLabelAtlas.h"
#include "label_nodes/CCLabelTTF.h"
#include "label_nodes/CCLabelBMFont.h"

// layers_scenes_transitions_nodes
// 场景过渡节点
#include "layers_scenes_transitions_nodes/CCLayer.h"
#include "layers_scenes_transitions_nodes/CCScene.h"
#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "layers_scenes_transitions_nodes/CCTransitionPageTurn.h"
#include "layers_scenes_transitions_nodes/CCTransitionProgress.h"

// menu_nodes
// 菜单节点
#include "menu_nodes/CCMenu.h"
#include "menu_nodes/CCMenuItem.h"

// misc_nodes
// 其他节点
#include "misc_nodes/CCClippingNode.h"
#include "misc_nodes/CCMotionStreak.h"
#include "misc_nodes/CCProgressTimer.h"
#include "misc_nodes/CCRenderTexture.h"

// particle_nodes
// 粒子节点
#include "particle_nodes/CCParticleBatchNode.h"
#include "particle_nodes/CCParticleSystem.h"
#include "particle_nodes/CCParticleExamples.h"
#include "particle_nodes/CCParticleSystemQuad.h"

// platform
// 平台
#include "platform/CCDevice.h"
#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "platform/CCSAXParser.h"
#include "platform/CCThread.h"
#include "platform/platform.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCPlatformMacros.h"

// IOS平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "platform/ios/CCAccelerometer.h"
    #include "platform/ios/CCApplication.h"
    #include "platform/ios/CCEGLView.h"
    #include "platform/ios/CCGL.h"
    #include "platform/ios/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

// android平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/CCAccelerometer.h"
    #include "platform/android/CCApplication.h"
    #include "platform/android/CCEGLView.h"
    #include "platform/android/CCGL.h"
    #include "platform/android/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

// 黑莓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    #include "platform/blackberry/CCAccelerometer.h"
    #include "platform/blackberry/CCApplication.h"
    #include "platform/blackberry/CCEGLView.h"
    #include "platform/blackberry/CCGL.h"
    #include "platform/blackberry/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY

// windows平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#include "platform/win32/CCAccelerometer.h"
	#include "platform/win32/CCApplication.h"
	#include "platform/win32/CCEGLView.h"
	#include "platform/win32/CCGL.h"
	#include "platform/win32/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

// mac平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	#include "platform/mac/CCAccelerometer.h"
	#include "platform/mac/CCApplication.h"
	#include "platform/mac/CCEGLView.h"
	#include "platform/mac/CCGL.h"
	#include "platform/mac/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC

// linux平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	#include "platform/linux/CCAccelerometer.h"
	#include "platform/linux/CCApplication.h"
	#include "platform/linux/CCEGLView.h"
	#include "platform/linux/CCGL.h"
	#include "platform/linux/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

// MARMALADE CHANGE
// Added for Marmalade support
// 增加Marmalade支持
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	#include "platform/Marmalade/CCAccelerometer.h"
	#include "platform/Marmalade/CCApplication.h"
	#include "platform/Marmalade/CCEGLView.h"
	#include "platform/Marmalade/CCGL.h"
	#include "platform/Marmalade/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

#if (CC_TARGET_PLATFORM == CC_PLATFORM_NACL)
    #include "platform/nacl/CCAccelerometer.h"
    #include "platform/nacl/CCApplication.h"
    #include "platform/nacl/CCEGLView.h"
    #include "platform/nacl/CCGL.h"
    #include "platform/nacl/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

// script_support
// 脚本支持
#include "script_support/CCScriptSupport.h"

// shaders
// 着色
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccShaders.h"

// sprite_nodes
// 精灵节点
#include "sprite_nodes/CCAnimation.h"
#include "sprite_nodes/CCAnimationCache.h"
#include "sprite_nodes/CCSprite.h"
#include "sprite_nodes/CCSpriteBatchNode.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCSpriteFrameCache.h"

// support
// 支持：编码格式，通知，分析器，顶点，用户设置，xml
#include "support/ccUTF8.h"
#include "support/CCNotificationCenter.h"
#include "support/CCPointExtension.h"
#include "support/CCProfiling.h"
#include "support/user_default/CCUserDefault.h"
#include "support/CCVertex.h"
#include "support/tinyxml2/tinyxml2.h"

// text_input_node
// 文本输入节点
#include "text_input_node/CCIMEDelegate.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "text_input_node/CCTextFieldTTF.h"

// textures
// 纹理
#include "textures/CCTexture2D.h"
#include "textures/CCTextureAtlas.h"
#include "textures/CCTextureCache.h"
#include "textures/CCTexturePVR.h"

// tilemap_parallax_nodes
// 瓦片地图视差节点
#include "tilemap_parallax_nodes/CCParallaxNode.h"
#include "tilemap_parallax_nodes/CCTMXLayer.h"
#include "tilemap_parallax_nodes/CCTMXObjectGroup.h"
#include "tilemap_parallax_nodes/CCTMXTiledMap.h"
#include "tilemap_parallax_nodes/CCTMXXMLParser.h"
#include "tilemap_parallax_nodes/CCTileMapAtlas.h"

// touch_dispatcher
// 触摸调度
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouchHandler.h"

// root
// 根目录：调度，导演，配置，摄像
#include "CCCamera.h"
#include "CCConfiguration.h"
#include "CCDirector.h"
#include "CCScheduler.h"

NS_CC_BEGIN

CC_DLL const char* cocos2dVersion();

NS_CC_END

#endif // __COCOS2D_H__
