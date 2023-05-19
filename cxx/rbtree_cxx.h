/**
 * @file rbtree_cxx.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 红黑树的泛型实现
 * @version 1.0
 * @date 2023-05-15
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#ifndef RBTREE_XX_H_
#define RBTREE_XX_H_

#include<iostream>
#include<stdlib.h>
#include<utility>
#include<memory>
#define _RBTREE_XX_NAMESPACE_START  namespace rbtree_xx_ {
#define _RBTREE_XX_NAMESPACE_END    }

#define NEGINFINITY -0x3f3f3f3f
#define INFINITY    0x3f3f3f3f
_RBTREE_XX_NAMESPACE_START

//ADT
enum class Color:unsigned char{Red,Black};
template<typename K,typename V>
struct RedBlackNode{
    RedBlackNode(const std::pair<K,V>&data={},Color color=Color::Red):
            _pLeft(nullptr),_pRight(nullptr),_pParent(nullptr),
            _kv(data),_color(color){}

    RedBlackNode*_pLeft;    // 左子树的指针
    RedBlackNode*_pRight;   // 右子树的指针 
    RedBlackNode*_pParent;  //特有的父亲指针
    std::pair<K,V> _kv;     // 键值对
    Color _color;    

};

template<typename K,typename V>
struct RedBlackTree
{
    RedBlackTree():_rbtree(new RedBlackNode({},Color::Black)){}
    RedBlackTree(RedBlackNode<K,V>*pt):_rbtree(pt){}

    std::shared_ptr<RedBlackNode<K,V>>_rbtree;
    static constexpr RedBlackNode<K,V>*NullNode;
};
                                                    
_RBTREE_XX_NAMESPACE_END

#endif // !RBTREE_XX_H_

