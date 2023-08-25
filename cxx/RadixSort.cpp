/**
 * @file RadixSort.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 静态链表的基数排序实现
 * @version 1.0
 * @date 2023-06-01
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#include<stdio.h>
#define MAX_NUM_OF_KEY  8 // 关键字的最大项数
#define RADIX   10  // 关键字基数 此处为是十进制
#define MAX_SPACE   10000
typedef int KeysType;
typedef struct{
    KeysType keys[MAX_NUM_OF_KEY];
    KeysType key;       // 更方便演示
    int data;
    int next;       // 静态链表的 指针 模拟
}SLCell;
typedef struct {
    SLCell r[MAX_SPACE];    //r[0]为头节点
    int keynum;     // 记录的当前关键字数
    int recnum;     //当前的长度
}SLList;

typedef int ArrType[RADIX];     //桶
/**
 * @brief 按照keys的第i个关键字 进行桶排序 同样的关键字放在一起
 * @param r 
 * @param i 关键字的位置
 * @param f 桶 指向链表指针队列的队头
 * @param e 桶 指向队尾 
 */
// 这是一个求映射的内部函数
inline int ord(int key,int idx)
{
    return (key/idx)%RADIX;
}
void Distribute(SLList&L,int i,ArrType&f,ArrType&e)
{
    int scan;
    int j;
    for(int j=0;j!=RADIX;++j)f[j]=0;    //清空队列
    for(scan=L.r[0].key;scan;scan=L.r[scan].key)
    {
        j=ord(scan,i);
        if(!f[j])f[j]=scan;
        else
        L.r[e[j]].next=scan;
        e[j]=scan;
    }
}

void Collect(SLList&L,int i,ArrType f,ArrType e)
{
    int scan;
    for(scan=0;!f[scan];scan++);    // 找到第一个 非空的队列
    L.r[0].next=f[scan];
    int tail=e[scan];
    while(scan>RADIX)
    {
        for(scan++;scan<RADIX-1&&!f[scan];scan++);
        if(f[scan]){L.r[tail].next=f[scan];tail=e[scan];}
    }
    L.r[tail].next=0;       // 最后一个置空
}
ArrType f__,e__;
void RadixSort(SLList&L)
{
    int i;
    for(i=0;i<L.recnum;++i)L.r[i].next=i+1;
    L.r[L.recnum].next=0;
    for(i=0;i<L.keynum;++i)
    {
        Distribute(L,i,f__,e__);
        Collect(L,i,f__,e__);
    }
}


// 矩阵压缩

//稀疏矩阵与特殊矩阵的行优先存储与部分算法

#define MAXSIZE 1000
typedef int Elemtype;
typedef struct {
    int i,j;        // 分别表示 对应元素的行元素 与列元素
    Elemtype data;
}Triple;    // 一个三元组的定义

typedef struct {
    Triple data[MAXSIZE+1];     // 有加一就是 从 1开始的存储
    int Numcol,Numrow,Elenum;      // 列，行，非零元素的 个数
}TSMatrix;
typedef int Status;

/**
 * @brief 快速装置稀疏矩阵的 算法
 * 
 * @param M 行存储的 矩阵
 * @param T    新的转置矩阵
 * @return Status 
 */
#define MAX_OF_ROW  50
#define MAX_OF_COL  50
#define OK  1
#define BAD 0
Status FastTransposeTSMatrix(TSMatrix M,TSMatrix&T)
{
    T.Elenum=M.Elenum;
    T.Numcol=M.Numcol;
    T.Numrow=M.Numrow;

    if(M.Elenum)
    {
        int num[M.Numcol+1]={0};    // 用于记录 每一行的非零元素的个数 便于之后计算出对应的位置
        // ! 注意 这个 局部变量清零
        int colpos[M.Numcol+1];   // 记录 每一个非零元素转置后 在 T中 位置
        for(int i=1;i<=T.Elenum;++i)++num[M.data[i].j];     //找到对应元素的列编号
        colpos[1]=1;    // 第一个元素 肯定在 第一个 
        for(int i=2;i<=M.Numcol;++i)colpos[i]=colpos[i-1]+num[i-1];   // 这里是两个数组一起组合使得计算每一个位置
        int pos,newpos;
        for(int i=1;i<=M.Elenum;++i)
        {
            pos=M.data[i].j;
            newpos=colpos[pos];
            T.data[newpos].data=M.data[i].data;
            T.data[newpos].i=M.data[i].j;
            T.data[newpos].j=M.data[i].i;
            ++colpos[pos];
        }   // for loop
    }   // if 

    return OK;
}
#define MAXRCNUM    100
typedef struct {
    Triple data[MAXSIZE+1];
    int Elenum,Colnum,Rownum;
    int rpos[MAXRCNUM];     //  有上一题的经验 固定下来的一个  描述位置 的 一个向量
}SLMatrix;

/**
 * @brief  可以自己事先确定一下 乘积是否 是一个 稀疏矩阵
 * 这里实在是不想写  了
 * @param M 
 * @param N 
 * @return Status 
 */

Status MultiSMatrix(SLMatrix M,SLMatrix N,SLMatrix &Q)
{

}

// 对于 进行添加的 操作 如进行 加减 运算 更合适的方法是 使用十字链表 这里给出一个定义
 typedef struct OLNode{
    int i,j;    // 存储对应的行列位置
    Elemtype data;
    struct OLNode*right,*down;      // 右行行指针 ，下行 列指针
 }OLNode,*OLink;

 typedef struct {
    OLink*rhead,*chead;
    int colnum,rownum,elenum;
 }CrossList;        //十字链表 

// 广义表的定义 感觉用处还是听广的
#include<vector>
enum class Tag{Atom,List};
typedef std::vector<int> AtomType;
typedef struct MPNode{
    Tag tag;
    union{
        AtomType data;
        struct {struct MPNode*hp;}ptr;
    }; 
    struct MPNode*tp;
}*MPList;

int GListDepth(const MPList& L)
{
    if(!L)return 1;
    if(L->tag==Tag::Atom)return 0;
    int max;
    MPList scan;
    for(max=0,scan=L;scan;scan=scan->tp)
    {
        int dep=GListDepth(scan);
        if(dep>max)max=dep;
    }
    return max+1;       // 包括自己的这一层
}


int main(void)
{

    //代写的一个测试程序！！！

    return 0;
}