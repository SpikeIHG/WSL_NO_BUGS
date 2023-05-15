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
#include"SplayTree.h"
#include"RBTree.h"
#include<fstream>
using namespace rb_tree_;
int main(void)
{
    // AvlTree T=NULL;

    // for(int i=1;i!=10;++i)
    //     T=Insert(i*2,T);

    // InOrderTraverse(T);
    // putchar('\n');
    
    // SplayTree T_splay;
    // T_splay=Initialize();


    // if(NullNode==nullptr)
    //     std::cout<<"BAD";
    //  for(int i=1;i!=10;++i)
    //     {
    //         if(!NullNode)
    //         {
    //             printf("%d***",i);
    //             break;
    //         }
    //      T_splay=Insert(i*i*i,T_splay);
    //     }

    // InOrderTraverse(T_splay);

    // T_splay=Remove(1,T_splay);
    // putchar('\n');
    // InOrderTraverse(T_splay);

    RedBlackTree T=rb_tree_::Initialize();
    for(int i=1;i!=10;++i)
        T=rb_tree_::Insert(i*i,T);

    rb_tree_::InorderTraverse(T);

    std::string pause;
    std::cin>>pause;

    return 0;
}