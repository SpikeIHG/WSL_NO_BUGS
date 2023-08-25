/**
 * @file Sort.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 数据结构中的排序与实现
 * @version 1.0
 * @date 2023-05-30
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#include<stdio.h>
#include<string>
#include<random>
#include<stdlib.h>
#define MAXSIZE 20
using KeyType=int;
using ElemType=int;
using Status=int;
using OtherInfo=std::string;
typedef struct {
    KeyType key;
    OtherInfo data;
}RecType;
typedef struct{
    RecType rec[MAXSIZE+1];     // rec[0]作为监视哨
    int length;
}Sqlist;

/**
 * @brief 简单（线性）插入排序
 * 最好情况 递增有序 最坏情况 递减 平均o(n^2) 辅助空间常量 稳定的
 * @param arr 数组
 * @param length 长度
 */
void InsertSort(ElemType arr[],int length)
{
    int i,j;
    
    for(i=2;i<=length;++i)
    {
        arr[0]=arr[i];  //先将该元素放入r[0]中
        j=i-1;          //i-1之前的元素都是排好序的

        while(arr[0]<arr[j])
        {
            arr[j+1]=arr[j];      //从小到大排 满足就后移
            --j;
        }
        arr[j+1]=arr[0];    // 注意对应的位置被多减了一个1
    }
}
/**
 * @brief 折半插入
 * 稳定的 n^2 只是减少了比较次数 但是移动次数 还是 n^2 注意 由两部分决定
 * 希尔 突破 n^2 但是高于 对数 不稳定 常量空间
 * @param L 线性表已经定义的数据结构
 */
void BInsertSort(Sqlist&L)
{
    int i,j;
    int high,low,mid;
    for(i=2;i<=L.length;++i)
    {
        L.rec[0]=L.rec[i];      // 放入监视哨
        low=1;high=i-1;     //确定范围
        while(low<=high)
        {
            mid=(low+high)/2;      // 第一步一定折半
            if(L.rec[0].key<L.rec[mid].key)
                high=mid-1;
            else
                low=mid+1;  // 这里没有当相等的时候退出 是为了和后面统一简化代码 但是适合重复度小的情况
        }//while loop
        // high 和 low 一定只想距1
        for(j=i-1;j>=low;j--)L.rec[j+1]=L.rec[j];
        L.rec[high+1]=L.rec[0];
    } // for loop
} //BInsertSort

/**
 * @brief 冒泡排序
 * 元素 从 0 开始 
 * @param arr 
 * @param length 
 */
void BubbleSort(ElemType arr[],int length)
{
    int i;
    while(length--)
    {
        for(i=0;i!=length;++i)
        {
            if(arr[i+1]<arr[i])
            {
                ElemType tmp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=tmp;
            }
        }
    }
}
// 改进的冒泡排序 稳定的
void PBubbleSort(ElemType arr[],int length)
{
    int i,j,swap;   //swap 作为标记 如果 有一次swap已经为 0 了说明已经有序 不需要再继续了
    ElemType tmp;
    j=1;        // 第一趟
    do{
        swap=0;
        for(i=0;i<length-j;++i)
        {
            if(arr[i+1]<arr[i])
            {
                tmp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=tmp;
                swap=1;
            }
        } // for loop
        ++j;
    }while(j<length&&swap);
}
/**
 * @brief 快速排序 三个while 不稳定 对数空间复杂度 最坏情况可能为n^2
 * 
 * @param arr 
 * @param l 数组的左端
 * @param r 数组的右端
 */
inline void my_qsort(ElemType arr[],int l,int r)
{
    ElemType mid=arr[(l+r)/2];  // pivot 取中间的
    ElemType tmp;
    int i=l;
    int j=r;
    do{     // 主要的内容
        while(arr[i]<mid)++i;
        while(arr[j]>mid)--j;
        if(i<=j)
        {
            tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
            ++i;--j;        // 不要忘记了
        }
    }while(i<=j);       //while loop 注意等号
    if(i<r)my_qsort(arr,i,r);
    if(l<j)my_qsort(arr,l,j);
}
/**
 * @brief 另外一种思路的快速排序
 * 上课讲的快速排序
 * @param arr 
 * @param low 
 * @param high 
 */
inline void mysort(ElemType arr[],int low,int high)
{
    int i,j;
    ElemType pivot;
    if(low<high)    // 递归进行的判断
    {
        i=low;j=high;pivot=arr[i];      //以第一个作为pivot
        do{
            while(i<j&&arr[j]>=pivot)--j;
            if(i<j)
            {
                arr[i]=arr[j];++i;   //表明下一个开始 j不能改变了保留
                while(i<j&&arr[i]<=pivot)++i;
                if(i<j)
                {
                    arr[j]=arr[i];--j;  // 从j开始了
                }
            }
        }while(i!=j);   //while loop 当两者未相遇

        arr[i]=pivot;     //最后返回
        mysort(arr,i+1,high);
        mysort(arr,low,i-1);
    }
}
void quicksort(ElemType arr[],int length)
{
    my_qsort(arr,0,length-1);
}

void quicksort_(ElemType arr[],int length)
{
    mysort(arr,0,length-1);
}
// 快速排序的潜在优化  按照大话数据结构的思路来
/**
 * @brief 划分函数 第一版 演示思路 先以第一个为枢纽元 然后左右依次交换
 * @param L 
 * @param low 
 * @param high 
 */
inline void swap_(Sqlist &L,int a,int b)
{
    auto tmp=L.rec[a];
    L.rec[a]=L.rec[b];
    L.rec[b]=tmp;
}

int Partition_1(Sqlist&L,int low,int high)
{
    int pivotkey=L.rec[low].key;

    while(low<high)
    {
        while(low<high&&pivotkey<=L.rec[high].key)--high;
        swap_(L,high,low);
        while(low<high&&pivotkey>=L.rec[low].key)++low;
        swap_(L,low,high);
    }
    return low;     // 最终退出时 high==low 一定成立的
}

void Qsort(Sqlist&L,int low,int high)
{
    int pivot;
    if(low<high)
    {
        pivot=Partition_1(L,low,high);
        Qsort(L,low,pivot-1);       // 注意一个是减一，一个是加一
        Qsort(L,pivot+1,high);
    }
}
/**
 * @brief 顺序表是以第一个元素开始存储的
 * @param L 
 */
void QuickSort(Sqlist&L)
{
    Qsort(L,1,L.length);    // 这里是以第一个元素开始存储的
}
// 优化枢纽的选择 因为固定位置的选择 可能很大程度 取决于 随机的运气 所以采用三数比较法
//如果对应很大的排序队伍可以采用 9数取中
#define MAX_PIVOT_LIMIT     101     // 九数取中的阈值
/**
 * @brief 三数取中与九数取中的优化 划分
 * @param L 
 * @param low 
 * @param high 
 * @return int 
 */
int Partition_2(Sqlist&L,int low,int high)
{
    int pivotkey;
    if(high-low<MAX_PIVOT_LIMIT)
    {
        // 可以有的判断组合很多 我们采用三个if判断
        int m=(high+low)/2;
        if(L.rec[low].key>L.rec[high].key)
            swap_(L,high,low);
        if(L.rec[m].key>L.rec[high].key)
            swap_(L,m,high);
        if(L.rec[m].key>L.rec[low].key)
            swap_(L,m,low);
    }
    else        //九数 感觉比较太多了 没有必要 可以写个简答的插入排序来找到这五个值的中值
    {
        int tmp[5];
        int mm=(low+high)/2;
        tmp[0]=L.rec[(low+high)/2].key;
        tmp[1]=L.rec[(low+mm)/2].key;
        tmp[2]=L.rec[(mm+high)/2].key;
        tmp[3]=L.rec[low].key;
        tmp[4]=L.rec[high].key;
        InsertSort(tmp,5);
        swap_(L,low,tmp[2]);
    }
    pivotkey=L.rec[low].key;        // 保持与之前的统一

    while(low<high)
    {
        while(low<high&&pivotkey<=L.rec[high].key)--high;
            swap_(L,high,low);  // 其实就是最终的 不需要交换 而是直接赋值即可
        while(low<high&&pivotkey>=L.rec[low].key)++low;
            swap_(L,low,high);
    }

    return low;
}
//优化不必要的交换 
int Partition_3(Sqlist&L,int low,int high)
{
    int pivotkey;
    if(high-low<MAX_PIVOT_LIMIT)
    {
        // 可以有的判断组合很多 我们采用三个if判断
        int m=(high+low)/2;
        if(L.rec[low].key>L.rec[high].key)
            swap_(L,high,low);
        if(L.rec[m].key>L.rec[high].key)
            swap_(L,m,high);
        if(L.rec[m].key>L.rec[low].key)
            swap_(L,m,low);
    }
    else        //九数 感觉比较太多了 没有必要 可以写个简答的插入排序来找到这五个值的中值
    {
        int tmp[5];
        int mm=(low+high)/2;
        tmp[0]=L.rec[(low+high)/2].key;
        tmp[1]=L.rec[(low+mm)/2].key;
        tmp[2]=L.rec[(mm+high)/2].key;
        tmp[3]=L.rec[low].key;
        tmp[4]=L.rec[high].key;
        InsertSort(tmp,5);
        swap_(L,low,tmp[2]);
    }
    pivotkey=L.rec[low].key;        // 保持与之前的统一
    L.rec[0]=L.rec[low];
    while(low<high)
    {
        while(low<high&&pivotkey<=L.rec[high].key)--high;
            L.rec[low]=L.rec[high];
        while(low<high&&pivotkey>=L.rec[low].key)++low;
            L.rec[high]=L.rec[low];
    }
    L.rec[low]=L.rec[0];
    return low;
}
// 优化小数组排序 选择插入排序
void Qsort2(Sqlist&L,int low,int high)
{
    int pivot;
    if(high-low>MAX_PIVOT_LIMIT)
    {
        pivot=Partition_3(L,low,high);
        Qsort2(L,low,pivot-1);
        Qsort(L,pivot+1,high);
    }
    else
    //InsertSort()      // 自己去完善一下吧
    ;
}
// !最后一个尾递归有点惊艳
void Qsort3(Sqlist&L,int low,int high)
{
    int pivot;
    while(low<high)
    {
        pivot=Partition_3(L,low,high);
        Qsort3(L,low,pivot-1);
        low=pivot+1;        // 相当于 Qsort(pivot+1,high)   low 此时可以赋新值
    }
}
void QuickSort_pro(Sqlist&L)
{
    Qsort3(L,1,L.length);
}

/**
 * @brief 选择排序 交换次数很少 
 * 树形选择排序 log
 * @param arr 
 * @param length 
 */
void SelectSort(ElemType arr[],int length)
{
    int i,j,min;
    ElemType tmp;
    for(i=0;i!=length;++i)
    {
        min=i;
        for(j=i+1;j!=length;++j)
        if(arr[j]<arr[min])
            min=j;
        if(min!=i)
        {
            tmp=arr[min];
            arr[min]=arr[i];
            arr[i]=tmp;
        }
    }
}

void HeapAdjust(ElemType arr[],int start,int end)
{
    ElemType tmp=arr[start];
    for(int i=start*2;i<=end;i*=2)
    {
        if(i+1<=end&&arr[i]<arr[i+1])++i;
        if(tmp<arr[i])
        {
            arr[start]=arr[i];
            start=i;
        }
        else
            break;
    }
    arr[start]=tmp;
}
void heapsort(ElemType arr[],int length)
{
    for(int i=length/2;i>=1;--i)
        HeapAdjust(arr,i,length);       // 建堆
    ElemType tmp;

    for(int i=1;i<=length;++i)
    {
        tmp=arr[1];
        arr[1]=arr[length-i+1];
        arr[length-i+1]=tmp;
        HeapAdjust(arr,1,length-i);
    }
}

#define MAXSIZE    101
/**
 * @brief 归并程序 核心程序 就是讲一个的两个部分归并到一个中
 * @param SR 源
 * @param TR 得到的有序的
 * @param i 起始的序号
 * @param m SR 的中间
 * @param n TR 的结束
 */
void Merge(ElemType SR[],ElemType TR[],int i,int m,int n)
{
    int j,k,l;  // k 是 TR的下标
    for(j=m+1,k=i;k<=m&&j<=n;++k)
    {
        if(SR[i]<SR[j])
        TR[k]=SR[i++];
        else
        TR[k]=SR[j++];
    }
    while(i<=m)TR[k++]=SR[i++];
    while(j<=n)TR[k++]=SR[j++];
}
void Msort(ElemType SR[],ElemType TR[],int s,int t)
{
    int m;
    ElemType TR2[MAXSIZE+1];
    if(s==t)
        TR[s]=SR[s];        // 这里有点容易出错
    else
    {
        m=(s+t)/2;
        Msort(SR,TR2,s,m);
        Msort(SR,TR2,m+1,t);
        Merge(TR2,TR,s,m,t);
    }
}
// 非递归实现 归并排序
void MergePass(int SR[],int TR[],int s,int n)
{
    int i=1;
    int j;

    while(i<=n-2*s+1)
    {
        Merge(SR,TR,i,i+s-1,i+2*s-1);
        i+=2*s;
    }
    if(i<n-s+1)
        Merge(SR,TR,i,i+s-1,n);
    else
        for(j=i;j<=n;++j)
        TR[j]=SR[j];
}
/**
 * @brief 非递归实现 归并排序 的主程序
 * 
 * @param arr 
 * @param length 
 */

void MSort2(ElemType arr[],int length)
{
    int*TR=(ElemType*)malloc(sizeof(ElemType)*(MAXSIZE+1));
    int k=1;        // 相当于是步长
    while(k<length)
    {
        MergePass(arr,TR,k,length);
        k*=2;
        MergePass(TR,arr,k,length);
        k*=2;
    }
}




int main(void)
{
    // 测试的样例 不过我的数据结构似乎没有统一  见谅！
    //std::cin.tie(nullptr);
    std::default_random_engine e(4335346);
    std::uniform_int_distribution<unsigned int> sample(0,40);

    ElemType a[15];
    for(int i=0;i!=15;++i)
        a[i]=sample(e);
    quicksort(a,15);
    for(auto b=std::begin(a);b!=std::end(a);++b)
        printf("%d ",*b);
        
    return 0;
}