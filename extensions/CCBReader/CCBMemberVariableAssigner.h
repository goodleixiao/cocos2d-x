#ifndef _CCB_CCBMEMBERVARIABLEASSIGNER_H_
#define _CCB_CCBMEMBERVARIABLEASSIGNER_H_

#include "cocos2d.h"
#include "CCBValue.h"

NS_CC_EXT_BEGIN

#define CCB_MEMBERVARIABLEASSIGNER_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if (pTarget == TARGET && 0 == strcmp(pMemberVariableName, (MEMBERVARIABLENAME))) { \
        MEMBERVARIABLETYPE pOldVar = MEMBERVARIABLE; \
        MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(MEMBERVARIABLE); \
        if (pOldVar != MEMBERVARIABLE) { \
            CC_SAFE_RELEASE(pOldVar); \
            MEMBERVARIABLE->retain(); \
        } \
        return true; \
    }


class CCBMemberVariableAssigner {
    public:
        virtual ~CCBMemberVariableAssigner() {};

        /**
         *  The callback function of assigning member variable.
         *  @note The member variable must be CCNode or its subclass.
         *  @param pTarget The custom class.
         *  @param pMemberVariableName The name of the member variable.
         *  @param pNode The member variable.
         *  @return Whether the assignment was successful.
         */
        // 分配成员变量的回调函数，成员变量必须是节点或其子类；使用目标，成员变量名称，节点变量为参数
        virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode) = 0;

        /**
         *  The callback function of assigning custom properties.
         *  @note The member variable must be Integer, Float, Boolean or String.
         *  @param pTarget The custom class.
         *  @param pMemberVariableName The name of the member variable.
         *  @param pValue The value of the property.
         *  @return Whether the assignment was successful.
         */
        // 分配自定义属性的回调函数，使用目标，成员变量名称，值为参数
        virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue) { return false; };
};

NS_CC_EXT_END

#endif
