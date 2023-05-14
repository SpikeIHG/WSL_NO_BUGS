/**
 * @file splaytree.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 自顶向下伸展树
 * @version 1.0
 * @date 2023-05-12
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include"splaytree.h"
_SPLAYTREE_NAMESPACE_START
SplayTree MakeEmpty(SplayTree T)
{
    if(T)
    {
        MakeEmpty(T->Right);
        MakeEmpty(T->Left);
        free(T);
    }
    return NullNode;
}
SplayTree Find(ElemType X,SplayTree T)
{
    if(T)
    {
        if(X<T->Element)
            return Find(X,T->Left);
        else
            return Find(X,T->Right);
    }
    return NullNode;
}
SplayTree FindMax(SplayTree T)
{
    if(T->Right!=NullNode)
        return FindMax(T->Right);
    else
        return T;
}
SplayTree FindMin(SplayTree T)
{
    if(T->Left!=NullNode)
        return FindMin(T->Left);
    else
        return T;
}
SplayTree Initialize(void)
{
    if(nullptr==NullNode)
    {
        NullNode=(SplayNode*)malloc(sizeof(SplayNode));
        if(!NullNode)
            FatalError("Allocate failed!");
        NullNode->Left=NullNode->Right=NullNode;       //? 绝妙
    }
    return NullNode;
}
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
SplayTree       // 核心功能函数
Splay(ElemType Item,Position X)
{
    static struct SplayNode Header; // ? Awesome!   we insert many times so static to save space!!! very important
    Position LeftTreeMax,RightTreeMin;  // As you see,literally, dynamic record

    Header.Right=Header.Left=NullNode;  //? Excellent!!
    LeftTreeMax=RightTreeMin=&Header;
    NullNode->Element=Item;     //? Fabulous

    while(X->Element!=Item)     //? check null perfect!!!
    {
        if(Item<X->Element)
        {
            if(Item<X->Left->Element)
                X=SingleRotateWithLeft(X);    //? Single rotate to adpte
            if(X->Left==NullNode)    // check if needed stop 
                break;  //? with the condition expr total two situations
            /* Link Right */
            RightTreeMin->Left=X;       //Logical null though there is a pointer!
            RightTreeMin=X;         // dynamic update
            X=X->Left;          // cur to move the direction is under the comparision!!! so defined
        }
        else{
            if(Item>X->Right->Element)
                X=SingleRotateWithRight(X);
            if(X->Right==NullNode)
                break;
            /* Link Left */
            LeftTreeMax->Right=X;
            LeftTreeMax=X;
            X=X->Right;
        }
    }
    /* Assemble */
    //For case break and NullNode
    LeftTreeMax->Right=X->Left;
    RightTreeMin->Left=X->Right;
    X->Left=Header.Right;
    X->Right=Header.Left;      //Attention header like a node in list and the order attention

    return X;

}

SplayTree Insert(ElemType Item,SplayTree T)
{
    static Position NewNode=nullptr;

    if(NewNode==nullptr)
    {
        NewNode=(Position)malloc(sizeof(SplayNode));
        if(!NewNode)
            FatalError("Allocate Failed!!");
    }
    NewNode->Element=Item;
    // Tree is nullnode
    if(T==NullNode)
    {
        NewNode->Left=NewNode->Right=NullNode;
        T=NewNode;
    }
    else{               // no operation when equal
        T=Splay(Item,T);
        if(Item<T->Element)     //Pay attention we use the node as root! Awesome!
        {
            NewNode->Left=T->Left;
            NewNode->Right=T;
            T->Left=NullNode;
            T=NewNode;      // needed for the unit return T!
        }
        else if(Item>T->Element)    //!  Don't forget!!!
        {
            NewNode->Right=T->Right;
            NewNode->Left=T;
            T->Right=NullNode;
            T=NewNode;
        }
        else
            return T;
    }
    NewNode=nullptr;      //   recyclable ! perfect save memory!!!
    return T;
}

SplayTree
Remove(ElemType Item,SplayTree T)
{
    Position NewTree;

    if(T!=NullNode)
    {
        T=Splay(Item,T);
        if(Item==T->Element)    // When found
        {
            if(T->Left==NullNode)
                NewTree=T->Right;
            else{
                NewTree=T->Left;
                /* because we need the leftmin so we splay */
                NewTree=Splay(Item,NewTree);
                NewTree->Right=T->Right; 
                //!assured the right is null because item is the first bigger no more bigger!!
            }
            free(T);
            T=NewTree;
        }
    }
    return T;  
}

void InOrderTraverse(const SplayTree T)
{
    if(T!=NullNode)
    {
        InOrderTraverse(T->Left);
        printf("%d ",T->Element);
        InOrderTraverse(T->Right);
    }
}

ElemType Retrieve(SplayTree T)
{
    if(T!=NullNode)
        return T->Element;
}
_SPLAYTREE_NAMESPACE_END

#endif // !SPLAYTREE_H