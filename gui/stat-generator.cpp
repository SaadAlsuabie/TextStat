#include "stat-generator.h"
#include <exception>

using namespace std;

//Implementations for word class
word::word()
{}
word::word(const std::string& val,size_t ln,size_t word_num)
{
    value = val;
    line_num = ln;
    this->word_num = word_num;
}
const std::string& word::get_value() { return value; }
size_t word::get_line_num() { return line_num; }
size_t word::get_word_num() { return word_num; }
//Implementations for stat_generator class
bool stat_generator::is_word_delimiter(char ch)
{
    return (ch == ' ' || ch == ',' || ch == '.' || ch == '\n' || ch == '\r' || ch == '!');
}
std::vector<word> stat_generator::tokenize()
{
    size_t line_num = 1;
    size_t i = 0;
    size_t len = source.length();
    vector<word> words;
    while(i < len && is_word_delimiter(source[i]))
    {
        if(source[i] == '\n')  line_num++;
        i++;
    }
    size_t start = i;
    size_t word_num = 1;
    while(i < len)
    {
        if(is_word_delimiter(source[i]))
        {
            size_t end = i - 1; // i != 0 guaranteed
            size_t word_length = end - start + 1;
            words.push_back(word(source.substr(start,word_length),line_num,word_num++));
            while(i < len && is_word_delimiter(source[i]))
            {
                if(source[i] == '\n')
                {
                    line_num++;
                    word_num = 1;
                }
                i++;
            }
            start = i;
        }
        i++;
    }
    if(start != len)
    {
        size_t end = len-1;
        size_t word_length = end - start + 1;
        words.push_back(word(source.substr(start,word_length),line_num,word_num++));
    }
    return words;
}
size_t stat_generator::find_substr_linenum(const std::string& str,size_t& start)
{
    if(str.length() == 0)
        return 0;
    size_t line_num = 1;
    for(size_t i = 0;i < source.length(); i++)
    {
        if(source[i] == '\n')
            line_num++;
        if(source[i] == str[0] && source.substr(i,str.length()) == str && i >= start)
        {
            start = i + str.length();
            return line_num;
        }
    }
    return 0;
}

// public methods

void stat_generator::open_file(const std::string& filename)
{
    ifstream fin;
    fin.open(filename.c_str());
    if(!fin.is_open())
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    source.clear();
    char ch;
    while((ch = fin.get()) != EOF)
        source.push_back(ch);
    words = tokenize();
    this->filename = filename;
    results = "filename,search_term,frequency\n";
}
const std::string& stat_generator::get_source()
{
    return source;
}
void stat_generator::display_tokens()
{
    for(auto e: words)
    {  
        cout << e.get_line_num()<<" |"<<e.get_value()<<"|"<<endl;
    }
}
void stat_generator::display_source()
{
    cout << source << endl;
}
void stat_generator::search_and_display(const std::string& what)
{
    size_t count = 0;
    size_t idx = 0;
    cout << "-- Matches --" << endl;
    for(auto word: words)
    {
        if(word.get_value() == what)
        {
            cout << "Line "<<word.get_line_num() <<", word number "<< word.get_word_num() << endl;
            count++;
        }
        idx++;
    }
    cout << count << " total matches found." << endl;
    cout << "Hit percentage: " << (float)count/words.size() << endl;
    results += filename+",\""+what+"\","+to_string(count);
}
std::string stat_generator::search(const std::string& what)
{
    size_t count = 0;
    size_t idx = 0;
    std::string output = "";
    output += "-- Matches --\n";
    for(auto word: words)
    {
        if(word.get_value() == what)
        {
            output += "Line "+to_string(word.get_line_num())+", word number "+to_string(idx+1)+"\n";
            count++;
        }
        idx++;
    }
    output += to_string(count) + " total matches found.\n";
    output += "Hit percentage: "+to_string((float)count/words.size()) + "\n";
    results += filename+",\""+what+"\","+to_string(count); // output csv
    return output;
}
void stat_generator::save_results()
{
    ofstream out("results.csv");
    out.write(results.c_str(),results.size());
}
void stat_generator::search_regex_and_display(const std::string& what)
{
    if(what == "")
        return;
    std::string src = source;
    try
    {
        regex exp(what);
        smatch res;
        size_t start = 0;
        while (regex_search(src, res, exp))
        {
            size_t ln = find_substr_linenum(res[0],start);
            if(ln != 0 )
                cout << "Line "<< ln << ": ";
            cout << res[0] << endl;
            if(res[0] == "")
                break;
            src = res.suffix();
        }
    }
    catch(std::exception& e)
    {
        cerr << e.what() << endl;
        return;
    }
}
std::string stat_generator::search_regex(const std::string& what)
{
    if(what == "")
        return "";
    std::string src = source;
    std::string output;
    try
    {
        regex exp(what);
        smatch res;
        size_t start = 0;
        while (regex_search(src, res, exp))
        {
            size_t ln = find_substr_linenum(res[0],start);
            if(ln != 0 )
            {
                output += "Line "+to_string(ln)+": ";
            }
            output += (string)res[0]+(string)"\n";
            src = res.suffix();
        }
    }
    catch(std::exception& e)
    {
        output += (string)e.what()+"\n";
        return output;
    }
    return output;
}
