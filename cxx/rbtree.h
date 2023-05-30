/**
 * @file rbtree.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 红黑树定义文件
 * @version 1.0
 * @date 2023-05-13
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
/**
 * @brief 主要原理 红黑树 性质 根为黑，红结点只能接黑节点 到达任意叶子结点的路径经过黑的个数一定
 *        颜色翻转 只要两个儿子都是红 就变儿子为黑 然后变父亲为红 若有冲突就上滤
*/
#ifndef RBTREE_DEF_H_
#define RBTREE_DEF_H_
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#define _RBTREE_NAMESPACE_START namespace rb_tree_ {
#define _RBTREE_NAMESPACE_END  }


#define INFINITY    0x3f3f3f3f
#define NEGINFINITY -0x3f3f3f3f
_RBTREE_NAMESPACE_START
//ADT
enum ColorType{Red__,Black__};
typedef int ElemType;
typedef struct RedBlackNode
{
    ElemType                Element;
    struct RedBlackNode*    Left; 
    struct RedBlackNode*    Right;
    ColorType               Color; 
}RedBlackNode,*RedBlackTree;
typedef RedBlackNode* Position;
//Global Argument
Position NullNode=nullptr;
namespace {         // Static 函数
   void Doprint(RedBlackTree T)
   {
        if(T!=NullNode)
        {
            Doprint(T->Left);
            printf("%d ",T->Element);
            if(T->Left==NullNode&&T->Right==NullNode)
                printf("leaf %d ",T->Color);
            Doprint(T->Right);
        }
   }
   void InorderTraverse(RedBlackTree T)
   {
        Doprint(T->Right);      // For the right pointer of the root
   }
}
/**
 * @brief 初始化红黑树，同时建造nullnode与head结点 注意使用等号 我们使用一个root
 * @return RedBlackTree 
 */
RedBlackTree Initialize(void);
/**
 * @brief 自顶向下的插入 非模板实现
 * @param Item 
 * @param T 
 * @return RedBlackTree 
 */
RedBlackTree Insert(ElemType Item,RedBlackTree T);

_RBTREE_NAMESPACE_END


#endif // !RBTREE_DEF_H_

