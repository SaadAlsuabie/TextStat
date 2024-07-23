#include "stat-generator.h"
#include <fstream>
#include <iostream>
#include <string>

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

////
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
    this->filename = filename;
}
const std::string& stat_generator::get_source()
{
    return source;
}

void stat_generator::display_source()
{
    cout << source << endl;
}