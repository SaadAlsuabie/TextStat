#ifndef STAT_GENERATOR_H_
#define STAT_GENERATOR_H_

#include <string>

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
public:
    void open_file(const std::string& filename);
    const std::string& get_source();
    void display_source();
};
#endif