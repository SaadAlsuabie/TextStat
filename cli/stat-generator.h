#ifndef STAT_GENERATOR_H_
#define STAT_GENERATOR_H_

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

/* Class to represent a word along with it's source i.e linenumber */
class word
{
private:
    std::string value;
    size_t line_num;
    size_t word_num;
public:
    word();
    word(const std::string& val,size_t ln,size_t word_num);
    const std::string& get_value();
    size_t get_line_num();
    size_t get_word_num();
};

/* Class to implement all the juicy functionality related to text stats*/
class stat_generator
{
private:
    std::string filename;
    std::string source;
    std::vector<word> words;
    std::string results; //csv string
    static bool is_word_delimiter(char ch);
    std::vector<word> tokenize();
    size_t find_substr_linenum(const std::string& str,size_t& last);
public:
    void open_file(const std::string& filename);
    const std::string& get_source();
    // This for debugging only
    void display_tokens();
    void display_source();
    void save_results(); // saves the results of all searches made so far
    void search_and_display(const std::string& what);
    std::string search(const std::string& what);
    void search_regex_and_display(const std::string& what);
    std::string search_regex(const std::string&);
};

#endif
