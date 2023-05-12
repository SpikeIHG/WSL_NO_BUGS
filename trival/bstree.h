/**
 * @file SBTree.c
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-10
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#ifndef SBTREE__H
#define SBTREE__H
#define OK  1
#define BAD 0
#define nullptr 0
#include<stdlib.h>
typedef int Status;

typedef struct node{
    int data;
    struct node*lchild,*rchild;
}BiTNode,*BiTree;

void InOrderTraverse(BiTree bt,void(*f)(BiTNode*))
{
    if(bt)
    {
        InOrderTraverse(bt->lchild,f);
        f(bt);
        InOrderTraverse(bt->rchild,f);
    }
}
/**
 * @brief 
 * 
 * @param T 查找的对象的地址 
 * @param key   查找关键字
 * @param f     用于保存考察结点的父节点便于返回
 * @param p     保留最后一个搜索的结点
 * @return Status 
 */
Status SearchBST(BiTree T,int key,BiTree f,BiTree*p)    // ! f 用来记载我们的上一个 父节点
{
    if(!T)
    {
        *p=f;
        return BAD;
    }
    else if(key==T->data)
    {
        *p=T;
        return OK;
    }
    else if(key<T->data)
    return SearchBST(T->lchild,key,T,p);
    else
    return SearchBST(T->rchild,key,T,p);
}

Status InsertBST(BiTree *T,int key)
{
    BiTree p,s;
    if(!SearchBST(*T,key,NULL,&p))
    {
        s=(BiTree)malloc(sizeof(BiTNode));
        s->data=key;
        s->lchild=s->rchild=nullptr;
        if(!p)
        *T=s;       //! 这个就是为什么要传入指针的原因
        else if(key<p->data)
        p->lchild=s;
        else
        p->rchild=s;
        return OK;
    }
    else
    return BAD;
}

Status delete_(BiTree *p)
{
    BiTree q,s;
    if((*p)->lchild==NULL)
    {
        q=(*p);(*p)=(*p)->rchild;free(q);
    }
    else if((*p)->rchild==NULL)
    {
        q=(*p);(*p)=(*p)->lchild;free(q);
    }
    else{
        q=*p;s=(*p)->lchild;
        while(s->rchild)
        {
            q=s;s=s->rchild;
        }
        (*p)->data=s->data;
        if(q!=*p)
            q->rchild=s->lchild;
        else
            q->lchild=s->lchild;
        free(s);
    }
    return OK;
}

/**
 * @brief 删除一个元素 三种情况
 * 
 * @param T 
 * @param key 
 * @return Status 
 */
Status DeleteBTS(BiTree*T,int key)
{
    if(!*T)
        return BAD;
    if(key==(*T)->data)
        return delete_(T);
    else if(key<(*T)->data)
        return DeleteBTS(&(*T)->lchild,key);
    else
        return DeleteBTS(&(*T)->rchild,key);
}

#endif // !SBTREE__H
