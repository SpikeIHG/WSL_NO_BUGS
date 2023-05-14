/**
 * @file avltree.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-12
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  ! 实现一下平衡树 ，自顶向下伸展树，以及有可能的话，红黑树，作为自己的lib
 */
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define _AVLTREE_NAMESPACE_START namespace avl_tree {
#define _AVLTREE_NAMESPACE_END  }

_AVLTREE_NAMESPACE_START

using ElemType=int;
struct AvlNode;
typedef struct AvlNode*Position;
typedef struct AvlNode*AvlTree;

void ListDirectory(const AvlTree);
void InOrderTraverse(const AvlTree);
AvlTree MakeEmpty(AvlTree);
Position Find(ElemType,AvlTree);
Position FindMin(AvlTree);
Position FindMax(AvlTree);
AvlTree Insert(ElemType,AvlTree);
AvlTree Delete(ElemType,AvlTree);
ElemType Retrieve(Position P);


_AVLTREE_NAMESPACE_END

#endif // !AVLTREE_H_

