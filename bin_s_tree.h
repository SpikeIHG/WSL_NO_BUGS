/**
 * @file bin_s_tree.h 
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief   二叉排序树的简单实现版本 可以作为头文件引入<stdlib.h>
 * @version 1.0
 * @date 2023-05-10
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
#ifndef BIN_S_TREE__H
#define BIN_S_TREE__h
//header
#include<stdlib.h>
#define _bs_tree_namespace_begin namespace _bs_tree {
#define _bs_tree_namespace_end  }

_bs_tree_namespace_begin

enum class status_info{BAD,OK};
using status_=int;

template <typename T>
class BSTree{
public:
    BSTree(T obj):tree_(obj.begin(),obj.end()){}
    traverse(std::ostream&os=std::cout,std::string delimiter=" ")const
            {for(auto i:tree_)std::cout<<i<<delimiter;};
    std::vector<T> insert(const decltype(this->begin()));
    std::vector<T> erase(const decltype(this->end()));
private:
    std::vector<T> tree_;
    int search(T)const;
};
template<typename T>
int BSTree<T>::search(T item)const
{
    tree_.find();
}

inline void visit()
{
    
}

_bs_tree_namespace_end

#endif // !BIN_S_TREE__H