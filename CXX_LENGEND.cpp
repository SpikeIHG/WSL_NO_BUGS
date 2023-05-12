/**
 * @file CXX_LENGEND.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-09
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  关于class 的故事
 * 
 */
//OPP

#include"utilis.h"
using namespace std;

utilis::TextQuery::TextQuery(std::ifstream&infile):
    file_(new std::vector<std::string>)
{   
    std::string text;   // ! lines
    while(std::getline(infile,text))
    {
        file_->emplace_back(text);
        line_no n=file_->size()-1;
        std::stringstream record(text);
        std::string word;
        while(record>>word)
        {
            auto &lines=word_map_[word];
            if(!lines)
                lines.reset(new std::set<line_no>);          //! 讲究 因为时赋值 所以用reset 用动态分配
            lines->insert(n);
        }
    }
}

utilis::QueryResult utilis::TextQuery::query(const string&sought)const
{
    static shared_ptr<set<line_no>>nodata(new set<line_no>);
    auto result=word_map_.find(sought);
    if(result==word_map_.end())
        return QueryResult(sought,file_,nodata);
    else
        return QueryResult(sought,file_,result->second);
}



ostream&utilis::operator<<(ostream&os,QueryResult qr)
{
    cout<<"The word : "<<qr.sought_<<" occurs "
        <<qr.lines_ptr_->size()<<" "<<make_plural(qr.lines_ptr_->size(),"time")<<'\n';
    for(auto n:*qr.lines_ptr_)
        cout<<"\t(line "<<n+1<<") "<<*(qr.file_c_->begin()+n)<<endl;
        return os;
}

void runQuery(ifstream&infile)
{
    utilis::TextQuery q(infile);
    while(true)
    {
        cout<<"Enter a word you wanna search and q to terminate: ";
        string sought;
        if(!(cin>>sought)||sought=="q")
            break;
        cout<<q.query(sought);
    }
}

utilis::Query::Query(const string&s):obj_(new WordQuery(s)){}

utilis::QueryResult utilis::NotQuery::eval(const TextQuery&t)const
{
    auto left=lhs_.eval(t),right=rhs_.eval(t);        //! 太妙了 完全不需要在意具体的实现
    auto ret_lines=make_shared<set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(),right.end());
    return QueryResult(rep(),left.get_file(),ret_lines);
}
utilis::QueryResult utilis::AndQuery::eval(const TextQuery&t)const
{
    auto left=lhs_.eval(t),right=rhs_.eval(t);
    auto ret_lines=make_shared<set<line_no>>();
    set_intersection(left.begin(),left.end(),
                right.begin(),right.end(),
                inserter(*ret_lines,ret_lines->begin()));
    return QueryResult(rep(),left.get_file(),ret_lines);
}

utilis::QueryResult utilis::NotQuery::eval(const TextQuery&t)const
{
    auto result=query_.eval(t);
    line_no sz=result.get_file()->size();
    auto beg=result.begin(),end=result.end();
    auto ret_lines=make_shared<set<line_no>>();
    for(size_t n=0;n!=sz;++n)
    {
        if(beg==end||n!=*beg)
            ret_lines->insert(n);
        else if(n==*beg)
            ++beg;
    }
    return QueryResult(rep(),result.get_file(),ret_lines);
}

using utilis::Query;

void runQuery(ifstream&infile,int)
{
    utilis::showtips();
    
    while(true)
    {
        string sought;
        if(!(cin>>sought)||sought=="q")
            break;
        stringstream record(sought);
        string operand;
        stack<Query> expr;
        Query obj("");
        while(record>>operand)
        {
            if(operand.front()=='~')
            {
                expr.push(~Query(string(operand.begin()+1,operand.end())));
            }
            else if(operand=="&")
            {
                record>>operand;
                Query tmp=Query(operand)&Query(expr.top());
                expr.pop();expr.push(tmp);
            }
            else if(operand=="|")
            {
                record>>operand;
                Query tmp=Query(operand)|Query(expr.top());
                expr.pop();expr.push(tmp);
            }
            else
            expr.push(Query(operand));
        }
        cout<<expr.top().eval(infile)<<endl;
    }
}
int main(void)
{
    ifstream infile("white_bird.txt");
    runQuery(infile,0);
    Query p=Query("birds")&Query("were"); 
    cout<<p.eval(infile);
    return 0;
}

