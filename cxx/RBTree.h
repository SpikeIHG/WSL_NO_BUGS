/**
 * @file RBTree.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 红黑树接口文件
 * @version 1.0
 * @date 2023-05-13
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#ifndef RBTREE_H_
#define RBTREE_H_

#include"rbtree.h"

_RBTREE_NAMESPACE_START
inline void FatalError(char msg[])
{
    std::cerr<<msg<<std::endl;
    exit(EXIT_FAILURE);
}

RedBlackTree Initialize(void)
{
    RedBlackTree T;
    if(nullptr==NullNode)
    {
        NullNode=(RedBlackNode*)malloc(sizeof(RedBlackNode));
        if(!NullNode)
            FatalError("Allocate Failed!");
        NullNode->Element=INFINITY;
        NullNode->Right=NullNode->Left=NullNode;
        NullNode->Color=Black__;      // ? we assume that all the leaf nodes are black
    }
    /* Allocate the root node */
    T=(RedBlackNode*)malloc(sizeof(RedBlackNode));
    if(!T)
        FatalError("Allocate Failed!");
    T->Element=NEGINFINITY;
    T->Color=Black__;     // the root must be black!
    T->Left=T->Right=NullNode;

    return T;   // ? attention T=initialize()
}

namespace {
    Position SingleRotateWithLeft(Position K2)
    {
        Position K1;

        K1=K2->Left;
        K2->Left=K1->Right;
        K1->Right=K2;

        return K1;
    }
    Position SingleRotateWithRight(Position K2)
    {
        Position K1;

        K1=K2->Right;
        K2->Right=K1->Left;
        K1->Left=K2;

        return K1;
    }
    /**
     * @brief 真正的旋转程序 很巧妙注意 因为有了父节点我们可以在内部考虑大小
     * @param Item 需要插入的元素
     * @param Parent 发生旋转的树的父节点 因为需要改变所以我们传父节点的值
     * @return Position 
     */
    Position Rotate(ElemType Item,Position Parent)
    {
        if(Item<Parent->Element)
        {
            return Parent->Left=Item<Parent->Left->Element?
                    SingleRotateWithLeft(Parent->Left):
                    SingleRotateWithRight(Parent->Left);
        }
        else
        {
            return Parent->Right=Item>Parent->Right->Element?
                    SingleRotateWithRight(Parent->Right):
                    SingleRotateWithLeft(Parent->Right);
        }
        
    }

    Position X,P,GP,GGP;        // cur and parent and grand ggrand
    /**
     * @brief 改变颜色 也就是核心实现
     * @param Item 
     * @param T 树的头节点
     */
    void HandleReorient(ElemType Item,RedBlackTree T)       //No x for x is staic 
    {
        X->Color=Red__;       //convert the color
        X->Left->Color=X->Right->Color=Black__;

        if(P->Color==Red__)     // conflict happens!
        {
            GP->Color=Red__;        // don't forget
            if((Item<GP->Element)!=(Item<P->Element))
                P=Rotate(Item,GP);      // a little difference from the former!
            X=Rotate(Item,GGP);     // we need  to change the GGP   
            X->Color=Black__;       // it's defined!!
        }
        /* we need to assure the root is black especially at first three steps !*/
        T->Right->Color=Black__;
    }
}
/**
 * @brief 插入元素
 * @param Item 需要插入的元素
 * @param T 树的根节点
 * @return RedBlackTree 
 */
RedBlackTree Insert(ElemType Item,RedBlackTree T)
{
    X=P=GP=T;     // 第一步 进行一个初始化 GGP= head
    NullNode->Element=Item;     // as a sign for null !! very smart!

    while(X->Element!=Item)     //condition not null x is cur
    {
        GGP=GP;GP=P;P=X;    // update
        if(Item<X->Element)
            X=X->Left;
        else        // when come the node for the Neg_infinity must > so the right!!!
            X=X->Right;     
        if(X->Right->Color==Red__&&X->Left->Color==Red__)
            HandleReorient(Item,T);
    }
    if(X!=NullNode)     // already exist !
        return NullNode;
    X=(RedBlackNode*)malloc(sizeof(RedBlackNode));
    if(!X)
        FatalError("Allocate Failed!");
    X->Element=Item;
    X->Left=X->Right=NullNode;

    if(Item<P->Element)
        P->Left=X;
    else
        P->Right=X;     // the first must be Head->RIght!! good!
    
    HandleReorient(Item,T);     // why? for we need to color the X red and check!!!
    return T;
}

_RBTREE_NAMESPACE_END




#endif // !RBTREE_H_


