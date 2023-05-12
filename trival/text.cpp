/**
 * @file text.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-08
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 *  验证一下这个软件 的可行性
 */

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<algorithm>

#include<fstream>
#include<sstream>

using namespace std;

class QueryResult;
class TextQuery{
public:
    using line_no=vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&)const;
private:
    shared_ptr<vector<string>> file_;
    map<string,shared_ptr<set<line_no>>> word_map_;
};

TextQuery::TextQuery(ifstream&infile):file_(new vector<string>)
{
    string text;
    while(getline(infile,text))
    {
        file_->emplace_back(text);
        line_no n=file_->size()-1;
        stringstream record(text);
        string word;
        while(record>>word)
        {
            auto &lines=word_map_[word];
            if(!lines)
            lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

ostream&operator<<(ostream&os,QueryResult qr);

ostream&print(ostream&os,QueryResult qr);
class QueryResult{
    friend ostream&operator<<(ostream&os,QueryResult qr);
    friend ostream&print(ostream&os,QueryResult qr);
public:
    QueryResult(string s,shared_ptr<vector<string>> f,shared_ptr<set<TextQuery::line_no>>p):
        sought(s),file(f),lines(p){}

private:
    string sought;
    shared_ptr<vector<string>> file;
    shared_ptr<set<TextQuery::line_no>> lines;
};

QueryResult TextQuery::query(const string&s)const 
{   
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto iter=word_map_.find(s);
    if(iter==word_map_.end())
        return QueryResult(s,file_,nodata);
    else
        return QueryResult(s,file_,iter->second);
}

ostream&print(ostream&os,QueryResult qr)
{
    os<<"the word "<<qr.sought<<" occurs "<<qr.lines->size()<<" times\n";
    for(auto l:*qr.lines)
    cout<<"\t(line "<<l+1<<")   "<<*(qr.file->begin()+l)<<endl;
}

ostream&operator<<(ostream&os,QueryResult qr)
{
     os<<"the word "<<qr.sought<<" occurs "<<qr.lines->size()<<" times\n";
    for(auto l:*qr.lines)
    cout<<"\t(line "<<l+1<<")   "<<*(qr.file->begin()+l)<<endl;
}
void runQuery(ifstream&f)
{
    TextQuery infile(f);
    cout<<"Query a word and type it in and q to quit: ";
    string op;
    while((cin>>op)&&op!="q")
    {
        cout<<infile.query(op);
        cout<<"next word:  ";
    }
}

int main(void)
{
    cout<<unitbuf;
    ifstream infile("white_bird.txt");
    if(infile)
        runQuery(infile);
    else
    cerr<<"bad file source"<<endl;

    return 0;
}