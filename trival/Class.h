/**
 * @file Class.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-07
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  class primer
 */

#ifndef CLASS__H__
#define CLASS__H__
//header
#include<iostream>
#include<vector>    // essential
#include<string>
#include<map>   // a map from word to line_nos
#include<set>   // restore the line_no
#include<memory>
#include<fstream>
#include<sstream>
#define QUERY_NAMESPACE_BEGIN namespace query{
#define QUERY_NAMESPACE_END }
//! 注意我们只把 类的定义 放在了头文件里面 具体的方法实现 以及友元定义都放在源程序里面的 
QUERY_NAMESPACE_BEGIN   //namespace query
class QueryResult;
class TextQuery{        // 保存查询结果 由一个文件内容来构造
public:
    using line_no=std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);      // 外部定义 并且也许不需要 inline 函数
    QueryResult query(const std::string&)const;         // 返回拷贝的 原因 因为是局部构造的
private:
    std::shared_ptr<std::vector<std::string>> file_;
    std::map<std::string,std::shared_ptr<std::set<line_no>>> word_map_;
};

std::ostream&operator<<(std::ostream&,QueryResult);
class QueryResult{
    friend std::ostream&operator<<(std::ostream&os,QueryResult qr);
public:
    QueryResult(std::string s,
        std::shared_ptr<std::vector<std::string>>f,
        std::shared_ptr<std::set<TextQuery::line_no>>p):
        sought_(s),file_(f),lines_(p){}

private:
    std::string sought_;
    std::shared_ptr<std::vector<std::string>> file_;
    std::shared_ptr<std::set<TextQuery::line_no>> lines_;
};

inline std::string make_plural(const std::size_t i,const std::string&s)
{
    return i==1?s:s+"s";
}
std::ostream&operator<<(std::ostream&os,QueryResult qr)
{
    os<<"word: "<<qr.sought_<<" occurs "<<qr.lines_->size()<<
        make_plural(qr.lines_->size(),"time")<<" :\n";
    for(const auto &p:*qr.lines_)
    {
        os<<"\t(line "<<p+1<<"): "<<*(qr.file_->begin()+p)<<std::endl;
    }
    return os;
}

QUERY_NAMESPACE_END

#endif // !CLASS__H__#define CLASS__H__


