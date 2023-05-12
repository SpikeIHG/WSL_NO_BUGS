/**
 * @file QUERY.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.1
 * @date 2023-05-08
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  let's use the inheritance to build the query text; and that will be perfect;
 */

#include"my_query.h"
using namespace std;

q::QueryResult q::TextQuery::query(const string&sought)const 
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto result=word_map_.find(sought);
    if(result==word_map_.end())
        return q::QueryResult(sought,file_,nodata);
    else
        return q::QueryResult(sought,file_,result->second);
}

ostream&q::operator<<(ostream&os,q::QueryResult qr)     // ! 很容易出错哈
{
    os<<"word : "<<qr.sought_<<" occurs "<<qr.lines_->size()<<" "
        <<make_plural(qr.lines_->size(),"time")<<'\n';
    for(auto n:*qr.lines_)
        os<<"\t(line "<<n+1<<") :"<<*(qr.file_->begin()+n)<<endl;    
}

void runQuery(ifstream&infile)
{
    q::TextQuery f(infile);
    while(true)
    {
        cout<<"Enter the word you wanna query and q to terminate : ";
        string sought;
        if(!(cin>>sought)||"q"==sought)
            break;
        cout<<f.query(sought);
    }
}
int main(void)
{
    ifstream infile("white_bird.txt");
    if(infile)
        runQuery(infile);
    else
        throw runtime_error("no such file");
    return 0;
}