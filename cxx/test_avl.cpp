/**
 * @file test_avl.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief test avl tree
 * @version 1.0
 * @date 2023-05-12
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */

#include"AvlTree.h"

using namespace avl_tree;



int main(void)
{
    AvlTree T=NULL;
    for(int i=1;i!=10;++i)
        T=Insert(i*2,T);

    InOrderTraverse(T);

    return 0;
}