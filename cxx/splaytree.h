/**
 * @file SplayTree.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 自顶向下伸展树的接口文件
 * @version 1.0
 * @date 2023-05-14
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * /
/**
*@brief 伸展树的方法主要有两种，第一种是自顶向下，第二种是自底向上，自底向上的伸展中，会出现向上向下两次遍历
*       同时还需要额外的指针存储，而自顶向下只要一个常量存储空间 所以实现自顶向下的伸展实现
*/
#ifndef SPLAY_TREE_H_
#define SPALY_TREE_H_
#include<iostream>
#include<stdlib.h>
#define _SPLAYTREE_NAMESPACE_START namespace splay_tree_{
#define _SPLAYTREE_NAMESPACE_END }
_SPLAYTREE_NAMESPACE_START
//Global argument

//ADT
struct SplayNode;
typedef struct SplayNode* SplayTree;
typedef int ElemType;

struct SplayNode{
    ElemType Element;
    SplayTree Right;
    SplayTree Left;
};
typedef struct SplayNode* Position;

//Global Argument
Position NullNode=nullptr;

//func API
inline void FatalError(char msg[])
{
    std::cerr<<msg<<std::endl;
    exit(EXIT_FAILURE);
}
/**
 * @brief 将伸展树置空
 * @param T 一棵伸展树
 * @return SplayTree 
 */
SplayTree MakeEmpty(SplayTree T);
/**
 * @brief 查找元素
 * @param X 待查找的元素
 * @param T 待查找的对象树
 * @return SplayTree 
 */
SplayTree Find(ElemType X,SplayTree T);
/**
 * @brief 找到树中的最大值，或者最小值
 * @param T 待查找的树
 * @return SplayTree 
 */
SplayTree FindMin(SplayTree T);
SplayTree FindMax(SplayTree T);
/**
 * @brief 初始化NullNode 全局变量 注意使用 SplayTree=Initailize();
 * @return SplayTree 
 */
SplayTree Initialize(void);

SplayTree Insert(ElemType X,SplayTree T);
SplayTree Remove(ElemType X,SplayTree T);
/**
 * @brief 得到树根的元素
 * @param T 待查找的树
 * @return ElemType 
 */
ElemType Retrieve(SplayTree T);
/**
 * @brief 中序遍历树
 * @param T 
 */
void InOrderTraverse(const SplayTree T);
_SPLAYTREE_NAMESPACE_END

#endif // !SPLAY_TREE_H_
