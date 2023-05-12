/**
 * @file AvlTree.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 命名空间 avl_tree
 * @version 1.0
 * @date 2023-05-12
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#ifndef AVL_TREE__
#define AVL_TREE__

#include"avltree.h"
_AVLTREE_NAMESPACE_START
struct AvlNode{
    ElemType Element;
    struct AvlNode*Right;
    struct AvlNode*Left;
    int height;     // ! 特殊的数据点递归做法
};
inline int Max(int a,int b)
{   
    return a>b?a:b;
}
static int Height(Position P)
{
    if(P==NULL)
    return -1;  //注意
    return P->height;
}
inline void Print(AvlNode*node,int depth)
{
    for(int i=1;i!=6;++i)
        putchar('\t');
    printf("%d\n",node->Element);
}
inline void listDir(AvlTree T,int depth)
{
    if(T)
    {
        Print(T,depth);
        listDir(T->Left,depth+1);
        listDir(T->Right,depth+1);
    }
}
void ListDirectory(AvlTree T)
{
    listDir(T,0);
}
void InOrderTraverse(const AvlTree T)
{
    if(T)
    {
        InOrderTraverse(T->Left);
        printf("%d ",T->Element);
        InOrderTraverse(T->Right);
    }
}

AvlTree MakeEmpty(AvlTree T)
{
    if(T)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElemType X,AvlTree T)
{
    if(T)
    {
        if(X<T->Element)
        return Find(X,T->Left);
        else if(X<T->Element)
        return Find(X,T->Left);
        else
        return T;
    }
    return NULL;
}

Position FindMin(AvlTree T)
{
    if(T)
    {
        if(!T->Left)
            return T;
        else
            return FindMin(T->Left);
    }
    return NULL;
}
Position FindMax(AvlTree T)
{
    if(T)
    {
        if(!T->Right)
            return T;
        else
            return FindMin(T->Right);
    }
    return NULL;
}

ElemType Retrieve(Position T)
{
    return T->Element;
}

/**
 * @brief 执行右旋转 ，树原来是一个朝左下的一字树
 * @param K2 第一最小不平衡树
 * @return Position 
 */
static Position SingleRotateWithLeft(Position K2)
{
    Position K1;

    K1=K2->Left;
    K2->Left=K1->Right;
    K1->Right=K2;
    K2->height=Max(Height(K2->Right),Height(K2->Left))+1;
    K1->height=Max(Height(K1->Left),K2->height)+1;

    return K1;
}
static Position SingleRotateWithRight(Position K2)
{
    Position K1;

    K1=K2->Right;
    K2->Right=K1->Left;
    K1->Left=K2;        // 然后记得更新 高度注意中间的是没变的 这个就是一个简化
    K2->height=Max(Height(K2->Right),Height(K2->Left))+1;
    K1->height=Max(K2->height,Height(K1->Right))+1;

    return K1;
}
static Position DoubleRotateWithLeft(Position K3)
{
    /*K1,K2 也要旋转*/
    K3->Left=SingleRotateWithRight(K3->Left);
    /* 然后再选一次*/
    return SingleRotateWithLeft(K3);        // 思路很简单啊
}
static Position DoubleRotateWithRight(Position K3)
{
    
    K3->Right=SingleRotateWithLeft(K3->Right);
    return SingleRotateWithRight(K3);
}
/**
 * @brief 递归实现 AVL tree
 * @param X 插入元素    
 * @param T 平衡树结点指针
 * @return AvlTree 
 */
AvlTree Insert(ElemType X,AvlTree T)     
{
    if(T==NULL)
    {
        T=(AvlNode*)malloc(sizeof(AvlNode));
        T->Element=X;
        T->Left=T->Right=NULL;
    }
    else if(X<T->Element)
    {
        T->Left=Insert(X,T->Left);
        if(Height(T->Left)-Height(T->Right)==2) // 插入后检查是否超过 不需要绝对值可预见
            if(X<T->Left->Element)
                T=SingleRotateWithLeft(T);
            else        // 不用考虑因为= 不会改变
                T=DoubleRotateWithLeft(T);
    }
    else if(X>T->Element)
    {
        T->Right=Insert(X,T->Right);
        if(Height(T->Right)-Height(T->Left)==2)
            if(X>T->Right->Element)
                T=SingleRotateWithRight(T);
            else
                T=DoubleRotateWithRight(T);
    }
    T->height=Max(Height(T->Left),Height(T->Right))+1;  // ! +1 不要忘记
    return T;
}  
_AVLTREE_NAMESPACE_END

#endif // !AVL_TREE__