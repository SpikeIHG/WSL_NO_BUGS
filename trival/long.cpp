/**
 * @file long.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief So long since the last coding
 * @version 1.0
 * @date 2023-08-21
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#include<stdio.h>
#include<iostream>
//? 仅仅作为温习CXX 的作用 重读书 希望能够压缩 并且形成自己的理解和自己cpp哲学
//? 之后我就会深入学习 python了 只有这样才能够更加深刻地理解语言的一些差异 然后就是学习更加具体的东西 网络 系统

/*c++ 静态语言 编译检查变量 所以要声明 而python是运行时检查 所以不用 也就是性能差异的原因
类型决定数据的性质 以及 可执行的操作
c++ 的内置类型 整型 浮点型 空类型 具体实现与机器有关 然后底层原理是精妙的布尔代数 */
void test_0(void);


int main(void)      // 系统函数 return也是一样
{
    int val_1;          // 声明 定义的理解 全局变量的 理解
    long long meta_val;
    double this_is_float_num;

    unsigned int this_is_tricky;        // 有无符号 注意一些常见的bug 简省技巧 
                                        //通常都是默认的有符号 并且应该减少无符号的情况
    //! WHY for the 类型转换 有截断 无符号的变化 等等

    //! litreal 字面量的定义  就是一眼便知  十进制 八进制0 十六进制0x 不区分大小写 浮点数 e10 可以识别的 下面是一个测试函数

    //test_0();

    /* 2===================================================================================================*/

    //! 变量
    // value 有点只读 的含义 所以在变量命名时 可以注意一下
    //! 初始化 理解 定义后变量就可以使用  初始化时定义一个变量时给予值 而赋值是给一个值并擦去 就是不一样在cxx
    int a2=0;
    int b2={0};
    int c2{0};      // 最好方案 可以检查
    int d2(0);
    double ld_2=1.3455;
    int error_candidate{ld_2};
    int err0r_2={ld_2};         // 好吧没有报错

    // ! 默认初始化 在任何函数之外的是一个默认初始化为0 在函数内部的内置变量不会初始化 而至于类类型通常由类设计者决定 会初始化

    // 声明与定义的区别 声明只是告诉了编译器 而 定义是实际创建了空间 多个声明一个定义 extern

    //Scope 作用域 嵌套 擦拭 全局 局部

    /*3================================================================================================*/
    //! 引用
    int obj{1000};
    int &ref_val_3=obj;     //! 引用即别名 定义时就必须要初始化 且不是对象不能引用引用的引用
    int a_3{390},b_3{1003};
    int &ref_a_3=a_3,&ref_b_3=b_3;      // 注意逗号的这个bug
    //! 指针是一个对象 最大区别 一种类型 有相关性质32位 以及定义的可执行操作 加 减
    //! 初始化 所有指针 甚至是所有的变量 不要哦访问空指针

    //! 复杂声明 从右往左读


}

/**
 * @brief 检查是否能够检查浮点数
 * 
 */
void test_0(void)
{
    double input_value;
    std::cout<<"请以e后缀的科学技术法输入一个浮点数来检验c能否读取"<<std::endl;
    if(std::cin>>input_value)
    std::cout<<input_value<<'\n'<<"good";
    else
    std::cout<<"BAD";
    std::cout<<std::endl;
}


/**
 * @brief review the Syntx of CXX
 * 
 */

