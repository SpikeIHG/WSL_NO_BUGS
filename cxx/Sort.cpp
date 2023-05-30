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

int main(void)
{
    
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