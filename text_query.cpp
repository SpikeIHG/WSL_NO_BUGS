/**
 * @file text_query.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-07
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  class primer
 */

#include"Class.h"
using namespace std;
using namespace query;

TextQuery::TextQuery(ifstream&infile):
//file_(std::make_shared<std::vector<std::string>>())      //命名 规范 可以直接给智能指针进行初始化 用动态分配的嘛虽然是 explicit
file_(new vector<string>)
{
    string text;    //? 一个固定的模式了 一行的文本
    while(getline(infile,text))
    {
        file_->emplace_back(text);      // 将文本给放入对象里 然后由于是顺序所以 统计一下行数
        line_no n=file_->size()-1;      // 宁可 后面写加一  而不写减一
        stringstream record(text);      //将行文本转换为一个 流对象
        string word;        
        while(record>>word)
        {
            auto &lines=word_map_[word];    // ! 注意这里 是一个lines 的set 指针 并且用引用 因为可能要改变
            if(!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string&s)const{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);       //! 静态变量的使用
    auto loc=word_map_.find(s);     //! loc 命名规范
    if(loc==word_map_.end())
        return QueryResult(s,file_,nodata);
    else
        return QueryResult(s,file_,loc->second);
}


void runQuery(ifstream&infile)
{
    TextQuery q(infile);
    while(true)
    {
        cout<<"Enter the word you wanna search(press q to terminate the program) : ";
        string pause;
        while(!(cin>>pause)&&pause!="q")
            cout<<q.query(pause);
    }
}

int main(void)
{
    ifstream infile("white_bird.txt");
    //runQuery(infile);
    string ap;
    infile>>ap;
    cout<<ap;

    return 0;
}