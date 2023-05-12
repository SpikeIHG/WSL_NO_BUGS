/**
 * @file my_query.h
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-08
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  the header to make the true
 */

#ifndef MY_QUERY__H__
#define MY_QUERY__H__
//header
#include<iostream>
#include<vector>    // essential
#include<string>
#include<map>   // a map from word to line_nos
#include<set>   // restore the line_no
#include<memory>
#include<fstream>
#include<sstream>
#include<algorithm>
#define QUERY_NAMESPACE_BEGIN namespace q{
#define QUERY_NAMESPACE_END }

QUERY_NAMESPACE_BEGIN

inline std::string make_plural(size_t i,std::string word)
{
    return i==1?word:word+"s";
}
class QueryResult;  //! 为了进行函数声明 需要一个前置声明
class TextQuery{
public:
    using line_no=std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);   //! 由一个文件得到一个 处理后对象
    QueryResult query(const std::string &)const;      //! reference to const attention the retval
private:
    std::shared_ptr<std::vector<std::string>> file_;    // ptr the file
    std::map<std::string,std::shared_ptr<std::set<line_no>>> word_map_;
};

TextQuery::TextQuery(std::ifstream&infile):file_(new std::vector<std::string>)
{
    std::string text;      // text of a line
    while(std::getline(infile,text))
    {
        file_->emplace_back(text);
        line_no n=file_->size()-1;      //minus 1 is better for latter op
        std::stringstream record(text);
        std::string word;
        while(record>>word)
        {
            auto&lines=word_map_[word];
            if(!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}
std::ostream&operator<<(std::ostream&,QueryResult);
class QueryResult{
    friend std::ostream&operator<<(std::ostream&,QueryResult);
public:
    QueryResult(std::string s,
        std::shared_ptr<std::vector<std::string>>f,
        std::shared_ptr<std::set<TextQuery::line_no>>p):
        sought_(s),file_(f),lines_(p){}
    std::set<TextQuery::line_no>::iterator begin(){return lines_->begin();}
    const std::set<TextQuery::line_no>::iterator begin()const{return lines_->cbegin();}
    std::set<TextQuery::line_no>::iterator end(){return lines_->end();}
    const std::set<TextQuery::line_no>::iterator end()const{return lines_->cend();}
    std::shared_ptr<std::vector<std::string>> get_file()const{return file_;}
private:
    std::string  sought_;
    std::shared_ptr<std::vector<std::string>> file_;
    std::shared_ptr<std::set<TextQuery::line_no>> lines_;

};
class Query;
// !升级版
class Query_base{       //! 这个是一个抽象基类 因为有纯虚函数  并且不定义public:
    friend class Query;     // ! 需要是使用函数 
protected:
    using line_no=TextQuery::line_no;
    virtual ~Query_base()=default;      //! 习惯 一个基类的析构函数   
private:
    virtual QueryResult eval(const TextQuery&)const=0;
    virtual std::string rep()const=0;   // 两个private 的纯虚函数 注意private 就无用 但是派生类还是可以定义哈

};
Query operator~(const Query&);   //! 注意 这里是const & 非常重要的 最根本的一个简化 东西
Query operator&(const Query&,const Query&);
Query operator|(const Query&,const Query&);

class Query{
    friend Query operator~(const Query&);   //! 注意 这里是const & 非常重要的 最根本的一个简化 东西
    friend Query operator&(const Query&,const Query&);
    friend Query operator|(const Query&,const Query&);
public:     //接口函数
    Query(const std::string&);  // !
    QueryResult eval(const TextQuery&text)const{return q->eval(text);}
    std::string rep()const {return q->rep();}

private:
    Query(std::shared_ptr<Query_base> query):q(query){}     // !
    std::shared_ptr<Query_base> q;
};

std::ostream&operator<<(std::ostream&os,const Query&query)
{
    return os<<query.rep();     //good !!!
}

class WordQuery:public Query_base{      // 全是私有因为不希望直接定义 被暴露在外面了用户不直接使用而是通过接口
    friend class Query;
    WordQuery(const std::string&s):query_word_(s){} // 当然就不需要默认了
    QueryResult eval(const TextQuery&t)const{t.query(query_word_);}
    std::string rep()const {return query_word_;}
    std::string query_word_;
};

class NotQuery:public Query_base{
    friend Query operator~(const Query&);
    NotQuery(const Query&q):query_(q){}
    QueryResult eval(const TextQuery&t)const;       //! 注意一模一样
    std::string rep()const {return ("~"+query_.rep());}
    Query query_;
};
inline Query operator~(const Query&operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}
class BinaryQuery:public Query_base{
protected:
    BinaryQuery(const Query&lhs,const Query&rhs,std::string s):
        lhs_(lhs),rhs_(rhs),opSym(s){}
    std::string rep()const {return "( "+lhs_.rep()+" "+opSym+" "+rhs_.rep()+" )";}
    Query lhs_,rhs_;
    std::string opSym;
};

class AndQuery:public BinaryQuery{
    friend Query operator&(const Query&,const Query&);
    AndQuery(const Query&left,const Query &right):
        BinaryQuery(left,right,"&"){}
    QueryResult eval(const TextQuery&t)const;
};
inline Query operator&(const Query&lhs,const Query&rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

class OrQuery:public BinaryQuery{
    friend Query operator|(const Query&,const Query&);
    OrQuery(const Query&left,const Query&right):
        BinaryQuery(left,right,"|"){}
    QueryResult eval(const TextQuery&)const;
};

inline Query operator|(const Query&lhs,const Query&rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult AndQuery::eval(const TextQuery&t)const
{   
    auto left=lhs_.eval(t),right=rhs_.eval(t);
    auto ret_line=std::make_shared<std::set<line_no>>(left.begin(),left.end());
    ret_line->insert(right.begin(),right.end());
    return QueryResult(rep(),left.get_file(),ret_line);
}

QueryResult OrQuery::eval(const TextQuery&t)const
{
    auto left=lhs_.eval(t),right=rhs_.eval(t);
    auto ret_lines=std::make_shared<std::set<line_no>>();
    std::set_intersection(left.begin(),left.end(),
                        right.begin(),right.end(), 
                        inserter(*ret_lines,ret_lines->begin()));
    return QueryResult(rep(),left.get_file(),ret_lines);
}

QueryResult NotQuery::eval(const TextQuery&t)const
{
    auto result=query_.eval(t);
    line_no sz=result.get_file()->size();
    auto begin=result.begin(),end=result.end();
    auto ret_lines=std::make_shared<std::set<line_no>>();
    for(size_t n=0;n!=sz;++n)
    {
        if(begin==end||*begin!=n)
            ret_lines->insert(n);
        else if(*begin==n)
            ++begin;
    }
}

QUERY_NAMESPACE_END
#endif // !MY_QUERY__H__
