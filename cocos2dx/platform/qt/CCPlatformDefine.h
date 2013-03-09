#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#include <assert.h>
#include <QtCore/qglobal.h>

#if defined(_USRDLL)
    #define CC_DLL  Q_DECL_EXPORT
#else
    #define CC_DLL  //Q_DECL_IMPORT
#endif

#if CC_DISABLE_ASSERT > 0
#define CC_ASSERT(cond)
#else
#define CC_ASSERT(cond) Q_ASSERT(cond)
#endif

#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif



#endif /* __CCPLATFORMDEFINE_H__*/
