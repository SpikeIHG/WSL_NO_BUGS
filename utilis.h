/**
 * @file utilis.h       //! 文件名 全小写 最好 包含简明描述 可以_
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-09
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  头文件
 */
#ifndef UTILIS__H__
#define UTILIS__H__
//header
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<algorithm> 
#include<stack>

#include<fstream>       //! 有时候一些奇怪的报错 源自 没有包含头文件 尤其是使用 std:: 时 不会直接报错*getline
#include<sstream>       
#define _UTILIS_NAMESPACE_BEGIN namespace utilis{     //! 命名空间小写 最好全称 独特一点
#define _UTILIS_NAMESPACE_END        }

_UTILIS_NAMESPACE_BEGIN
inline std::string make_plural(size_t n,std::string s)
{
    return n==1?s:s+"s";
}
void showtips(void)
{
    std::cout<<"欢迎使用文件查询程序，注意，目前该文件查询系统仅支持英文，且最好不带标点符号的英文"<<'\n'
        <<"可以执行的操作有，查询单个单词，查询多个单词"<<'\n'
        <<"单个单词，或者单个单词没出现的行 eg ~sought 代表该单词没出现的行"<<'\n'
        <<"多个单词，eg I&YOU 代表两个单词均出现的行，He|Her 有一个出现的行，当然也支持上述几种混合,但是还不支持括号"<<std::endl
        <<"输入q退出 : ";
}

class QueryResult;          //! 类首字母大写 不要_ 每个单词均大写 struct typedef 模板 都这样
class TextQuery{
public:
    using line_no=std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&)const;   //! 所有数据成员包括 函数 都全小写 可以下划线 最后_结尾 struct可以不用
private:
    std::shared_ptr<std::vector<std::string>> file_;
    std::map<std::string,std::shared_ptr<std::set<line_no>>> word_map_;
};
std::ostream&operator<<(std::ostream&,QueryResult);
class QueryResult{
    friend std::ostream&operator<<(std::ostream&,QueryResult);
public:             //! public-> protected -> private
    QueryResult(std::string s,
        std::shared_ptr<std::vector<std::string>> f,
        std::shared_ptr<std::set<TextQuery::line_no>>p):
        sought_(s),file_c_(f),lines_ptr_(p){}
    std::set<TextQuery::line_no>::iterator begin(){return lines_ptr_->begin();}
    std::set<TextQuery::line_no>::iterator begin()const {return lines_ptr_->cbegin();}
    std::set<TextQuery::line_no>::iterator end(){return lines_ptr_->end();}
    std::set<TextQuery::line_no>::iterator end()const {return lines_ptr_->cend();}
    std::shared_ptr<std::vector<std::string>> get_file()const {return file_c_;}
private:
    std::string sought_;
    std::shared_ptr<std::vector<std::string>> file_c_;
    std::shared_ptr<std::set<TextQuery::line_no>> lines_ptr_;
};

//! 功能拓展
class QueryBase{
    friend class Query;
protected:
    using line_no=TextQuery::line_no;
    virtual ~QueryBase()=default;
private:
    virtual QueryResult eval(const TextQuery&t)const=0;
    virtual std::string rep()const=0;
};
class Query;
Query operator~(const Query&);
Query operator&(const Query&,const Query&);
Query operator|(const Query&,const Query&);

class Query{
    friend Query operator~(const Query&);
    friend Query operator&(const Query&,const Query&);
    friend Query operator|(const Query&,const Query&);
public:
    Query(const std::string&);
    QueryResult eval(const TextQuery&t)const{return obj_->eval(t);}
    std::string rep()const{return obj_->rep();}
private:
    Query(std::shared_ptr<QueryBase>p):obj_(p){}
    std::shared_ptr<QueryBase> obj_;   //! 管理的
};

std::ostream&operator<<(std::ostream&os,const Query &query)
{
    os<<query.rep();
    return os;
}

class WordQuery:public QueryBase{
    friend class Query;         //! 注意 友元不能 继承 所以 必须再次声明 虚调用 所以必须每个都来
    WordQuery(const std::string&s):query_word_(s){}
    QueryResult eval(const TextQuery&t)const{return t.query(query_word_);}
    std::string rep()const {return query_word_;}
    std::string query_word_;    //! 保存 基本信息
};

class NotQuery:public QueryBase{
    friend Query operator~(const Query&);       //! 都是因为我们将所有的 过程类进行封装
    NotQuery(const Query&q):query_(q){}
    QueryResult eval(const TextQuery&t)const;
    std::string rep()const {return "~"+query_.rep();}       //! 都是基于 wordquery
    Query query_;
};

inline Query operator~(const Query&operand)
{
    return std::shared_ptr<QueryBase>(new NotQuery(operand));       //! 重载运算符的形参命名
}
class BinaryQuery:public QueryBase{
protected:
    BinaryQuery(const Query&l,const Query&r,std::string op):
        lhs_(l),rhs_(r),opSym_(op){}                 // 可以继承用用
    std::string rep()const {return "("+lhs_.rep()+" "+opSym_+" "+rhs_.rep()+")";}
    Query lhs_,rhs_;
    std::string opSym_;      //operate symbol
};

class AndQuery:public BinaryQuery{
    friend Query operator&(const Query&,const Query&);
    AndQuery(const Query&l,const Query&r):
        BinaryQuery(l,r,"&"){}
    QueryResult eval(const TextQuery&t)const;
};
inline Query operator&(const Query&l,const Query&r)
{
    return std::shared_ptr<QueryBase>(new AndQuery(l,r));
}

class OrQuery:public BinaryQuery{
    friend Query operator|(const Query&,const Query&);
    OrQuery(const Query&l,const Query&r):
        BinaryQuery(l,r,"|"){}
    QueryResult eval(const TextQuery&t)const;
};
inline Query operator|(const Query&l,const Query&r)
{
    return std::shared_ptr<QueryBase>(new OrQuery(l,r));
}

class log{
public:
    log(std::fstream&file):log_file_(file){std::cout<<"X()"<<std::endl;}
    void update(const Query&option){
        log_file_<<"Time: "<<__TIME__<<" "<<"author: "
        <<"Your name"<<'\n'<<option.rep();
    }
private:
    std::fstream& log_file_;




};
inline void log(const Query &option)
{

}




_UTILIS_NAMESPACE_END


#endif // !UTILIS__H__