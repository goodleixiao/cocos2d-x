#ifndef _CCB_CCBSELECTORRESOLVER_H_
#define _CCB_CCBSELECTORRESOLVER_H_

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../GUI/CCControlExtension/CCInvocation.h"


NS_CC_EXT_BEGIN 

#define CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(TARGET, SELECTORNAME, METHOD) if(pTarget == TARGET && strcmp(pSelectorName, SELECTORNAME) == 0) { \
    return menu_selector(METHOD); \
}

#define CCB_SELECTORRESOLVER_CCCONTROL_GLUE(TARGET, SELECTORNAME, METHOD) if(pTarget == TARGET && strcmp(pSelectorName, SELECTORNAME) == 0) { \
    return cccontrol_selector(METHOD); \
}

class CCBSelectorResolver {
    public:
        virtual ~CCBSelectorResolver() {};
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) = 0;
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) = 0;
};


class CCBScriptOwnerProtocol {
public:
    virtual ~CCBScriptOwnerProtocol() {};
    virtual CCBSelectorResolver * createNew() = 0;
};

NS_CC_EXT_END

#endif
