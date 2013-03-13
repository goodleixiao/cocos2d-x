/****************************************************************************
Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
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
#ifndef __CCARRAY_H__
#define __CCARRAY_H__

#include "support/data_support/ccCArray.h"

/**
 * @addtogroup data_structures      数据结构
 * @{
 */

/** @def CCARRAY_FOREACH
A convenience macro to iterate over a CCArray using. It is faster than the "fast enumeration" interface.
@since v0.99.4
*/

/*
In cocos2d-iphone 1.0.0, This macro have been update to like this:

#define CCARRAY_FOREACH(__array__, __object__)                                                \
if (__array__ && __array__->data->num > 0)                                                    \
for(id *__arr__ = __array__->data->arr, *end = __array__->data->arr + __array__->data->num-1;    \
__arr__ <= end && ((__object__ = *__arr__) != nil || true);                                        \
__arr__++)

I found that it's not work in C++. So it keep what it's look like in version 1.0.0-rc3. ---By Bin
*/
/*
宏定义遍历数组，更快访问
*/
#define CCARRAY_FOREACH(__array__, __object__)                                                                         \
    if ((__array__) && (__array__)->data->num > 0)                                                                     \
    for(CCObject** __arr__ = (__array__)->data->arr, **__end__ = (__array__)->data->arr + (__array__)->data->num-1;    \
    __arr__ <= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                             \
    __arr__++)

#define CCARRAY_FOREACH_REVERSE(__array__, __object__)                                                                  \
    if ((__array__) && (__array__)->data->num > 0)                                                                      \
    for(CCObject** __arr__ = (__array__)->data->arr + (__array__)->data->num-1, **__end__ = (__array__)->data->arr;     \
    __arr__ >= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                              \
    __arr__--)

#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
#define CCARRAY_VERIFY_TYPE(__array__, __type__)                                                                 \
    do {                                                                                                         \
        if ((__array__) && (__array__)->data->num > 0)                                                           \
            for(CCObject** __arr__ = (__array__)->data->arr,                                                     \
                **__end__ = (__array__)->data->arr + (__array__)->data->num-1; __arr__ <= __end__; __arr__++)    \
                CCAssert(dynamic_cast<__type__>(*__arr__), "element type is wrong!");                            \
    } while(false)
#else
#define CCARRAY_VERIFY_TYPE(__array__, __type__) void(0)
#endif

#define arrayMakeObjectsPerformSelector(pArray, func, elementType)    \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        CCObject* child;                                              \
        CCARRAY_FOREACH(pArray, child)                                \
        {                                                             \
            elementType pNode = (elementType) child;                  \
            if(pNode)                                                 \
            {                                                         \
                pNode->func();                                        \
            }                                                         \
        }                                                             \
    }                                                                 \
}                                                                     \
while(false)

#define arrayMakeObjectsPerformSelectorWithObject(pArray, func, pObject, elementType)   \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        CCObject* child = NULL;                                       \
        CCARRAY_FOREACH(pArray, child)                                \
        {                                                             \
            elementType pNode = (elementType) child;                  \
            if(pNode)                                                 \
            {                                                         \
                pNode->func(pObject);                                 \
            }                                                         \
        }                                                             \
    }                                                                 \
}                                                                     \
while(false)


NS_CC_BEGIN

class CC_DLL CCArray : public CCObject
{
public:
    ~CCArray();

    /** Create an array */
    // 创建一个数组
    static CCArray* create();
    /** Create an array with some objects */
    // 使用一些对象创建数组
    static CCArray* create(CCObject* pObject, ...);
    /** Create an array with one object */
    // 使用一个对象创建一个数组
    static CCArray* createWithObject(CCObject* pObject);
    /** Create an array with capacity */
    // 创建一个带容量的数组
    static CCArray* createWithCapacity(unsigned int capacity);
    /** Create an array with an existing array */
    // 使用存在的数组创建一个数组
    static CCArray* createWithArray(CCArray* otherArray);
    /**
     @brief   Generate a CCArray pointer by file
     @param   pFileName  The file name of *.plist file
     @return  The CCArray pointer generated from the file
     */
    // 从文件来创建一个数组指针
    static CCArray* createWithContentsOfFile(const char* pFileName);
    
    /*
     @brief The same meaning as arrayWithContentsOfFile(), but it doesn't call autorelease, so the
     invoker should call release().
     */
    // 由文件创建数组，但是不是自动释放对象
    static CCArray* createWithContentsOfFileThreadSafe(const char* pFileName);

    /** Initializes an array */
    // 初始化一个数组
    bool init();
    /** Initializes an array with one object */
    // 是否从一个对象初始化一个数组
    bool initWithObject(CCObject* pObject);
    /** Initializes an array with some objects */
    // 是否从一些对象初始化数组
    bool initWithObjects(CCObject* pObject, ...);
    /** Initializes an array with capacity */
    // 初始化一定容量的数组
    bool initWithCapacity(unsigned int capacity);
    /** Initializes an array with an existing array */
    // 从存在的数组初始化一个新的数组
    bool initWithArray(CCArray* otherArray);

    // Querying an Array
    // 查询一个数组

    /** Returns element count of the array */
    // 返回数组中元素的个数
    unsigned int count();
    /** Returns capacity of the array */
    // 返回容量
    unsigned int capacity();
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    // 返回指定对象的序号
    unsigned int indexOfObject(CCObject* object);
    /** Returns an element with a certain index */
    // 返回指定序号的元素
    CCObject* objectAtIndex(unsigned int index);
    /** Returns last element */
    // 返回最后的元素
    CCObject* lastObject();
    /** Returns a random element */
    // 返回一个随机元素
    CCObject* randomObject();
    /** Returns a Boolean value that indicates whether object is present in array. */
    // 返回一个对象是否在数组中
    bool containsObject(CCObject* object);
    /** @since 1.1 */
    bool isEqualToArray(CCArray* pOtherArray);
    // Adding Objects
    // 增加对象

    /** Add a certain object */
    // 增加一个指定对象
    void addObject(CCObject* object);
    /** Add all elements of an existing array */
    // 增加一个存在数组的元素
    void addObjectsFromArray(CCArray* otherArray);
    /** Insert a certain object at a certain index */
    // 插入一个对象，在知道指定序号
    void insertObject(CCObject* object, unsigned int index);

    // Removing Objects
    // 移除对象

    /** Remove last object */
    // 移除最后一个对象
    void removeLastObject(bool bReleaseObj = true);
    /** Remove a certain object */
    // 移除一个指定对象
    void removeObject(CCObject* object, bool bReleaseObj = true);
    /** Remove an element with a certain index */
    // 移除一个指定序号的元素
    void removeObjectAtIndex(unsigned int index, bool bReleaseObj = true);
    /** Remove all elements */
    //移除所有元素
    void removeObjectsInArray(CCArray* otherArray);
    /** Remove all objects */
    // 移除所有对象
    void removeAllObjects();
    /** Fast way to remove a certain object */
    // 快速移除一个指定对象
    void fastRemoveObject(CCObject* object);
    /** Fast way to remove an element with a certain index */
    // 快速移除一个指定序号的元素
    void fastRemoveObjectAtIndex(unsigned int index);

    // Rearranging Content
    // 重新整理内容

    /** Swap two elements */
    // 交换两个元素
    void exchangeObject(CCObject* object1, CCObject* object2);
    /** Swap two elements with certain indexes */
    // 交换两个指定序号的元素
    void exchangeObjectAtIndex(unsigned int index1, unsigned int index2);

    /** Replace object at index with another object. */
    // 用另一个对象替换一个指定序号的对象
    void replaceObjectAtIndex(unsigned int uIndex, CCObject* pObject, bool bReleaseObject = true);

    /** Revers the array */
    // 反向数组
    void reverseObjects();
    /* Shrinks the array so the memory footprint corresponds with the number of items */
    // 收缩阵列这样的内存占用量对应的项目数
    void reduceMemoryFootprint();
  
    /* override functions */
    // 重载虚函数
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    ccArray* data;
    CCArray();
    CCArray(unsigned int capacity);
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCARRAY_H__
